-- main.lua

-- 获取代码目录
--local script_path = debug.getinfo(1, "S").source:match("^@(.*/)")
local script_path = '/home/wsl/test/fluent-bit/examples/filter_lua/main.lua'
-- 更新package.path
package.path = package.path .. ";" .. script_path .. "?.lua;" .. script_path .. "?/init.lua;" .. script_path .. "utils/?.lua"

local init = require("init")
local shared = require("shared")
local match_utils = require("utils.match_utils")
local log_utils = require("utils.log_utils")

local config = init.config

shared.update_rules_cache()

local function check_rules_file()
    local check_interval = 60 -- 设置检查间隔时间（秒）

    return function()
        local current_time = os.time()
        if current_time - shared.last_rules_check_time < check_interval then
            return
        end

        shared.last_rules_check_time = current_time

        local success, attr = pcall(lfs.attributes, config.rules_file_path)
        if not success then
            shared.log_message("Lua Fast Filter " .. os.date("%Y-%m-%d %H:%M:%S") .. " Failed to get attributes of rules file: " .. config.rules_file_path)
            return
        end
        if attr and attr.modification then
            if shared.last_modified ~= attr.modification then
                shared.log_message("Lua Fast Filter " .. os.date("%Y-%m-%d %H:%M:%S") .. " Rule config change detected. Updating...")
                shared.last_modified = attr.modification
                shared.update_rules_cache(config.rules_file_path)
            end
        end
    end
end

local check_rules = check_rules_file()

function update_tag(tag, timestamp, record)

    -- 60s
    check_rules()

    -- 检查并清理缓存
    shared.clean_cache()

    if shared.tag_cache[tag] then
        return 0, timestamp, record
    end

    local file = record["file"]
    local service_id = record["service_id"]

    if not file or not service_id then
        local new_record = record
        new_record["lokitag"] = tag
        return 2, timestamp, new_record
    end

    local parts = {}
    for part in string.gmatch(file, "[^/]+") do
        table.insert(parts, part)
    end
    file = table.concat(parts, "/", 5)

    local matched = false
    local service_rules = shared.rules_cache.service_rules[service_id]
    if service_rules then
        -- 规则中只有一个service_id, 但是没有采集路径
        if type(service_rules) ~= "table" then
            local new_record = record
            new_record["lokitag"] = tag
            return 2, timestamp, new_record
        end
        for _, rule in ipairs(service_rules) do
            -- 匹配Fast逻辑
            if rule.fast_match_type then
                if match_utils.match_filename_fast(file, rule.file_suffix_pattern, log_utils.handle_absolute_logs, config.log_prefixes) then
                    matched = true
                    shared.tag_cache[tag] = os.time()
                    shared.log_message(string.format("Lua Fast Filter %s New entry added to tag_cache Hits Fast Rule service_id: %s file: %s tag: %s",
                            os.date("%Y-%m-%d %H:%M:%S"), service_id, file, tag))
                    break
                end
                -- 匹配少量的存量正则逻辑
            else
                if match_utils.match_filename_regex(file, rule.file_suffix_pattern) then
                    matched = true
                    shared.tag_cache[tag] = os.time()
                    shared.log_message(string.format("Lua Fast Filter %s New entry added to tag_cache Hits Regex Rule service_id: %s file: %s tag: %s",
                            os.date("%Y-%m-%d %H:%M:%S"), service_id, file, tag))
                    break
                end
            end
        end
    end

    if not matched then
        for _, rule in ipairs(shared.rules_cache.global_rules) do
            if match_utils.match_filename_regex(file, rule.file_suffix_pattern) then
                matched = true
                shared.tag_cache[tag] = os.time()
                shared.log_message(string.format("Lua Fast Filter %s New entry added to tag_cache Hits Global Rule service_id: %s file: %s tag: %s",
                        os.date("%Y-%m-%d %H:%M:%S"), service_id, file, tag))
                break
            end
        end
    end

    if not matched then
        local new_record = record
        new_record["lokitag"] = tag
        return 2, timestamp, new_record
    end

    return 0, timestamp, record
end

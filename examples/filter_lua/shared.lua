local lfs = require("lfs")
local json = require("cjson")
local init = require("init")

local config = init.config
local file_utils = init.file_utils

local shared = {
    tag_cache = {},
    rules_cache = nil,
    last_modified = 0,
    last_rules_check_time = 0,
    last_tagcache_check_time = 0,
}

function shared.log_message(message)
    print(message)
    io.flush()  -- 确保日志立即输出
end

function shared.update_rules_cache()
    local content, err = file_utils.read_json_file(config.rules_file_path)
    if not content then
        shared.log_message("Lua Fast Filter " .. os.date("%Y-%m-%d %H:%M:%S") .. " Error reading JSON file: " .. err)
        return
    end

    local success, new_rules = pcall(json.decode, content)
    if success and new_rules then
        shared.rules_cache = new_rules
        shared.log_message("Lua Fast Filter " .. os.date("%Y-%m-%d %H:%M:%S") .. " Rules cache updated")
    else
        shared.log_message("Lua Fast Filter " .. os.date("%Y-%m-%d %H:%M:%S") .. " Failed to decode rules JSON")
    end
end

-- 定期清理缓存
function shared.clean_cache()
    local check_interval = 600 -- 设置检查间隔时间（秒）
    local cache_expiry_time = 36 * 3600 -- 36 小时过期时间
    local current_time = os.time()

    if current_time - shared.last_tagcache_check_time < check_interval then
        return
    end

    shared.last_tagcache_check_time = current_time

    for tag, timestamp in pairs(shared.tag_cache) do
        if current_time - timestamp > cache_expiry_time then
            shared.tag_cache[tag] = nil
            shared.log_message("Lua Fast Filter " .. os.date("%Y-%m-%d %H:%M:%S") .. " Cache entry expired and removed: " ..
                    tag)
        end
    end
end

return shared
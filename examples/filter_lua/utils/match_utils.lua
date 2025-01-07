local match_utils = {}

function match_utils.diff(file_suffix, rule_file_suffix_pattern)
    if #file_suffix ~= #rule_file_suffix_pattern then
        return false
    end
    for i = 1, #file_suffix do
        if rule_file_suffix_pattern:sub(i, i) == '?' or file_suffix:sub(i, i) == rule_file_suffix_pattern:sub(i, i) then
            -- continue
        else
            return false
        end
    end
    return true
end

function match_utils.match_filename_regex(file, pattern)
    local pattern = pattern:gsub("\\", "%%")
    return string.match(file, pattern) ~= nil
end

function match_utils.match_filename_fast(file, file_suffix_pattern, handle_absolute_logs, log_prefixes)
    local files = {}
    for matched_file in string.gmatch(file_suffix_pattern, '([^,]+)') do
        table.insert(files, matched_file)
    end

    for _, matched_file in ipairs(files) do
        matched_file = handle_absolute_logs(matched_file, log_prefixes)
        if match_utils.diff(file, matched_file) then
            return true
        end
    end
    return false
end

return match_utils
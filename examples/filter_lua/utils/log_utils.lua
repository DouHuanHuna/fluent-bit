local log_utils = {}

function log_utils.handle_absolute_logs(file, log_prefixes)
    for _, prefix in ipairs(log_prefixes) do
        if string.find(file, prefix, 1, true) then
            return string.sub(file, #prefix + 1)
        end
    end
    return file
end

return log_utils
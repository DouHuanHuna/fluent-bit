local file_utils = {}

function file_utils.read_json_file(file_path)
    local file, err = io.open(file_path, "r")
    if not file then
        return nil, "Could not open file: " .. file_path .. " - " .. (err or "unknown error")
    end
    local content = file:read("*a")
    file:close()
    return content
end

return file_utils
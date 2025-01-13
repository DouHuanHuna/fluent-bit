function modify_record(tag, timestamp, record)
    -- 修改 message 字段的内容
    record["message"] = "Modified: " .. record["message"]

    -- 添加一个新的字段
    record["processed"] = "true"

    -- 返回修改后的记录
    return 1, timestamp, record
end

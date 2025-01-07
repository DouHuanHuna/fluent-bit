local config = {
    update_interval = 30,
    new_tag = "unmatched",
    --rules_file_path = os.getenv("RULES_FILE_PATH"),
    rules_file_path = './rules.json',
    log_prefixes = { "/data0/www/applogs/", "/data0/www/logs/", "/opt/app/logs/", "/home/app/logs", "/home/log/" }
}

return config
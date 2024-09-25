//
// Created by yzm on 2024/9/24
//

#include <iostream>

#include "debug.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

void Debug::Init()
{
    try
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::trace);

        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/multisink.txt", true);
        file_sink->set_level(spdlog::level::trace);

        spdlog::sinks_init_list sink_list = {file_sink, console_sink};

        spdlog::set_default_logger(std::make_shared<spdlog::logger>("multi_sink", sink_list));
        spdlog::set_pattern("[source %s] [function %!] [line %#] [%^%l%$] %v");

        DEBUG_LOG_INFO("spdlog init success");

    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "spdlog init failed: " << ex.what() << std::endl;
    }
}
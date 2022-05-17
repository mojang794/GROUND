#pragma once

#include <time.h>
#include <string>

namespace gr
{
    // Basic date time class
    class Time
    {
    public:
        static std::string GetDateTime()
        {
            time_t rawtime;
            struct tm timeinfo;
            char buffer[80];

            time(&rawtime);
            localtime_s(&timeinfo, &rawtime);
            strftime(buffer, 80, "%d-%m-%Y_%H-%M-%S", &timeinfo);
            return std::string(buffer);
        }

    public:
        static std::string GetDate()
        {
            time_t rawtime;
            struct tm timeinfo;
            char buffer[80];

            time(&rawtime);
            localtime_s(&timeinfo, &rawtime);
            strftime(buffer, 80, "%d-%m-%Y", &timeinfo);
            return std::string(buffer);
        }

    public:
        static std::string GetTime()
        {
            time_t rawtime;
            struct tm timeinfo;
            char buffer[80];

            time(&rawtime);
            localtime_s(&timeinfo, &rawtime);
            strftime(buffer, 80, "%H-%M-%S", &timeinfo);
            return std::string(buffer);
        }
    };
}
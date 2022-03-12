/*
 * @Author: your name
 * @Date: 2022-03-02 14:22:24
 * @LastEditTime: 2022-03-12 12:46:27
 * @LastEditors: lqf
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%A
 * @FilePath: \configSystem\test\config.cpp
 */
#include <iostream>
#include <fstream>
#include <memory>
#include <config.h>
#include <json.hpp>
#include <logger.h>
#include <set>
#include <list>
using namespace nlohmann;
using namespace Itachi;
// 
// ConfigVar<std::vector<int>>::ptr vec =
//     Config::LookUp(".lqf.listenport", std::vector<int>{1, 2, 3});

// ConfigVar<std::set<int>>::ptr set1 =
//     Config::LookUp("System.lqf.Listenport1", std::set<int>{1, 2, 3});

// ConfigVar<std::list<int>>::ptr list1 =
//     Config::LookUp("System.lqf.Listenport2", std::list<int>{1, 2, 3});

// ConfigVar<std::vector<LogAppenderDefiner>>::ptr vec_loggers =
//     Config::LookUp(".lqf.loggers", std::vector<LogAppenderDefiner>{});

int main()
{

    Config::LoadFromJson("/home/lqf/cpp/Itachi/config.json");

    
    return 0;
}
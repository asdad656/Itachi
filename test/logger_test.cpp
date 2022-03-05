/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-05 13:15:53
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-05 15:29:36
 * @Description: 
 */
#include <iostream>
#include <fstream>
#include <memory>
#include <config.h>
#include <json.hpp>
#include <logger.h>
#include <set>
#include <list>
#include "definition.h"
using namespace nlohmann;
using namespace Itachi;
std::vector<int> data = {1, 2, 3, 4, 6};
ConfigVar<std::vector<int>>::ptr vec =
    Config::LookUp(".lqf.listenport", std::vector<int>{1, 2, 3});

ConfigVar<std::set<int>>::ptr set1 =
    Config::LookUp("System.lqf.Listenport1", std::set<int>{1, 2, 3});

ConfigVar<std::list<int>>::ptr list1 =
    Config::LookUp("System.lqf.Listenport2", std::list<int>{1, 2, 3});



int main()
{


    Config::LoadFromJson("/home/lqf/cpp/Itachi/config.json");
    LOG_DEBUG<<"Mesasdasdfsage";

    LOG_ERROR<<"Mesasdasdfsage";


    LOG_INFO<<"Mesasdasdfsage";


    LOG_WARN<<"Mesasdasdfsage";



    LOG_FATAL<<"Mesasdasdfsage";

    return 0;
}
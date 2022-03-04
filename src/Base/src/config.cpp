/*
 * @Author: your name
 * @Date: 2022-03-02 13:49:58
 * @LastEditTime: 2022-03-05 00:20:18
 * @LastEditors: lqf
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \newProject\config.cpp
 */
#include"config.h"
#include<json.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include<list>
namespace Itachi{
using namespace nlohmann;

ConfigVarBase::ptr Config::LookUpBase(const std::string &name){
    auto it=getConfigInstance().find(name);
    return it==getConfigInstance().end()?nullptr:it->second;
}



void Config::LoadFromJson(const std::string& json_path){
    std::fstream data_stream;
    data_stream.open(json_path);
    if(!data_stream.is_open()){
        std::cout<<"load json file faild"<<std::endl;
        return;
    }
    json data_json;
    data_stream>>data_json;
    std::list<std::pair<std::string,json>>data_list;
    if(data_json.is_discarded()){
        std::cout<<"load json faild"<<std::endl;
    }

    getAllVars("",data_json,data_list);

    for(const auto &val:data_list){
        std::string name=val.first;
        if(name.empty())continue;
        std::transform(name.begin(),name.end(),name.begin(),::tolower);
        auto  it=LookUpBase(name);
        if(it!=nullptr){
            it->fromString(val.second.dump());
        }else{
           // std::cout<<name<<"    config undefine"<<std::endl;
        }
    }
}



void Config::getAllVars(std::string name,
                        json&json_data,
                        std::list<std::pair<std::string,json>>&list_data){
    for(json::iterator it=json_data.begin();it!=json_data.end();++it){
        if((!it->is_object()&&it->is_primitive()||it->is_array()))
            {
            list_data.push_back(std::make_pair(name+"."+it.key(),*it));
            continue;
        }else if(it->is_object()){
            list_data.push_back(std::make_pair(name+"."+it.key(),*it));
            getAllVars(name+"."+it.key(),*it,list_data);
        }
    }
}

struct initer{
    initer(){
        Itachi::Config::LoadFromJson("/home/lqf/cpp/configSystem/config.json");
    }
};



}

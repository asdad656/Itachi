/*
 * @Author: your name
 * @Date: 2022-03-02 13:58:32
 * @LastEditTime: 2022-03-05 00:43:46
 * @LastEditors: lqf
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \newProject\include\config.h
 */
#ifndef __CONFIG__H__
#define __CONFIG__H__
#include<json.hpp>
#include<memory>
#include<functional>
#include<mutex>
#include<map>
#include<vector>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<json.hpp>
#include<list>
#include<sstream>
#include<boost/lexical_cast.hpp>
#include<atomic>
#include<logger.h>
namespace Itachi{

class ConfigVarBase{
public:
    typedef std::shared_ptr<ConfigVarBase> ptr;
    ConfigVarBase(const std::string& name,const std::string&describtion="none"):
    m_name(name),
    m_describtion(describtion)
    {
    }
//-------------------get------------------------//
    const std::string& getName()const {return m_name;}
    const std::string& getDestribtion()const {return m_describtion;}
//--------------------set------------------------//
    void setName(const std::string& name){m_name=name;};
    void setDescribtion(const std::string& describtion){m_describtion=describtion;}
    virtual void fromString(const std::string&)=0;
    virtual std::string toString()const=0;
    
private:
    std::string m_name;
    std::string m_describtion;
};

//普通函数序列化
template<class To,class From>
class lexical_cast{
public:
    To operator()(const From &from){
        return boost::lexical_cast<To>(from);
    }
};

//string to vector特化
template<class T>
class lexical_cast<std::vector<T>,std::string>
{
public:
    std::vector<T> operator()(const std::string&From)const{
        nlohmann::json from=nlohmann::json::parse(From);
        std::vector<T> to;
        for(int i=0;i<from.size();++i){
            to.push_back(lexical_cast<T,std::string>()(from[i].dump()));
        }
        return to;
    }
};

//std::vector to string

template<class T>
class lexical_cast<std::string,std::vector<T>>
{
public:
    std::string operator()(const std::vector<T>& from)const{
            std::ostringstream iss;
            iss<<"[";
            for(int i=0;i<from.size();++i){
                iss<<lexical_cast<std::string,T>()(from[i]);
                if(i!=from.size()-1){
                    iss<<",";
                }else{
                    iss<<"]";
                }
            }
            if(from.size()==0){
                iss<<"]";
            }
            return iss.str();
    }
};


//string to list特化
template<class T>
class lexical_cast<std::list<T>,std::string>
{
public:
    std::list<T> operator()(const std::string&From)const{
        nlohmann::json from=nlohmann::json::parse(From);
        std::list<T> to;
        for(nlohmann::json::const_iterator it=from.cbegin();it!=from.cend();++it){
            to.push_back(lexical_cast<T,std::string>()(it->dump()));
        }
        return to;

    }
};

//std::list to string

template<class T>
class lexical_cast<std::string,std::list<T>>
{
public:
    std::string operator()(const std::list<T>& from){
            std::ostringstream iss;
            iss<<"[";
            for(const auto&val:from){
                iss<<lexical_cast<std::string,T>()(val)<<",";
            }
            std::string str=iss.str();
            *str.rbegin()=']';
            return str;
    }
};



//string to set
template<class T>
class lexical_cast<std::set<T>,std::string>
{
public:
    std::set<T> operator()(const std::string&From){
        nlohmann::json from=nlohmann::json::parse(From);
        std::set<T> to;
        for(nlohmann::json::const_iterator it=from.cbegin();it!=from.cend();++it){
            to.insert(lexical_cast<T,std::string>()(it->dump()));
        }
        return to;

    }
};

//std:set to string

template<class T>
class lexical_cast<std::string,std::set<T>>
{
public:
    std::string operator()(const std::set<T>& from){
            std::ostringstream iss;
            iss<<"[";
            for(const auto&val:from){
                iss<<lexical_cast<std::string,T>()(val)<<",";
            }
            std::string str=iss.str();
            *str.rbegin()=']';
            return str;
    }
};


//LogAppdenderToString
template<>
class lexical_cast<std::string,LogAppenderDefiner>
{
public:
    std::string operator()(const LogAppenderDefiner& from){
            return from.ToString();
    }
};

//json to LogAppender
template<>
class lexical_cast<LogAppenderDefiner,std::string>
{
public:
    LogAppenderDefiner operator()(const std::string&From){
        LogAppenderDefiner To;
        To.FromString(From);
        /*
    std::string m_name;
    std::string m_type;
    std::string m_filePath;
    std::string m_level;
    */
        return To;
    }
};


// template<class T>
// class changeCallBack{
// }
template<class T,class TOString=lexical_cast<std::string,T>,class FromString=lexical_cast<T,std::string>>
class ConfigVar : public ConfigVarBase{
public:
    typedef std::shared_ptr<ConfigVar> ptr;
    typedef std::function<void(const T&,const T&)> changeCallBack;
    typedef std::map<int8_t,changeCallBack>CallBacks;
    ConfigVar(const std::string &name,const T&default_value,
                const std::string &describtion=""):
    ConfigVarBase(name,describtion),
    m_var(default_value)
    {
        init();
    }
    void setVar(const T & var_value){
        if(var_value!=m_var){
            for(auto &val:m_cbs){
                val.second(m_var,var_value);
            }
            m_var=var_value;
        }
    }
    const T&getVar()const{return m_var;}
    std::string toString() const override{
        return TOString()(m_var);
    }
    void fromString(const std::string& string_value)override{
        setVar(FromString()(string_value));
    }
    void addCallBack(changeCallBack& cb){
        m_cbs[SerialNumbear]=std::move(cb);
    }
    void clearCallBack(){
        m_cbs.clear();
    }
    private:
    void init(){
        auto default_Callback=[this](const T&old_var,const T&new_var){
        std::cout<<"config name: "<<getName()
                    <<" change from: "<<TOString()(old_var)
                    <<" to " <<TOString()(new_var)<<std::endl;
        };
        m_cbs[SerialNumbear++]=default_Callback;
    }
private:
    T m_var;
    CallBacks m_cbs;
    std::atomic<int8_t>SerialNumbear{0};
    //默认的修改callback 

};

class Config{
public:
    typedef std::map<std::string,ConfigVarBase::ptr> ConfigData;
    template<class T>
    static typename ConfigVar<T>::ptr LookUp(const std::string Name,const T& default_value){
        std::string name=Name;
        std::transform(name.begin(),name.end(),name.begin(),::tolower);
        ConfigData& configData=getConfigInstance();
        ConfigData::iterator it=configData.find(name);
        if(it!=configData.end()){
            typename ConfigVar<T>::ptr casted=std::dynamic_pointer_cast<ConfigVar<T>>((it->second));
            if(casted==nullptr)
            {
                std::cout<<"config has been existed but type not match"<<std::endl;
                return nullptr;
            }
            else{
                std::cout<<"config has been existed "<<std::endl;
                return casted;
            }
        }
        typename ConfigVar<T>::ptr config(new  ConfigVar<T>(name,default_value));
        configData[name]=config;
        return config;
    }
    static ConfigVarBase::ptr LookUpBase(const std::string &name);
    static void LoadFromJson(const std::string& json_path);
    static void getAllVars(std::string name,
                            nlohmann::json&json_data,
                            std::list<std::pair<std::string,nlohmann::json>>&data);
    inline static size_t size(){
        return getConfigInstance().size();
    };
private:
    static ConfigData& getConfigInstance(){
        static ConfigData m_ConfigData;
        return m_ConfigData;
    }
    
    template<class T>
    auto decltypeUsedTest(T &continaar,std::string &name)->decltype(continaar()[name]){
        return continaar[name];
    }
};

}

#endif
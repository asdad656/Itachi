<!--
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-05 13:38:12
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-05 13:38:12
 * @Description: 
-->
# Itachi
Itachi网络库（参考muduo网络库，libevent网络库）

1.配置系统：
需求：只需要改变配置文件（config.json）即可完成对服务器的配置，例如 线程数量，日志器的种类和个数，监听端口等。
实现方式：
    1。抽象出所有项的属性，作为祖先
    2。继承祖先，使用模板进行泛化
    3.  对于泛化后的每一项，用仿函数对fromstring,tostring进行特化
    4. 用static 构造函数在main函之前构造的特性，完成在main函数之前的配置加载
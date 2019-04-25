#ifndef PARSER_H
#define PARSER_H
#include<string>
#include<fstream>
#include<iostream>
#include <regex>
using namespace std;
struct Result
{
    //判定结果结构体
    bool result=true;//判定结果
    string reason="";//语法错误原因，判定为true时为空
};
class parser
{
    //语法分析类
    public:
        parser();
        virtual ~parser();
        void is_arithmetic_ep();//判定是否是算术表达式
        void is_program();//判定是不是程序
        void readflag(string str,bool analysis_flag=false);//读取flagout.txt字符串并进行预处理
        //-------------表达式不带正负号--------------
        void ParseS();//表达式入口
        void ParseE();
        void ParseT();
        void ParseD();
        void ParseF();
        //---------------程序逻辑处理----------------
        void ParseP();//程序
        void ParseC();//常量说明
        void ParseCd();//常量定义
        void ParseV();//变量说明
        void ParseVd();//变量定义
        void ParseG();//过程说明
        void ParseY();//语句
        //-----------------错误处理？----------------
        void getsize(int size_i,int size_num);
        void wrong();
        void paren();
        void make_error(string errmsg);//错误处理
        void pop_word(string errmsg);//取出一个单词嘤，errmsg是取不出来报什么错哦


    protected:

    private:
        vector<string> items;//里面存储了一行表达式中各个item的种类
        string itemsnow;//当前item
        int i=0,sizei,start=0,num,flagparen;
        Result rt;
};

#endif // PARSER_H

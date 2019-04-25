#ifndef FLAG_H
#define FLAG_H
#include<string>
#include<map>
#include<fstream>
#include<iostream>
#include<vector>
using namespace std;
const string BASIC[]={"begin", "call", "const", "do", "end", "if", "odd", "procedure", "read", "then", "var", "while", "write"};
class flag//词法分析类
{
    public:
        flag();
        virtual ~flag();
        void analysis(string line,fstream &f);//分析函数
        void judge(string str,int fl,fstream &f);//根据fl进行字符串判别
        vector<int> getlinesize();

    protected:

    private:
         map<string,string> key;//存储种类关键词
         vector<int> linesize;//和语法分析相关，提供每一行的分词数

};

#endif // FLAG_H

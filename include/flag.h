#ifndef FLAG_H
#define FLAG_H
#include<string>
#include<map>
#include<fstream>
#include<iostream>
#include<vector>
using namespace std;
const string BASIC[]={"begin", "call", "const", "do", "end", "if", "odd", "procedure", "read", "then", "var", "while", "write"};
class flag//�ʷ�������
{
    public:
        flag();
        virtual ~flag();
        void analysis(string line,fstream &f);//��������
        void judge(string str,int fl,fstream &f);//����fl�����ַ����б�
        vector<int> getlinesize();

    protected:

    private:
         map<string,string> key;//�洢����ؼ���
         vector<int> linesize;//���﷨������أ��ṩÿһ�еķִ���

};

#endif // FLAG_H

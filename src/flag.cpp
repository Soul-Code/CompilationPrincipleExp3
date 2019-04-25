#include "flag.h"
flag::flag()
{
    //map��ʼ��,�������
    key["ident"]="ident";
    key["number"]="number";
    key["begin"]="beginsym";
    key["call"]="callsym";
    key["const"]="constsym";
    key["do"]="dosym";
    key["end"]="endsym";
    key["if"]="ifsym";
    key["odd"]="oddsym";
    key["procedure"]="porceduresym";
    key["read"]="readsym";
    key["then"]="thensym";
    key["var"]="varsym";
    key["while"]="whilesym";
    key["write"]="writesym";
    key["+"]="plus";
    key["-"]="minus";
    key["*"]="times";
    key["/"]="slash";
    key["="]="eql";
    key["#"]="neq";
    key["<"]="lss";
    key["<="]="leq";
    key[">"]="gtr";
    key[">="]="geq";
    key[":="]="becomes";
    key["("]="lparen";
    key[")"]="rparen";
    key[","]="comma";
    key[";"]="semicolon";
    key["."]="period";
    key["nul"]="nul";
}

flag::~flag()
{

}
void flag::analysis(string line,fstream &fout)
{
    int ls=0;//�����������˼�ǡ���linesize��
    int fl=0;
    string str = "";
    string::iterator iter = line.begin();
    for(;iter<=line.end();iter++)
    {
        char a = *iter;

        //��ĸ��д��ΪСд
        if(a>=65&&a<=90)
        {
            a=a+32;
        }

        if(str.size()==0)
            {
                //��ƥ���ַ���Ϊ��ʱ�����ݵ�һ���ַ������ַ�������
                if(a>=97&&a<=122)
                {
                    //��1����ʶ����ؼ�����
                    str+=a;
                    fl=1;

                }
                else if(a>=48&&a<=57)
                {
                    //��2��������
                    str+=a;
                    fl=2;
                }
                else
                {
                    if(a=='+'||a=='-'||a=='*'||a=='/'||a=='='||a=='#'||a=='('||a==')'||a==','||a==';'||a=='.')
                    {
                        //��3��������
                        str+=a;
                        fl=3;
                    }
                    else if (a==':'||a=='<'||a=='>')
                    {
                        //��4���������к�����=��
                        str+=a;
                        fl=4;

                    }
                    else
                    {
                        if(a!=32)
                        {
                            //��5���ų��ո��ʣ�µľ�Ϊ�Ƿ��ַ�
                            str+=a;
                            fl=5;
                        }

                    }
                }
            }
            else
            {
                //��ƥ���ַ��������Ѿ���
                if(a>=97&&a<=122&&fl==1)
                {
                    //�ַ�ΪСд��ĸ�����ַ�������Ϊ��ʶ����ؼ�����
                    str+=a;
                }
                else if(a>=48&&a<=57&&(fl==1||fl==2))
                {
                    //�ַ�Ϊ���ֲ����ַ�������Ϊ��ʶ����ؼ������������
                    str+=a;
                }
                else if(a==61&&fl==4)
                {
                    //�ַ�Ϊ=�����ַ�������Ϊ:=,<=,>=
                    str+=a;
                }
                else
                {
                    judge(str,fl,fout);
                    ls++;
                    fl=0;
                    str="";
                    iter--;
                }
            }
    }
    linesize.push_back(ls);



}
void flag::judge(string str,int fl,fstream &f)
{
    if(fl==1)
    {
        for(int i=0;i<13;i++)
            {
                //�б��Ƿ�Ϊ�ؼ���
                    if(BASIC[i]==str)
                    {
                        //cout<<"("<<key[str]<<","<<str<<")"<<endl;
                        f<<"("<<key[str]<<","<<str<<")"<<endl;
                        return;
                    }
            }
        //cout<<"("<<key["ident"]<<","<<str<<")"<<endl;
        f<<"("<<key["ident"]<<","<<str<<")"<<endl;
    }
    if(fl==2)
    {
        //cout<<"("<<key["number"]<<","<<str<<")"<<endl;
        f<<"("<<key["number"]<<","<<str<<")"<<endl;
    }
    if(fl==3)
    {
        //cout<<"("<<key[str]<<","<<str<<")"<<endl;
        f<<"("<<key[str]<<","<<str<<")"<<endl;
    }
    if(fl==4&&str!=":")
    {
        //cout<<"("<<key[str]<<","<<str<<")"<<endl;
        f<<"("<<key[str]<<","<<str<<")"<<endl;
    }
    if(fl==5||str==":")
    {
        //cout<<"("<<key["nul"]<<","<<str<<")"<<endl;
        f<<"("<<key["nul"]<<","<<str<<")"<<endl;
    }
    return;

}
vector<int> flag::getlinesize()
{
    return linesize;
}

#include "flag.h"
flag::flag()
{
    //map初始化,方便输出
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
    int ls=0;//这个变量的意思是……linesize？
    int fl=0;
    string str = "";
    string::iterator iter = line.begin();
    for(;iter<=line.end();iter++)
    {
        char a = *iter;

        //字母大写变为小写
        if(a>=65&&a<=90)
        {
            a=a+32;
        }

        if(str.size()==0)
            {
                //待匹配字符串为空时，根据第一个字符决定字符串性质
                if(a>=97&&a<=122)
                {
                    //类1：标识符与关键字类
                    str+=a;
                    fl=1;

                }
                else if(a>=48&&a<=57)
                {
                    //类2：数字类
                    str+=a;
                    fl=2;
                }
                else
                {
                    if(a=='+'||a=='-'||a=='*'||a=='/'||a=='='||a=='#'||a=='('||a==')'||a==','||a==';'||a=='.')
                    {
                        //类3：其他类
                        str+=a;
                        fl=3;
                    }
                    else if (a==':'||a=='<'||a=='>')
                    {
                        //类4：其他类中后面会跟=的
                        str+=a;
                        fl=4;

                    }
                    else
                    {
                        if(a!=32)
                        {
                            //类5：排除空格后剩下的均为非法字符
                            str+=a;
                            fl=5;
                        }

                    }
                }
            }
            else
            {
                //待匹配字符串性质已决定
                if(a>=97&&a<=122&&fl==1)
                {
                    //字符为小写字母并且字符串类型为标识符与关键字类
                    str+=a;
                }
                else if(a>=48&&a<=57&&(fl==1||fl==2))
                {
                    //字符为数字并且字符串类型为标识符与关键字类或数字类
                    str+=a;
                }
                else if(a==61&&fl==4)
                {
                    //字符为=并且字符串类型为:=,<=,>=
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
                //判别是否为关键字
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

#include <iostream>
#include<fstream>
#include<flag.h>
#include<parser.h>
using namespace std;
flag fg;
parser ps;
void read_pl0_file()
{
    //打开文件
    fstream myfile("test.txt");//输入文件？我的文件？
    fstream fgout("flagout.txt");//输出字符流
    fstream psin("flagout.txt");//读入字符流
    string temp;
    if (!myfile.is_open()||!fgout.is_open()||!psin.is_open())
    {
        cout << "未成功打开文件" << endl;
        //未成功打开应该return-1？反正不应该继续执行来着
    }
    while(getline(myfile,temp))
    {
        fg.analysis(temp,fgout);
    }
    vector<int> ls=fg.getlinesize();//读取每行的长度
    cout<<"一共有"<<ls.size()<<"行数据哦"<<endl;//输出行数
    for(int i=0; i<ls.size(); i++)
    {
        //循环每行
        int size_num=1;
        for(int a=0; a<i; a++)
        {
            size_num = size_num + ls[a];
        }
        //  cout<<size_num<<"   "<<ls[0]<<endl;
        ps.getsize(ls[i],size_num);//大概是把当前解析光标置于指定位置
        cout<<"**********NO."<<i+1<<" expression************"<<endl;
        for(int j=0; j<ls[i]; j++)
        {
            getline(psin,temp);//读文件行
            if(j==(ls[i]-1))
            {
                ps.readflag(temp,true);
            }
            else
            {
                ps.readflag(temp);
            }
        }
    }

    myfile.close();
    fgout.close();
    psin.close();

}
int main()
{
    read_pl0_file();
    return 0;
}

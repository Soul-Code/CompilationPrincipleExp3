#include <iostream>
#include<fstream>
#include<flag.h>
#include<parser.h>
using namespace std;
flag fg;
parser ps;
void read_pl0_file()
{
    //���ļ�
    fstream myfile("test.txt");//�����ļ����ҵ��ļ���
    fstream fgout("flagout.txt");//����ַ���
    fstream psin("flagout.txt");//�����ַ���
    string temp;
    if (!myfile.is_open()||!fgout.is_open()||!psin.is_open())
    {
        cout << "δ�ɹ����ļ�" << endl;
        //δ�ɹ���Ӧ��return-1��������Ӧ�ü���ִ������
    }
    while(getline(myfile,temp))
    {
        fg.analysis(temp,fgout);
    }
    vector<int> ls=fg.getlinesize();//��ȡÿ�еĳ���
    cout<<"һ����"<<ls.size()<<"������Ŷ"<<endl;//�������
    for(int i=0; i<ls.size(); i++)
    {
        //ѭ��ÿ��
        int size_num=1;
        for(int a=0; a<i; a++)
        {
            size_num = size_num + ls[a];
        }
        //  cout<<size_num<<"   "<<ls[0]<<endl;
        ps.getsize(ls[i],size_num);//����ǰѵ�ǰ�����������ָ��λ��
        cout<<"**********NO."<<i+1<<" expression************"<<endl;
        for(int j=0; j<ls[i]; j++)
        {
            getline(psin,temp);//���ļ���
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

#include "parser.h"

parser::parser()
{
    //ctor
}

parser::~parser()
{
    //dtor
}
void parser::getsize(int size_i,int size_num)
{
    //
    i=size_num-1;
    start=i;
    sizei=size_i+i;
}
void parser::wrong()
{
    vector<string> key;
    //�ؼ���0-12
    key.push_back("beginsym");
    key.push_back("callsym");
    key.push_back("constsym");
    key.push_back("dosym");
    key.push_back("endsym");
    key.push_back("ifsym");
    key.push_back("oddsym");
    key.push_back("readsym");
    key.push_back("thensym");
    key.push_back("varsym");
    key.push_back("whilesym");
    key.push_back("writesym");
    key.push_back("porceduresym");
    //���ܳ��ֵ������ַ�13-21
    key.push_back("neq");
    key.push_back("lss");
    key.push_back("leq");
    key.push_back("gtr");
    key.push_back("geq");
    key.push_back("becomes");
    key.push_back("semicolon");
    key.push_back("lss");
    key.push_back("period");
    //����������22-28
    key.push_back("plus");
    key.push_back("minus");
    key.push_back("times");
    key.push_back("slash");
    key.push_back("eql");
    key.push_back("lparen");
    key.push_back("rparen");
    int j;
    //�ж��Ƿ�Ϊ�ؼ���
    for(j=0; j<22; j++)
    {
        if(key[j]==items[i])
            break;
    }
    //�ж��Ƿ�Ϊ���ʽ�в��ܳ��ֵ������ַ���ؼ���
    if(j<22)
    {
        rt.reason=items[i]+" cannot appear in the expression";
    }
    else if(i==sizei-1)
    {
        rt.reason="The ending cannot be the "+items[i];
    }
}
void parser::make_error(string errmsg)
{
    rt.result=false;
    if(i>sizei)
        i=sizei-1;
    wrong();
    cout<<errmsg<<endl;
    cout<<errmsg<<endl;
//    if(rt.reason!="") {}
//    else
//    {
        int tempcount=i-start;
        stringstream temps;
        temps<<tempcount;
        string temp=temps.str();
        rt.reason="�� "+temp+" �����ʴ�������."+errmsg;
//    }

}
void parser::pop_word(string errmsg)
{
    if(i<sizei-1)
    {
        //��ջһ������
        i++;
        itemsnow=items[i];
    }
    else
    {
        itemsnow="#";
        i++;
        cout<<errmsg<<"  "<<itemsnow<<endl;
    }
}

//--------------------���ʽ����
void parser::ParseS()
{
    if(itemsnow=="lparen"||itemsnow=="ident"||itemsnow=="number")
    {
        //������/��ʶ��/���� ����������<����>
        cout<<"����S����T"<<endl;
        ParseT();
        cout<<"�˻�S����E"<<endl;
        ParseE();
        cout<<"�˳�S"<<endl;
    }
    else
    {
        rt.result=false;
        if(i>sizei)
            i=sizei-1;
        cout<<"S����"<<itemsnow<<endl;
        wrong();
        if(rt.reason!="") {}
        else
        {
            int tempcount=i-start;
            stringstream temps;
            temps<<tempcount;
            string temp=temps.str();
            rt.reason="The "+temp+" position of the expression needs to be ident,number or lparen";
        }
    }
}
void parser::ParseT()
{
    if(itemsnow=="lparen"||itemsnow=="ident"||itemsnow=="number")
    {
        //������/��ʶ��/���� ����������<����>
        cout<<"����T����F"<<endl;
        ParseF();
        cout<<"�˻�T����D"<<endl;
        ParseD();
        cout<<"�˳�T"<<endl;
    }
    else
    {
        rt.result=false;
        if(i>=sizei)
            i=sizei-1;
        cout<<"T����"<<itemsnow<<items[i]<<endl;
        wrong();
        if(rt.reason!="") {}
        else
        {
            int tempcount=i-start;
            stringstream temps;
            temps<<tempcount;
            string temp=temps.str();
            rt.reason="The "+temp+" position of the expression needs to be ident,number or lparen";
        }
    }
}
void parser::ParseF()
{
    cout<<"����F"<<endl;
    if(itemsnow=="ident")
    {
        if(i<sizei-1)
        {
            i++;
            itemsnow=items[i];
        }
        else
        {
            itemsnow="#";
            i++;
        }
    }
    else if(itemsnow=="number")
    {
        if(i<sizei-1)
        {
            i++;
            itemsnow=items[i];
        }
        else
        {
            itemsnow="#";
            i++;
        }
    }
    else if(itemsnow=="lparen")
    {
        if(i<sizei-1)
        {
            i++;
            itemsnow=items[i];
        }
        else
        {
            itemsnow="#";
            i++;
        }
        cout<<"F����S"<<endl;
        ParseS();
        cout<<"�˳�S�˻�F"<<endl;
        // i++;
        // itemsnow=items[i];
        if(itemsnow=="rparen")
        {
            if(i<sizei-1)
            {
                i++;
                itemsnow=items[i];
            }
            else
            {
                itemsnow="#";
                i++;
            }
        }
        else
        {
            cout<<"���ʽS����ӣ�"<<itemsnow<<endl;
            rt.result=false;
            int tempcount=i-start;
            stringstream temps;
            temps<<tempcount;
            string temp=temps.str();
            rt.reason="you need rparlen at the "+temp+" position after expression";
        }
    }
    else
    {
        rt.result=false;
        if(i>=sizei)
            i=sizei-1;
        wrong();
        cout<<"F��ͷ����"<<endl;
        if(rt.reason!="") {}
        else
        {
            int tempcount=i-start;
            stringstream temps;
            temps<<tempcount;
            string temp=temps.str();
            rt.reason="The "+temp+" position of the expression needs to be ident,number or lparen";
        }
    }
    cout<<"�˳�F"<<endl;

}
void parser::ParseE()
{
    cout<<"����E"<<endl;
    if(itemsnow=="plus"||itemsnow=="minus")
    {
        if(i<sizei-1)
        {
            i++;
            itemsnow=items[i];
        }
        else
        {
            itemsnow="#";
            i++;
        }
        cout<<"��E����T"<<endl;
        ParseT();
        cout<<"��T�˻�E����E"<<endl;
        ParseE();
        cout<<"��E�˻�E����"<<endl;
    }
    else if(itemsnow=="rparen"||itemsnow=="#")
    {
    }
    else
    {
        rt.result=false;
        cout<<"E����"<<endl;
        if(i>=sizei)
            i=sizei-1;
        wrong();
        if(rt.reason!="") {}
        else
        {
            int tempcount=i-start;
            stringstream temps;
            temps<<tempcount;
            string temp=temps.str();
            rt.reason="The "+temp+" position of the expression needs to be plus,minus or rparen";
        }
    }
}
void parser::ParseD()
{
    cout<<"����D"<<endl;
    if(itemsnow=="plus"||itemsnow=="minus"||itemsnow=="rparen"||itemsnow=="#")
    {
        //��+ ��- �����ţ�����Ϊ
    }
    else if(itemsnow=="times"||itemsnow=="slash")
    {
        //�˳�
        if(i<sizei-1)
        {
            i++;
            itemsnow=items[i];
        }
        else
        {
            itemsnow="#";
            i++;
            cout<<"�����Գ˳��Ž�β"<<itemsnow<<endl;
        }
        cout<<"��D����F"<<endl;
        ParseF();
        cout<<"��F�˻�D����D"<<endl;
        ParseD();
        cout<<"��D�˻�D����"<<endl;
    }
    else
    {
        rt.result=false;
        cout<<"D����"<<endl;
        if(i>=sizei)
            i=sizei-1;
        wrong();
        if(rt.reason!="") {}
        else
        {
            int tempcount=i-start;
            stringstream temps;
            temps<<tempcount;
            string temp=temps.str();
            rt.reason="The "+temp+" position of the expression needs to be plus,minus��times or slash";
        }

    }
    cout<<"�˳�D"<<endl;
}
//----------------------------------���򲿷�
void parser::ParseP()
{
    cout<<"����P "<<itemsnow<<endl;
    if(itemsnow=="constsym")
    {
        cout<<"����C "<<itemsnow<<endl;
        ParseC();
    }
    if(itemsnow=="varsym")
    {
        cout<<"����V "<<itemsnow<<endl;
        ParseV();
    }
    if(itemsnow=="proceduresym")
    {
        cout<<"����G "<<itemsnow<<endl;
        ParseG();
    }
    //todo:���Ĵ���
}
void parser::ParseC()
{
    if(itemsnow=="constsym")
    {
        if(i<sizei-1)
        {
            //��ջһ������
            i++;
            itemsnow=items[i];
        }
        else
        {
            itemsnow="#";
            i++;
            cout<<"������const��β"<<itemsnow<<endl;
        }
        cout<<"����Cd "<<itemsnow<<endl;
        ParseCd();
    }
    if(itemsnow=="semicolon")
    {
        itemsnow="#";
        i++;
    }
    else
    {
        make_error("Ӧ���ԷֺŽ�β��");
    }
    cout<<"�˳�C"<<endl;
}

void parser::ParseCd()
{
    if(itemsnow=="ident")
    {
        pop_word("������ident��βŶ");
        if(itemsnow=="eql")
        {
            pop_word("������eql��βŶ");
            if(itemsnow=="number")
            {
                pop_word("������number��βŶ");
            }
            else
            {
                make_error("���������е��ںź�����������");
            }
        }
        else
        {
            make_error("���������б�ʶ���������ӵ��ں�");
        }
    }
    if(itemsnow=="comma")
    {
        //�Ѷ����ó���
        if(i<sizei-1)
        {
            //��ջһ������
            i++;
            itemsnow=items[i];
        }
        else
        {
            itemsnow="#";
            i++;
            cout<<"�����Զ��Ž�β"<<itemsnow<<endl;
        }
        cout<<"�ٴν���Cd "<<itemsnow<<endl;
        ParseCd();
    }
    cout<<"�˳�Cd"<<endl;

}
void parser::ParseV()
{

    if(itemsnow=="varsym")
    {
        //��var�ó���
        pop_word("������var��β");
        cout<<"����Vd "<<itemsnow<<endl;
        ParseVd();
    }

    if(itemsnow=="semicolon")
    {
        itemsnow="#";
        i++;
    }
    else
    {
        make_error("Ӧ���ԷֺŽ�β��");
    }
    cout<<"�˳�V"<<endl;
}
void parser::ParseVd()
{
    if(itemsnow=="ident")
    {
        pop_word("������ident��β");
        if(itemsnow=="comma")
        {
            //�Ѷ����ó���
            pop_word("�����Զ��Ž�βŶ");
            cout<<"�ٴν���Vd "<<itemsnow<<endl;
            ParseVd();
        }
    }
    else
    {
        make_error("var���������ident��ͷ");
    }
    cout<<"�˳�Vd "<<itemsnow<<endl;
}
void parser::ParseG()
{

    if(itemsnow=="proceduresym")
    {
        //ȡ�����̱�ʶ��
        if(i<sizei-1)
        {
            //��ջһ������
            i++;
            itemsnow=items[i];
        }
        else
        {
            itemsnow="#";
            i++;
            cout<<"�����Թ��̱�ʶ����β"<<itemsnow<<endl;
        }
        if(itemsnow=="ident")
        {
            if(i<sizei-1)
            {
                //��ջһ������
                i++;
                itemsnow=items[i];
            }
            else
            {
                itemsnow="#";
                i++;
                cout<<"�����Թ����ײ���β"<<itemsnow<<endl;
            }
        }
    }

    if(itemsnow=="semicolon")
    {
        itemsnow="#";
        i++;
    }
    else
    {
        make_error("Ӧ���ԷֺŽ�β��");
    }
}
void parser::ParseY()
{

}

void parser::paren()
{
    //�⿴����������һ������Ĵ���
    int countparen=0;
    for(int j=start; j<=sizei-1; j++)
    {
        if(items[j]=="lparen"||items[j]=="rparen")
            countparen++;
    }
    if(countparen%2!=0)
    {
        rt.result=false;
        rt.reason="you need '(' before ')'";
    }

}

void parser::is_arithmetic_ep()
{
    //items�������ĵ���ȡ��ĸ���item
    //����ԭ�����ļ�Ϊ1+2,��items[0]=number,items[1]=plus,items[2]=number
    //����������ʽ�ж��ɹ���������rt.result=true,rt.reason=""
    //���ʧ�ܣ�������rt.result=false,reason=�����ַ�����PS�����ɸ�Ӣ�İɣ����ĺ��������Щ����
    itemsnow=items[i];
    rt.reason="";
    rt.result=true;
    flagparen=1;
    //������ǳ��������ˣ�
    ParseS();
    //����һ�ִ���
    if(rt.result)
        paren();


    //Result rt;

    // for(int j=start;j<=sizei-1;j++)
    //  cout<<items[j]<<" ";
    //rt.result=false;
    //rt.reason="nonodayou";
//    return rt;


}

void parser::is_program()
{

    //items�������ĵ���ȡ��ĸ���item
    //����ԭ�����ļ�Ϊ1+2,��items[0]=number,items[1]=plus,items[2]=number
    //����������ʽ�ж��ɹ���������rt.result=true,rt.reason=""
    //���ʧ�ܣ�������rt.result=false,reason=�����ַ�����PS�����ɸ�Ӣ�İɣ����ĺ��������Щ����
    itemsnow=items[i];
    rt.reason="";
    rt.result=true;
    flagparen=1;
    ParseP();
    //����һ�ִ���
    if(rt.result)
        paren();
}


void parser::readflag(string str,bool analysis_flag)
{
    //������ʽ��ȡÿһ�ִʵ�����
    regex r("[(][a-z]*,");//������ʽ
    smatch sm;
    for(auto it=str.cbegin(); regex_search(it,str.cend(),sm,r); it=sm.suffix().first)
    {
        for(auto aa:sm)
        {
            string x=aa.str();
            string a;
            a.assign(x,1,x.length()-2);
            cout<<a<<endl;
            items.push_back(a);//ȥ��ĩβ����
            //cout<<items[0]<<endl;
        }

    }
    if(analysis_flag)
    {

//        is_arithmetic_ep();
        is_program();
        if(rt.result)
        {
            cout<<"no error"<<endl;
        }
        else
        {
            cout<<"error"<<endl;
            cout<<rt.reason<<endl;

        }
        //cout<<items[7]<<endl;
    }

}

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
    //关键字0-12
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
    //不能出现的其他字符13-21
    key.push_back("neq");
    key.push_back("lss");
    key.push_back("leq");
    key.push_back("gtr");
    key.push_back("geq");
    key.push_back("becomes");
    key.push_back("semicolon");
    key.push_back("lss");
    key.push_back("period");
    //算数符或界符22-28
    key.push_back("plus");
    key.push_back("minus");
    key.push_back("times");
    key.push_back("slash");
    key.push_back("eql");
    key.push_back("lparen");
    key.push_back("rparen");
    int j;
    //判断是否为关键字
    for(j=0; j<22; j++)
    {
        if(key[j]==items[i])
            break;
    }
    //判断是否为表达式中不能出现的其他字符或关键字
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
        rt.reason="第 "+temp+" 个单词处有问题."+errmsg;
//    }

}
void parser::pop_word(string errmsg)
{
    if(i<sizei-1)
    {
        //出栈一个单词
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

//--------------------表达式部分
void parser::ParseS()
{
    if(itemsnow=="lparen"||itemsnow=="ident"||itemsnow=="number")
    {
        //左括号/标识符/数字 那这个大概是<因子>
        cout<<"经过S进入T"<<endl;
        ParseT();
        cout<<"退回S进入E"<<endl;
        ParseE();
        cout<<"退出S"<<endl;
    }
    else
    {
        rt.result=false;
        if(i>sizei)
            i=sizei-1;
        cout<<"S错误"<<itemsnow<<endl;
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
        //左括号/标识符/数字 那这个大概是<因子>
        cout<<"经过T进入F"<<endl;
        ParseF();
        cout<<"退回T进入D"<<endl;
        ParseD();
        cout<<"退出T"<<endl;
    }
    else
    {
        rt.result=false;
        if(i>=sizei)
            i=sizei-1;
        cout<<"T错误"<<itemsnow<<items[i]<<endl;
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
    cout<<"进入F"<<endl;
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
        cout<<"F进入S"<<endl;
        ParseS();
        cout<<"退出S退回F"<<endl;
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
            cout<<"表达式S后需加）"<<itemsnow<<endl;
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
        cout<<"F开头错误"<<endl;
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
    cout<<"退出F"<<endl;

}
void parser::ParseE()
{
    cout<<"进入E"<<endl;
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
        cout<<"从E进入T"<<endl;
        ParseT();
        cout<<"从T退回E进入E"<<endl;
        ParseE();
        cout<<"从E退回E结束"<<endl;
    }
    else if(itemsnow=="rparen"||itemsnow=="#")
    {
    }
    else
    {
        rt.result=false;
        cout<<"E错误"<<endl;
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
    cout<<"进入D"<<endl;
    if(itemsnow=="plus"||itemsnow=="minus"||itemsnow=="rparen"||itemsnow=="#")
    {
        //加+ 减- 右括号）不作为
    }
    else if(itemsnow=="times"||itemsnow=="slash")
    {
        //乘除
        if(i<sizei-1)
        {
            i++;
            itemsnow=items[i];
        }
        else
        {
            itemsnow="#";
            i++;
            cout<<"不能以乘除号结尾"<<itemsnow<<endl;
        }
        cout<<"从D进入F"<<endl;
        ParseF();
        cout<<"从F退回D进入D"<<endl;
        ParseD();
        cout<<"从D退回D结束"<<endl;
    }
    else
    {
        rt.result=false;
        cout<<"D错误"<<endl;
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
            rt.reason="The "+temp+" position of the expression needs to be plus,minus，times or slash";
        }

    }
    cout<<"退出D"<<endl;
}
//----------------------------------程序部分
void parser::ParseP()
{
    cout<<"进入P "<<itemsnow<<endl;
    if(itemsnow=="constsym")
    {
        cout<<"进入C "<<itemsnow<<endl;
        ParseC();
    }
    if(itemsnow=="varsym")
    {
        cout<<"进入V "<<itemsnow<<endl;
        ParseV();
    }
    if(itemsnow=="proceduresym")
    {
        cout<<"进入G "<<itemsnow<<endl;
        ParseG();
    }
    //todo:语句的处理、
}
void parser::ParseC()
{
    if(itemsnow=="constsym")
    {
        if(i<sizei-1)
        {
            //出栈一个单词
            i++;
            itemsnow=items[i];
        }
        else
        {
            itemsnow="#";
            i++;
            cout<<"不能以const结尾"<<itemsnow<<endl;
        }
        cout<<"进入Cd "<<itemsnow<<endl;
        ParseCd();
    }
    if(itemsnow=="semicolon")
    {
        itemsnow="#";
        i++;
    }
    else
    {
        make_error("应该以分号结尾呢");
    }
    cout<<"退出C"<<endl;
}

void parser::ParseCd()
{
    if(itemsnow=="ident")
    {
        pop_word("不能以ident结尾哦");
        if(itemsnow=="eql")
        {
            pop_word("不能以eql结尾哦");
            if(itemsnow=="number")
            {
                pop_word("不能以number结尾哦");
            }
            else
            {
                make_error("常量定义中等于号后面必须加整数");
            }
        }
        else
        {
            make_error("常量定义中标识符后面必须加等于号");
        }
    }
    if(itemsnow=="comma")
    {
        //把逗号拿出来
        if(i<sizei-1)
        {
            //出栈一个单词
            i++;
            itemsnow=items[i];
        }
        else
        {
            itemsnow="#";
            i++;
            cout<<"不能以逗号结尾"<<itemsnow<<endl;
        }
        cout<<"再次进入Cd "<<itemsnow<<endl;
        ParseCd();
    }
    cout<<"退出Cd"<<endl;

}
void parser::ParseV()
{

    if(itemsnow=="varsym")
    {
        //把var拿出来
        pop_word("不能以var结尾");
        cout<<"进入Vd "<<itemsnow<<endl;
        ParseVd();
    }

    if(itemsnow=="semicolon")
    {
        itemsnow="#";
        i++;
    }
    else
    {
        make_error("应该以分号结尾呢");
    }
    cout<<"退出V"<<endl;
}
void parser::ParseVd()
{
    if(itemsnow=="ident")
    {
        pop_word("不能以ident结尾");
        if(itemsnow=="comma")
        {
            //把逗号拿出来
            pop_word("不能以逗号结尾哦");
            cout<<"再次进入Vd "<<itemsnow<<endl;
            ParseVd();
        }
    }
    else
    {
        make_error("var定义必须以ident开头");
    }
    cout<<"退出Vd "<<itemsnow<<endl;
}
void parser::ParseG()
{

    if(itemsnow=="proceduresym")
    {
        //取出过程标识符
        if(i<sizei-1)
        {
            //出栈一个单词
            i++;
            itemsnow=items[i];
        }
        else
        {
            itemsnow="#";
            i++;
            cout<<"不能以过程标识符结尾"<<itemsnow<<endl;
        }
        if(itemsnow=="ident")
        {
            if(i<sizei-1)
            {
                //出栈一个单词
                i++;
                itemsnow=items[i];
            }
            else
            {
                itemsnow="#";
                i++;
                cout<<"不能以过程首部结尾"<<itemsnow<<endl;
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
        make_error("应该以分号结尾呢");
    }
}
void parser::ParseY()
{

}

void parser::paren()
{
    //这看起来好像是一个报错的处理
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
    //items包含了文档读取后的各个item
    //比如原测试文件为1+2,则items[0]=number,items[1]=plus,items[2]=number
    //如果算术表达式判定成功，请设置rt.result=true,rt.reason=""
    //如果失败，请设置rt.result=false,reason=理由字符串，PS：理由给英文吧，中文好像程序有些问题
    itemsnow=items[i];
    rt.reason="";
    rt.result=true;
    flagparen=1;
    //这可能是程序的入口了？
    ParseS();
    //处理一种错误
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

    //items包含了文档读取后的各个item
    //比如原测试文件为1+2,则items[0]=number,items[1]=plus,items[2]=number
    //如果算术表达式判定成功，请设置rt.result=true,rt.reason=""
    //如果失败，请设置rt.result=false,reason=理由字符串，PS：理由给英文吧，中文好像程序有些问题
    itemsnow=items[i];
    rt.reason="";
    rt.result=true;
    flagparen=1;
    ParseP();
    //处理一种错误
    if(rt.result)
        paren();
}


void parser::readflag(string str,bool analysis_flag)
{
    //正则表达式提取每一分词的种类
    regex r("[(][a-z]*,");//正则表达式
    smatch sm;
    for(auto it=str.cbegin(); regex_search(it,str.cend(),sm,r); it=sm.suffix().first)
    {
        for(auto aa:sm)
        {
            string x=aa.str();
            string a;
            a.assign(x,1,x.length()-2);
            cout<<a<<endl;
            items.push_back(a);//去掉末尾逗号
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

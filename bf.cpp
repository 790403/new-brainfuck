#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxsize 10000000
int turemem[maxsize];
int ptr;
stack<int> whiles,ifs;
string a="";
int i;
int&mem(int aa){
    if(aa<0||aa>=10000000){
        cerr<<"\n在第"<<i+1<<"个字符指针越界\n";
        throw runtime_error("指针越界");
    }
    return turemem[aa];
}
void getnum(int&num,bool&isaddr,bool&hasnum,int&i){
    num=0;
    isaddr=0;
    hasnum=0;
    int aaa=1;
    if(a[i+1]=='@')isaddr=1,i++,hasnum=1;
    if(a[i+1]=='-')i++,hasnum=1,aaa=-1;
    while(a[i+1]>='0'&&a[i+1]<='9')num*=10,num+=a[i+1]-'0',i++,hasnum=1;
    num*=aaa;
    if(!hasnum)num=1;
    if(isaddr){
        if(num<0||num>=maxsize){
            cerr<<"\n在第"<<i+1<<"个字符指针越界\n";
            throw runtime_error("指针越界");
        }
        num=mem(num);
    }
}
signed main(signed argc,char* argv[]){
    try{
        system("chcp 65001 >nul");
        if(argc==3&&strcmp(argv[1],"-f")==0){
            ifstream file(argv[2]);
            string b((istreambuf_iterator<char>(file)),istreambuf_iterator<char>());
            a=b;
        }else if(argc==3&&strcmp(argv[1],"-c")==0){
            a=argv[2];
        }else{
            cout<<"用-f打开文件\n用-c直接运行单行代码";
            return 0;
        }
        string ans="";
        for(int i=0;i<a.size();i++){
            if(a[i]=='+'){
                int count=1;
                while(i+1<a.size()&&a[i+1]=='+')count++,i++;
                if(count>1)ans+="+"+to_string(count);
                else ans+="+";
            }else if(a[i]=='-'){
                int count=1;
                while(i+1<a.size()&&a[i+1]=='-')count++,i++;
                if(count>1)ans+="-"+to_string(count);
                else ans+="-";
            }else if(a[i]=='>'){
                int count=1;
                while(i+1<a.size()&&a[i+1]=='>')count++,i++;
                if(count>1)ans+=">"+to_string(count);
                else ans+=">";
            }else if(a[i]=='<'){
                int count=1;
                while(i+1<a.size()&&a[i+1]=='<')count++,i++;
                if(count>1)ans+="<"+to_string(count);
                else ans+="<";
            }else ans+=a[i];
        }
        a=ans;
        a+='\n';
        for(i=0;i<a.size();i++){
            int num;
            bool isaddr,hasnum;
            switch(a[i]){
                case '>':
                    getnum(num,isaddr,hasnum,i);
                    if(ptr+num<maxsize)ptr+=num;
                    else{
                        cerr<<"\n在第"<<i+1<<"个字符的数组访问超过了最大值\n";
                        throw runtime_error("数组访问超过了最大值");
                    }
                    break;
                case '<':
                    getnum(num,isaddr,hasnum,i);
                    if(ptr-num>=0)ptr-=num;
                    else{
                        cerr<<"\n在第"<<i+1<<"个字符的数组访问小于了0\n";
                        throw runtime_error("数组访问小于了0");
                    }
                    break;
                case '+':
                    getnum(num,isaddr,hasnum,i);
                    mem(ptr)+=num;
                    break;
                case '-':
                    getnum(num,isaddr,hasnum,i);
                    mem(ptr)-=num;
                    break;
                case '*':
                    getnum(num,isaddr,hasnum,i);
                    mem(ptr)*=num;
                    break;
                case '/':
                    getnum(num,isaddr,hasnum,i);
                    if(num==0){
                        cerr<<"\n在第"<<i+1<<"个字符,除数不能为零\n";
                        throw runtime_error("除数不能为零");
                    }
                    mem(ptr)/=num;
                    break;
                case '%':
                    getnum(num,isaddr,hasnum,i);
                    if(num==0){
                        cerr<<"\n在第"<<i+1<<"个字符,除数不能为零\n";
                        throw runtime_error("除数不能为零");
                    }
                    mem(ptr)%=num;
                    break;
                case '.':
                    putchar(mem(ptr));
                    break;
                case ',':
                    mem(ptr)=getchar();break;
                case ':':
                    cout<<mem(ptr);break;
                case ';':
                    cin>>mem(ptr);break;
                case '[':
                    if(mem(ptr)==0){
                        int count=0;
                        bool ok=0;
                        int j=i;
                        for(;j<a.size();j++){
                            if(a[j]=='[')count++;
                            if(a[j]==']')count--;
                            if(count==0){
                                ok=1;
                                break;
                            }
                        }
                        if(!ok){
                            cerr<<"\n在第"<<i+1<<"个字符没有匹配的\']\'\n";
                            throw logic_error("括号未匹配");
                        }else{
                            i=j;
                        }
                    }else{
                        whiles.push(i);
                    }
                    break;
                case ']':
                    if(mem(ptr)!=0){
                        if(whiles.size()==0){
                            cerr<<"\n在第"<<i+1<<"个字符没有匹配的\'[\'\n";
                            throw logic_error("括号未匹配");
                        }else i=whiles.top();
                    }else{
                        if(whiles.size()==0){
                            cerr<<"\n在第"<<i+1<<"个字符没有匹配的\'[\'\n";
                            throw logic_error("括号未匹配");
                        }else whiles.pop();
                    }
                    break;
                case '(':
                    if(mem(ptr)==0){
                        int count=0;
                        bool ok=0;
                        int j=i;
                        for(;j<a.size();j++){
                            if(a[j]=='(')count++;
                            if(a[j]==')')count--;
                            if(count==0){
                                ok=1;
                                break;
                            }
                        }
                        if(!ok){
                            cerr<<"\n在第"<<i+1<<"个字符没有匹配的\')\'\n";
                            throw logic_error("括号未匹配");
                        }else{
                            i=j;
                        }
                    }else{
                        ifs.push(i);
                    }
                    break;
                case ')':
                    if(ifs.size()==0){
                        cerr<<"\n在第"<<i+1<<"个字符没有匹配的\'(\'\n";
                        throw logic_error("括号未匹配");
                    }else ifs.pop();
                    break;
                case '#':
                    while(i<a.size()&&a[i]!='\n')i++;
                    break;
                case '}':
                    if(ptr>=maxsize-1){
                        cerr<<"\n在第"<<i+1<<"个字符的数组访问超过了最大值\n";
                        throw runtime_error("数组访问超过了最大值");
                    }
                    getnum(num,isaddr,hasnum,i);
                    mem(ptr+1)=mem(ptr)>num;
                    break;
                case '{':
                    if(ptr>=maxsize-1){
                        cerr<<"\n在第"<<i+1<<"个字符的数组访问超过了最大值\n";
                        throw runtime_error("数组访问超过了最大值");
                    }

                    getnum(num,isaddr,hasnum,i);
                    mem(ptr+1)=mem(ptr)<num;
                    break;
                case '=':
                    if(ptr>=maxsize-1){
                        cerr<<"\n在第"<<i+1<<"个字符的数组访问超过了最大值\n";
                        throw runtime_error("数组访问超过了最大值");
                    }
                    getnum(num,isaddr,hasnum,i);
                    mem(ptr+1)=(mem(ptr)==num);
                    break;
                case '&':
                    mem(ptr)=ptr;
                    break;
                case '^':
                    getnum(num,isaddr,hasnum,i);
                    if(num<0||num>=maxsize){
                        cerr<<"\n在第"<<i+1<<"个字符内存超界\n";
                        throw runtime_error("内存超界");
                    }
                    ptr=num;
                    break;
                case '|':
                    getnum(num,isaddr,hasnum,i);
                    mem(ptr)=num;
                    break;
                case '\"':{
                    int j;
                    for(j=i+1;j<a.size();j++){
                        if(a[j]=='\"')break;
                        if(j==a.size()-1){
                            cerr<<"\n在第"<<i+1<<"个字符没有匹配的\'\"\'\n";
                            throw logic_error("引号未匹配");
                        }
                        if(a[j]=='\\'){
                            if(a[j+1]=='n')cout<<'\n';
                            else if(a[j+1]=='\"')cout<<'\"';
                            else if(a[j+1]=='\\')cout<<'\\';
                            else{
                                cerr<<"\n在第"<<j+1<<"个字符是未用、弃用转义字符\n";
                                throw logic_error("未用、弃用转义字符");
                            }
                            j++;
                        }else{
                            cout<<a[j];
                        }
                    }
                    i=j;
                    break;
                }
                case '\\':
                    getnum(num,isaddr,hasnum,i);
                    mem(ptr)=mem(mem(num));
                    break;
                case '`':
                    return 0;
                    break;
                case '\n':
                case ' ':
                case '\0':
                case '\t':
                    break;
                default:
                    cerr<<"\n第"<<i+1<<"个字符是未知的:"<<a[i]<<'\n';
                    throw logic_error("关键字未知");
            }
        }
    }catch(const exception& e){
        cerr<<"错误: "<<e.what()<<'\n';
        return 1;
    }
    return 0;
}
#include "country.h"

Country::Country()
{
//    Country::PATH=Country::to_windowspath(QCoreApplication::applicationDirPath().toStdString());
}

string Country::find_windowspath(){
    QString cur=QDir::currentPath();
    qDebug()<<cur;
    QString absolute_path=QDir(cur).absoluteFilePath("");
    qDebug()<<absolute_path;
    string abp=absolute_path.toStdString();

    for(int i=0;i<abp.size();i++)
    {
        if(abp[i]=='/')
        {
            abp.erase(i,1);
            abp.insert(i,"\\");
        }
    }
    return abp;
}

QString Country::NAME[30]={"世界","中国","日本","韩国","蒙古","越南","泰国","缅甸","老挝","柬埔寨","马来西亚","新加坡","印度尼西亚","菲律宾","澳大利亚","新西兰"};
map<QString,int> Country::cindex={{"世界",0},{"中国",1},{"日本",2},{"韩国",3},{"蒙古",4},{"越南",5},{"泰国",6},{"缅甸",7},{"老挝",8},{"柬埔寨",9},{"马来西亚",10},{"新加坡",11},{"印度尼西亚",12},{"菲律宾",13},{"澳大利亚",14},{"新西兰",15}};

int Country::COLUMN=12;
int Country::ROW=170;
string Country::PATH=Country::find_windowspath();


QString Country::Item(int r,int c){
    return QString::fromStdString(item[r*COLUMN+c]);
}

Country::~Country(){
}

void Country::read(int idx){
//    cerr<<PATH<<endl;
    string s=PATH+"\\data\\";

    if(idx<10) s+=char(idx+'0');
    else{
        s+='1';
        s+=char(idx%10+'0');
    }
    s+=".CSV";

    ifstream fin(s);
        if (!fin.is_open()){qDebug()<< "打开文件失败！";cerr<<s<<endl;}

    string tmp;
    vector<string> buf;
    while(getline(fin,tmp)) buf.push_back(tmp);

//    vector<string> T;
    item.clear();
//    item.shrink_to_fit();
    for(auto it=buf.begin();it!=buf.end();it++)
    {
        string tmp;
        istringstream sfin(*it);

        for(int i=0;i<COLUMN;i++)
        {
            getline(sfin, tmp, ',');
//            if(!getline(sfin, tmp, ',')) break;
            item.push_back(tmp);
        }
    }


}

void Country::read(QString text){
    string s=PATH+"\\data\\";
    int idx=cindex[text];

    if(idx<10) s+=char(idx+'0');
    else{
        s+='1';
        s+=char(idx%10+'0');
    }
    s+=".CSV";

    ifstream fin(s);
        if (!fin.is_open()){qDebug()<< "打开文件失败！";}

    string tmp;
    vector<string> buf;
    while(getline(fin,tmp)) buf.push_back(tmp);

    item.clear();
//    item.shrink_to_fit();
    for(auto it=buf.begin();it!=buf.end();it++)
    {
        string tmp;
        istringstream sfin(*it);

        for(int i=0;i<COLUMN;i++)
        {
            getline(sfin, tmp, ',');
            item.push_back(tmp);
        }
    }
}

int Country::calc_month(int idx,int col){
    int res=0;
    switch(col){
        case 0:col=1;break;
        case 1:col=2;break;
        case 2:col=3;break;
        case 3:col=4;break;
        case 4:col=8;break;
        case 5:col=9;break;
    }
//    qDebug()<<col;

    for(int i=0+COLUMN;i<item.size();i+=COLUMN){
        char c=item[i+7][5];//月份数字
        if(c-'0'==idx){
            switch(col){
                case 1:case 3:case 8:res=to_number(item[i+col]);break;
                case 2:case 4:case 9: res+=to_number(item[i+col]);break;
            }
        }
    }

    return res;
}

int Country::to_number(string s){
    bool flag=(s[0]=='-');
    int res=0;
    for(int i=0+flag;i<s.size();i++){
        res=res*10+s[i]-'0';
    }
    if(flag) res*=-1;
    return res;
}

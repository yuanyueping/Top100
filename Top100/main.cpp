#include <bits/stdc++.h>
using namespace std;
struct node
{
    string url;
    int num;
    node(string a,int b):url(a),num(b) {}
    string setUrl(string a)
    {
        url = a;
        return url;
    }
    string getUrl()
    {
        return url;
    }
    int setNum(int b)
    {
        num = b;
        return num;
    }
    int getNum()
    {
        return num;
    }
};
bool cmp(node a, node b)
{
    if(a.num == b.num)
        return a.url >= b.url;
    return a.num >= b.num;
}
/*
查看文件的字节数
*/
double file_size(string filename)
{
    FILE *fp = NULL;
    fp = fopen(filename.c_str(),"r");
    if(!fp)
        return -1;
    fseek(fp,0L,SEEK_END);
    int  len = ftell(fp);
    return len;
}
bool isLess(string filename)
{
    double len = file_size(filename);
    // 转换成 GB 1024B=1KB,1024KB=1MB,1024MB=1GB
    for(int i = 0; i < 3; ++i)
    {
        len = len/1024.00;
    }
    if(len <= 1.00)
        return true;
    else
        return false;
}
void output(string str,string filename)
{
    ofstream out(filename);
    out << str << endl;
    return ;
}
map<int,int> mp_filename;// hash值是否出现过
vector<string>filenames; // 存放文件名
int Hash(string str)
{
    int key = 0;
    for(int i = 0; i < str.size(); ++i)
    {
        int num = str[i];
        key += (i+1)*10007*num;
    }
    key = key % 100;
    string fname = to_string(key);
    fname += ".txt";
    if( mp_filename[key] == 0)
    {
        mp_filename[key] = 1;
        filenames.push_back(fname);
    }
    output(str,fname);
    return key;
}
void Input(string filename)
{
    mp_filename.clear();

    ifstream in;
    in.open(filename.data());
    if(!in)
    {
        cout << "Can't open file" << endl;
        return ;
    }
    string buf;
    while(in >> buf)
    {
        Hash(buf);
    }
    return ;
}
bool check()
{
    for(int i = 0; i < filenames.size(); ++i)
    {
        if(!isLess(filenames[i]))
        {

            // 在执行其他的哈希方法；
            return false;
        }
    }
    return true;
}
vector<node> Sort_top100()
{
    vector<node>top_urls;
    top_urls.clear();
    for(int i = 0; i < filenames.size(); ++i)
    {
        ifstream in;
        in.open(filenames[i].data());
        if(!in)
            cout << "Can't open file" << endl;
        map<string,int>mp_url;
        string buf;
        while(in >> buf)
        {
            mp_url[buf]++;
        }
        vector<node>urls;
        map<string,int>::iterator it_url = mp_url.begin();
        while(it_url != mp_url.end())
        {
            urls.push_back(node(it_url->first,it_url->second));
        }
        sort(urls.begin(),urls.end(),cmp);
        int len = urls.size();
        len = min(len,100);
        for(int i = 0; i < len; ++i)
        {
            top_urls.push_back(urls[i]);
        }
    }
    sort(top_urls.begin(),top_urls.end(),cmp);
    return top_urls;

}
void Printf()
{
    vector<node> top_urls;
    top_urls = Sort_top100();
    for(int i = 0; i < 100; ++i)
        cout << top_urls[i].getUrl()<< "  " << top_urls[i].getNum() << endl;
    return ;

}
int main()
{
   string fname;
   cin >> fname;
   Input(fname);
   check();
   Printf();
   return 0;
}

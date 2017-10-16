//
// Created by beans on 2017/10/16.
//

#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<iterator>
#include<cctype>
#include<unordered_map>
using namespace std;

unordered_map<string, int> strMap;  //保存的结果
/***从字符串流中依次读入单词记录出现频率***/
void countWord(stringstream &ss)
{
    //依次读入单词
    string strTmp;
    while (ss >> strTmp)
    {
        unordered_map<string, int>::iterator it = strMap.find(strTmp);
        if (it == strMap.end())
        {
            strMap.insert(unordered_map<string, int>::value_type(strTmp, 1));
        }
        else
            strMap[strTmp]++;
    }
}

int main()
{
    //读入文档
    string strFile, tmp;
    fstream file("1.txt");
    while(getline(file, strFile))  //!file.eof()
    {
        strFile.append(tmp);
        tmp.clear();
    }
    //去除符号
    for (int i = 0; i<strFile.length(); i++)
    {
        if (ispunct(strFile[i]))
            strFile[i] = ' ';
    }
    //统计字符
    stringstream ss(strFile);
    countWord(ss);
    //打印结果
    cout << "{"<<endl;
    unordered_map<string,int>::const_iterator it;
    for (it = strMap.begin(); it != strMap.end(); ++it) {
        if (it != strMap.begin())
            cout << "," << endl;
        printf("(%s,%.3lf)",it->first.c_str(),(double)((double)it->second/(double)strMap.size()));
    }
    cout <<endl<<"}"<< endl;
    return 0;
}
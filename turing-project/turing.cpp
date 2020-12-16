#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator> // for std::ostream_iterator
#include <algorithm>  // for std::copy
#include "machine.h"
int ini_machine(Machine &machine){
    ifstream file;
    file.open("../programs/example.tm",ios::in);
    if(!file.is_open()){
        cout<<"file is not found or the read process fails"<<endl;
        return 0; //exit
    }
    string strLine;
    while(getline(file,strLine))
    {
        if(strLine.empty())  //跳过空行
            continue;
        vector<string> res_line;
        stringstream ss(strLine);
        string temp_line;
        while (ss >> temp_line)
            res_line.push_back(temp_line);
        if(res_line.size()>=1 && res_line[0]==";")  //此行为注释内容 跳过
            continue;
        else if(res_line.size()>=3 && res_line[1]=="="){  //处理带等号的式子
            machine.ini_equal(res_line[0],res_line[2]);
        }
        else if(res_line.size()>=5){  //处理转移函数
            machine.ini_delta(res_line);
        }
        else
            return 0;  // 不属于上述任何一种，TM定义有误
    }
    return 1;
}


int main(void)
{
    Machine machine;
    int ini_result = ini_machine(machine);  //读取tm文件 初始化machine
    if(ini_result==0)  //TM初始化失败
        return 0;
    int check_result = machine.check();

    cout<<endl<<endl;
    for(int i=0;i<(machine.delta).size();i++){
        copy (machine.delta[i].begin(), machine.delta[i].end(), ostream_iterator<string> (cout, " "));
        cout<<endl<<endl;
    }
    cout<<endl<<endl<<endl<<endl;
    copy (machine.Q.begin(), machine.Q.end(), ostream_iterator<string> (cout, "   "));
    cout<<endl;
    copy (machine.S.begin(), machine.S.end(), ostream_iterator<string> (cout, "   "));
    cout<<endl;
    copy (machine.G.begin(), machine.G.end(), ostream_iterator<string> (cout, "   "));
    cout<<endl;
    cout<<machine.q0<<endl;
    cout<<machine.B<<endl;
    cout<<machine.num<<endl;
    copy (machine.F.begin(), machine.F.end(), ostream_iterator<string> (cout, "   "));
    cout<<endl;
    return 1;
}
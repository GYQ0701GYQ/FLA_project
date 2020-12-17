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
    if(ini_result==0){ //TM初始化失败
        cout<<"Ini failed"<<endl;
        return 0;
    }    
    int check_result = machine.check();
    if(check_result==0){
        cout<<"Definition illegal"<<endl;
        return 0; //TM定义不合法
    }

    string test_str="010110_",temp_push,temp_cmp;
    vector<vector<string>> tape;
    vector<string> temp_tape;
    vector<int> pos;
    string current_state=machine.q0;
    stringstream ss;
    int tape_num;
    ss<<machine.num;
    ss>>tape_num;
    temp_tape.push_back("_");  //每个tape最左端设置Blank
    for(int j=0;j<tape_num;j++){
        tape.push_back(temp_tape);
        pos.push_back(1);  //初始pos跳过最左端的blank
    }
    for(int i=0;i<test_str.length();i++){
        temp_push.push_back(test_str[i]);
        tape[0].push_back(temp_push);
        for(int j=1;j<tape_num;j++)
            tape[j].push_back(machine.B);
        temp_push="";
    }
    if(tape[0].size()<=0) //无待解析内容
        return 0;

    vector<string>::iterator it = machine.F.end();
    while(it==machine.F.end()){
        for(int i=0;i<tape.size();i++){
            cout<<"head:"<<pos[i]<<"  ";
            copy (tape[i].begin(), tape[i].end(), ostream_iterator<string> (cout, " "));
            cout<<endl;
        }
        cout<<endl;
        temp_cmp = "";
        for(int j=0;j<tape_num;j++) //获取当前全部读头的内容
            temp_cmp += tape[j][pos[j]];
        for(int i=0;i<machine.delta[0].size();i++){
            if(current_state==machine.delta[0][i] && temp_cmp==machine.delta[1][i]){  //和第i个转移语句匹配
                cout<<"经过一次移动"<<current_state<<"   "<<temp_cmp<<"  ";
                current_state = machine.delta[4][i];
                for(int k=0;k<tape_num;k++){
                    // tape[k][pos[k]] = machine.delta[2][i][k];
                    if(pos[k]==tape[k].size()-1 && machine.delta[3][i][k] == 'r' ){
                        string aaa;
                        aaa.push_back(machine.delta[2][i][k]);
                        tape[k].push_back(machine.B);
                    }
                    if(pos[k]>=1 && pos[k]<=tape[k].size()-2)
                        tape[k][pos[k]] = machine.delta[2][i][k];
                    else if(pos[k]==0 && machine.delta[3][i][k] == 'l')
                        break;
                    cout<<machine.delta[2][i][k];
                    if(machine.delta[3][i][k] == 'r')
                        pos[k]++;
                    else if(machine.delta[3][i][k] == 'l')
                        pos[k]--;
                }
                cout<<"   "<<current_state<<endl;
                it = find(machine.F.begin(), machine.F.end(), current_state);
                break;
            }
            // cout<<temp_cmp<<endl;
        }
    }
    // copy (tape1.begin(), tape1.end(), ostream_iterator<string> (cout, "   "));
    // cout<<endl;
    // copy (tape2.begin(), tape2.end(), ostream_iterator<string> (cout, "   "));
    // cout<<endl;
    // cout<<endl<<endl;
    // for(int i=0;i<(machine.delta).size();i++){
    //     copy (machine.delta[i].begin(), machine.delta[i].end(), ostream_iterator<string> (cout, " "));
    //     cout<<endl<<endl;
    // }
    // cout<<endl<<endl<<endl<<endl;
    // copy (machine.Q.begin(), machine.Q.end(), ostream_iterator<string> (cout, "   "));
    // cout<<endl;
    // copy (machine.S.begin(), machine.S.end(), ostream_iterator<string> (cout, "   "));
    // cout<<endl;
    // copy (machine.G.begin(), machine.G.end(), ostream_iterator<string> (cout, "   "));
    // cout<<endl;
    // cout<<machine.q0<<endl;
    // cout<<machine.B<<endl;
    // cout<<machine.num<<endl;
    // copy (machine.F.begin(), machine.F.end(), ostream_iterator<string> (cout, "   "));
    // cout<<endl;
    return 1;
}
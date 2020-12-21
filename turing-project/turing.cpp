#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator> // for std::ostream_iterator
#include <algorithm>  // for std::copy
#include "machine.h"
int ini_machine(Machine &machine, string input_tm){
    ifstream file;
    string name = "../programs/"+input_tm;
    const char *aaa = (char*)name.c_str();
    file.open(aaa,ios::in);
    if(!file.is_open()){
        // cout<<"File is not found or the read process fails"<<endl;
        fprintf(stderr,"TM file is not found or the read process failed\n");
        exit(1); //exit
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
        else if((res_line.size()==3 && res_line[1]=="=") || (res_line.size()>3 && res_line[3]==";")){  //处理带等号的式子
            machine.ini_equal(res_line[0],res_line[2]);
        }
        else if((res_line.size()==5) || (res_line.size()>5 && res_line[5]==";") ){  //处理转移函数
            machine.ini_delta(res_line);
        }
        else
            return 0;  // 不属于上述任何一种，TM定义有误
    }
    return 1;
}

int ini_para(int &verbose, string &input_tm, string &input_str, string &input_para, int argc,char** argv){
    switch(argc){
        case 1 :
            fprintf(stdout,"usage: turing [-v|--verbose] [-h|--help] <tm> <input>\n");
            exit(1);
            return 0;
        case 2 :
            input_para=argv[1];
            if(input_para=="-h" || input_para=="--help"){
                fprintf(stdout,"usage: turing [-v|--verbose] [-h|--help] <tm> <input>\n");
                return 0;
            }
            else{
                fprintf(stderr,"parameter error\n");
                return 0;
            }
        case 3 :
            input_para=argv[1];
            if(input_para=="-v" || input_para=="--verbose" || input_para=="-h" || input_para=="--help"){
                fprintf(stderr,"parameter error\n");
                return 0;
            }
            else{
                input_tm = argv[1];
                input_str = argv[2];
                return 1;
            }
        case 4 :
            input_para=argv[1];
            if(input_para=="-v" || input_para=="--verbose")
                verbose=1;
            input_tm = argv[2];
            input_str = argv[3];
            return 1;
        default:
            fprintf(stderr,"parameter error\n");
            return 0;
    }
    return 0;
}

int main(int argc,char** argv)
{
    string input_tm, input_str,input_para;
    int verbose=0;
    int para_result = ini_para(verbose,input_tm,input_str,input_para,argc,argv);
    if(para_result==0){ //参数解析
        exit(1);
    }   
    Machine machine;
    int ini_result = ini_machine(machine, input_tm);  //读取tm文件 初始化machine
    if(ini_result==0){ //TM初始化失败
        fprintf(stderr,"syntax error\n");
        exit(1);
    }    
    int check_result = machine.check();
    if(check_result==0){
        fprintf(stderr,"syntax error\n");
        exit(1);
    }
    // handle input_str
    string temp_push,temp_cmp;
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
    if(verbose==1)
        cout<<"Input: "<<input_str<<endl;
    for(int i=0;i<input_str.length();i++){
        temp_push.push_back(input_str[i]);
        vector<string>::iterator input_letter=find(machine.S.begin(), machine.S.end(), temp_push);
        if(input_letter!=machine.S.end()){
            tape[0].push_back(temp_push);
            for(int j=1;j<tape_num;j++)
                tape[j].push_back(machine.B);
            temp_push="";
        }
        else if(verbose==1){
            cout<<"==================== ERR ===================="<<endl;
            cout<<"error: '"<<input_str[i]<<"' was not declared in the set of input symbols"<<endl;
            cout<<"Input: "<<input_str<<endl;
            cout<<"       ";
            for(int k=0;k<i;k++)
                cout<<" ";
            cout<<"^"<<endl;
            cout<<"==================== END ===================="<<endl;
            exit(1);
        }
        else if(verbose==0){
            fprintf(stderr,"illegal input\n");
            exit(1);
        }
    }
    cout<<"==================== RUN ===================="<<endl;
    
    // handle tape0
    if(tape[0].size()<=0) //无待解析内容
        return 0;
    else{
        for(int j=0;j<tape_num;j++)
            tape[j].push_back(machine.B);
    }
    // for(int i=0;i<tape.size();i++){
    //         cout<<"初始 head:"<<pos[i]<<"  ";
    //         copy (tape[i].begin(), tape[i].end(), ostream_iterator<string> (cout, " "));
    //         cout<<endl;
    //     }
    // cout<<endl;
    vector<string>::iterator it = machine.F.end();
    int step=0;
    if(verbose==1){
        cout<<"Step   : "<<step<<endl;
        for(int i=0;i<tape.size();i++){
            cout<<"Index"<<i<<" : ";
            for(int j=0;j<tape[i].size();j++){
                cout<<j<<" ";
            }
            cout<<endl;
            cout<<"Tape"<<i<<"  : ";
            for(int j=0;j<tape[i].size();j++){
                cout<<tape[i][j]<<" ";
            }
            cout<<endl;
            cout<<"Head"<<i<<"  : ";
            for(int j=0;j<tape[i].size()-1;j++){
                cout<<"  ";
            }
            cout<<"^"<<endl;
        }
        cout<<"State  : "<<current_state<<endl<<"---------------------------------------------"<<endl;
    }

    while(it==machine.F.end()){
        temp_cmp = "";
        for(int j=0;j<tape_num;j++) //获取当前全部读头的内容
            temp_cmp += tape[j][pos[j]];
        for(int i=0;i<machine.delta[0].size();i++){
            if(current_state==machine.delta[0][i] && temp_cmp==machine.delta[1][i]){  //和第i个转移语句匹配
                step++;
                current_state = machine.delta[4][i];
                for(int k=0;k<tape_num;k++){
                    if(pos[k]==tape[k].size()-1 && machine.delta[3][i][k] == 'r' ){  //为tape尾部追加一位
                        tape[k].push_back(machine.B);
                    }
                    if(pos[k]>=0 && pos[k]<=tape[k].size()-1)
                        tape[k][pos[k]] = machine.delta[2][i][k];
                    if(pos[k]==0 && machine.delta[3][i][k] == 'l')  //head=0要向左移
                        break;
                    if(machine.delta[3][i][k] == 'r')
                        pos[k]++;
                    else if(machine.delta[3][i][k] == 'l')
                        pos[k]--;
                }
                it = find(machine.F.begin(), machine.F.end(), current_state);
                break;
            }else if(i==machine.delta[0].size()-1){
                step++;
                current_state="reject";
                it = find(machine.F.begin(), machine.F.end(), current_state);
                break;
            }
            // cout<<temp_cmp<<endl;
        }
        // for(int i=0;i<tape.size();i++){
        //     cout<<"head"<<i+1<<":"<<pos[i]<<"  "<<current_state;
        //     copy (tape[i].begin(), tape[i].end(), ostream_iterator<string> (cout, " "));
        //     cout<<endl;
        // }
        // cout<<endl;
        if(verbose==1){
        cout<<"Step   : "<<step<<endl;
        for(int i=0;i<tape.size();i++){
            cout<<"Index"<<i<<" : ";
            for(int j=0;j<tape[i].size();j++){
                cout<<j<<" ";
            }
            cout<<endl;
            cout<<"Tape"<<i<<"  : ";
            for(int j=0;j<tape[i].size();j++){
                cout<<tape[i][j]<<" ";
            }
            cout<<endl;
            cout<<"Head"<<i<<"  : ";
            for(int j=0;j<tape[i].size()-1;j++){
                cout<<"  ";
            }
            cout<<"^"<<endl;
        }
        cout<<"State  : "<<current_state<<endl<<"---------------------------------------------"<<endl;
        }
    }
    switch(verbose){
        case 1 :
            cout<<"Result: ";
            for(int i=0;i<tape[0].size();i++)
                if(tape[0][i] != machine.B)
                    cout<<tape[0][i];
            cout<<endl<<"==================== END ===================="<<endl;
            break;
        case 0:
            for(int i=0;i<tape[0].size();i++)
                if(tape[0][i] != machine.B)
                    cout<<tape[0][i];
            break;
        default:
            break;
    }
    return 1;
}
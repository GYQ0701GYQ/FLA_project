#include <stdio.h>
#include <iostream>
#include <sstream>
#include "machine.h"

Machine::Machine()
{
    this->a = 99;
    vector<string> temp;
    for(int i=0;i<5;i++){
        this->delta.push_back(temp);
    }
}
void Machine::print()
{
    cout<<"the value of a is "<<this->a<<endl;
}
int Machine::ini_equal(string left, string right){
    if(left=="#q0")
        this->q0 = right;
    else if(left=="#B")
        this->B = right;
    else if(left=="#N")
        this->num = right;
    else{
        string tok;
        string temp_str="";
        vector<string> temp_result;
        stringstream s1(right);  //去掉左括号
        while(getline(s1,tok,'{'))
            if(tok > "")
                temp_str += tok;
        stringstream s2(temp_str);  //去掉右括号
        temp_str="";
        while(getline(s2,tok,'}'))
            if(tok > "")
                temp_str += tok;
        stringstream s3(temp_str);  //根据逗号分隔
        temp_str="";
        while(getline(s3,tok,','))
            if(tok > "")
                temp_result.push_back(tok);
        if(left=="#Q")
            this->Q = temp_result;
        else if(left=="#S")
            this->S = temp_result;
        else if(left=="#G")
            this->G = temp_result;
        else if(left=="#F")
            this->F = temp_result;
        else 
            return 0;
    }
    return 1;
}
int Machine::ini_delta(vector<string> a){
    // this->delta的size已经被初始化为5，a的大小
    for(int i=0;i<5;i++)
        this->delta[i].push_back(a[i]);  //纵向把每一个转移步骤push到delta
    // cout<<this->delta[0].size()<<endl;
    return 1;
}
int Machine::check(){
    // 合法性检查：S必须在G中，B必须在G中，B不能在S中
    // q0必须在Q中,F必须在Q中
    // num必须是数字符号且大于0
    // 不能有读头均不移动且在同一状态的情况（陷入循环）
    // 每个移动的当前状态和下一状态必须都在Q中
    //每个移动的内容长度不能超过num
    // string a="4";
    // stringstream s1;
    // int c;
    // s1<<a;
    // s1>>c;
    // cout<<c<<endl;
    return 1;
}
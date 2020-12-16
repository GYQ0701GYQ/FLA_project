#ifndef MACHINE_H
#define MACHINE_H
#include <vector>
using namespace std;

class Machine
{
    public:  
    int a;  //for test

    vector<string> Q;
    vector<string> S;
    vector<string> G;
    string q0;
    string B;
    string num;
    vector<string> F;
    vector<vector<string>> delta;

    void print(); // for test
    Machine();
    int ini_equal(string left, string right);
    int ini_delta(vector<string> a);
    int check();
};

#endif
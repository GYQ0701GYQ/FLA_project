# FLA_project
## 1.目录结构描述
MF20330024-管俣祺.tar.gz

|——|— MF20330024-管俣祺.pdf
   
|——|— programs

|—————|— case1.tm

|—————|— case2.tm

|—————|— example.tm

|——|— README.md

|——|— turing-project

|—————|— machine.cpp  （machine类为图灵机解析器）

|—————|— machine.h  （machine类头文件）

|—————|— Makefile

|—————|— turing.cpp （模拟器）



## 2.TM定义的要求
（1）由于模拟器设置的停机条件为：当前状态=某个终止状态，而在处理输入串的过程中，遇到不匹配任何转移函数的情况会进入reject状态，reject状态在纸带上写下false后进入halt_reject停机；

（2）输入串符合语法时会进入halt_accept停机；

（3）因此，tm文件中定义的状态集Q必须包含reject状态（状态名必须是reject），以及终止状态集必须包含接受停机（halt_accept或其他名称均可）和拒绝停机（halt_reject或其他名称均可）两种状态，来控制模拟器的停机。

## 3.编译说明
（1）进入turing-project目录下编译，执行命令：make

（2）将./turing重命名，执行：alias  turing=./turing

（3）按照project里声明的运行方式运行程序

; This example program checks 1^m x 1^n = 1^mn

; the finite set of states
#Q = {start,A,B,C,D,E,cmp,accept,accept2,accept3,accept4,halt_accept,reject,reject2,reject3,reject4,reject5,halt_reject}

; the finite set of input symbols
#S = {1,0,x,=}

; the complete set of tape symbols
#G = {1,0,x,=,_,t,r,u,e,f,a,l,s}

; the start state
#q0 = start

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept,halt_reject}

; the number of tapes
#N = 2

; the transition functions

; State start: start state
start 1_ __ r* A

; State A: pass 1 until meet x
A 1_ 1_ r* A
A x_ x_ r* B

; State B: copy 1 until meet =
B 1_ 11 rr B
B =_ =_ l* C

; State C: move head 1 to left
C x_ x_ l* C
C 1_ 1_ l* C
C __ __ r* D

; State D: check if exist 1 before x
D 1_ __ r* A
D x_ __ rl E

; State E: erase symbol before =
E 11 _1 r* E
E =1 _1 r* cmp

; State cmp: compare two tapes
cmp 11 __ rl cmp
cmp __ __ ** accept

; State accept*: write 'true' on 1st tape
accept __ t_ r* accept2
accept2 __ r_ r* accept3
accept3 __ u_ r* accept4
accept4 __ e_ ** halt_accept

; State reject*: write 'false' on 1st tape
reject 11 __ rr reject
reject x1 __ rr reject
reject =1 __ rr reject
reject 1_ __ r* reject
reject x_ __ r* reject
reject =_ __ r* reject
reject _1 __ *l reject  ; erase
reject __ f_ r* reject2
reject2 __ a_ r* reject3
reject3 __ l_ r* reject4
reject4 __ s_ r* reject5
reject5 __ e_ ** halt_reject

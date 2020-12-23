; This example program checks a^i b^j a^i b^j

; the finite set of states
#Q = {start,A,B,C,cmp,accept,accept2,accept3,accept4,halt_accept,reject,reject1,reject2,reject3,reject4,reject5,halt_reject}

; the finite set of input symbols
#S = {a,b}

; the complete set of tape symbols
#G = {a,b,_,t,r,u,e,f,a,l,s}

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
start a_ _a rr A

; State A: write a 
A a_ _a rr A
A b_ _b rr B

; State B: write b
B b_ _b rr B
B a_ a_ *l C

; State C: move head 2 to left
C ab ab *l C
C aa aa *l C
C a_ a_ *r cmp

; State cmp: compare two tapes
cmp aa __ rr cmp
cmp bb __ rr cmp
cmp __ __ ** accept

; State accept*: write 'true' on 1st tape
accept __ t_ r* accept2
accept2 __ r_ r* accept3
accept3 __ u_ r* accept4
accept4 __ e_ ** halt_accept

; State reject*: write 'false' on 1st tape
reject aa aa ll reject
reject ab ab ll reject
reject ba ba ll reject
reject bb bb ll reject
reject a_ a_ l* reject
reject b_ b_ l* reject
reject _a _a *l reject
reject _b _b *l reject
reject __ __ rr reject1
reject1 aa __ rr reject1
reject1 ab __ rr reject1
reject1 ba __ rr reject1
reject1 bb __ rr reject1
reject1 a_ __ r* reject1
reject1 b_ __ r* reject1
reject1 _a __ *r reject1
reject1 _b __ *r reject1
reject1 __ f_ r* reject2
reject2 __ a_ r* reject3
reject3 __ l_ r* reject4
reject4 __ s_ r* reject5
reject5 __ e_ ** halt_reject

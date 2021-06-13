## 1.Compiler(.C) -> 2.Assemtler(.S) -> Machine Language(.O) -> CPU
## 3.VM 虛擬機器 4.OS 作業系統
## Compiler :  Sytax -> Semantie -> Code Generation -> IR -> ASM -> Obj
## 早期電腦工程師都是女的 bug
## 練習
```
PS C:\Users\USER\sp\03-compiler\00-gen> gcc genExp.c rlib.c -o genExp
PS C:\Users\USER\sp\03-compiler\00-gen> ./genExp
6
(5/1)
6-3*(2/(7+4*9))
5/((3*1))
0*8
1/(6*5+3)
9+(4*(9))-1*0
8/7-7*((((4/0)/2)/1-1*4)*(5/4+3*3)+2*5)
2/4
9/0
```
```
PS C:\Users\USER\sp\03-compiler\00-gen> gcc genEnglish.c rlib.c -o genEnglish
PS C:\Users\USER\sp\03-compiler\00-gen> ./genEnglish
a dog chase a dog
```
```
PS C:\Users\USER\sp\03-compiler\01-exp0> gcc exp0.c -o exp0
PS C:\Users\USER\sp\03-compiler\01-exp0> ./exp0 '3+4+5'
argv[0]=C:\Users\USER\sp\03-compiler\01-exp0\exp0.exe argv[1]=3+4+5
=== EBNF Grammar =====
E=F ([+-] F)*
F=Number | '(' E ')'
==== parse:3+4+5 ========
t0=3
t1=4
t2=t0+t1
t3=5
t4=t2+t3

PS C:\Users\USER\sp\03-compiler\01-exp0> ./exp0 '3+(5-4)'
argv[0]=C:\Users\USER\sp\03-compiler\01-exp0\exp0.exe argv[1]=3+(5-4)
=== EBNF Grammar =====
E=F ([+-] F)*
F=Number | '(' E ')'
==== parse:3+(5-4) ========
t0=3
t1=5
t2=4
t3=t1-t2
t4=t0+t3
```
```
PS C:\Users\USER\sp\03-compiler\01-exp0> ./exp0hack '3+5'    
=== EBNF Grammar =====
E=F ([+-] F)*
F=Number | '(' E ')'
==== parse:3+5 ========
# t0=3
@3
D=A
@t0
M=D
# t1=5
@5
D=A
@t1
M=D
# t2=t0+t1
@t0
D=M
@t1
D=D+M
@t2
M=D
```
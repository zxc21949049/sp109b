## if
```
// if (EXP) STMT (else STMT)?
void IF() {
  int ifBegin = nextLabel();
  int ifMid = nextLabel();
  int ifEnd = nextLabel();
  emit("(L%d)\n", ifBegin);
  skip("if");
  skip("(");
  int e = E();
  emit("if not T%d goto L%d\n", e, ifMid); //經if判斷不成立，到下一個條件式
  skip(")");
  STMT();
  emit("goto L%d\n", ifEnd);  //條件成立，結束
  emit("(L%d)\n", ifMid);  //第二個條件式
  if (isNext("else")) {
    skip("else");
    STMT();
    emit("goto L%d\n", ifEnd);  //條件成立，結束
  }
}
```

## if.c
```
if (x>5)
{
    t=1;
}
else if (x<=0){
    t=2;
}else{
    t=3;
}
```
## 執行
```
zxc21949049@MSI MINGW64 /d/VScode/WP/ccc/sp109b/my homework/IF (main)
$ gcc compiler.c main.c lexer.c -o compiler

zxc21949049@MSI MINGW64 /d/VScode/WP/ccc/sp109b/my homework/IF (main)
$ ./compiler if.c
if (x>5)       
{
    t=1;       
}
else if (x<=0){
    t=2;       
}else{
    t=3;       
}
========== lex ==============
token=if
token=(
token=x
token=>
token=5
token=)
token={
token=t
token==
token=1
token=;
token=}
token=else
token=if
token=(
token=x
token=<=
token=0
token=)
token={
token=t
token==
token=2
token=;
token=}
token=else
token={
token=t
token==
token=3
token=;
token=}
========== dump ==============
0:if
1:(
2:x
3:>
4:5
5:)
6:{
7:t
8:=
9:1
10:;
11:}
12:else
13:if
14:(
15:x
16:<=
17:0
18:)
19:{
20:t
21:=
22:2
23:;
24:}
25:else
26:{
27:t
28:=
29:3
30:;
31:}
============ parse =============
(L0)
t0 = x
t1 = 5
t2 = t0 > t1
if not T2 goto L1
t3 = 1
t = t3
goto L2
(L1)
(L3)
t4 = x
t5 = 0
t6 = t4 <= t5
if not T6 goto L4
t7 = 2
t = t7
goto L5
(L4)
t8 = 3
t = t8
goto L5
goto L2
```

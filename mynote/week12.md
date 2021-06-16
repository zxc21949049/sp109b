## 練習
* fork1.c
```
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>

int main() { 
    fork(); // 一個行程分叉成父子兩個行程
    fork(); // 兩個行程又分別分叉出兩對父子，所以變成四個行程。
    printf("%-5d : Hello world!\n", getpid());
}

```
>fork() 複製行程 n---->2n <br>
>getpid就是得到該行程的識別碼
* result
```
zxc21949049@ubuntu:~/sp/08-posix/03-fork/01-hello$ gcc fork1.c -o fork1
zxc21949049@ubuntu:~/sp/08-posix/03-fork/01-hello$ ./fork1
4120  : Hello world!
4122  : Hello world!
zxc21949049@ubuntu:~/sp/08-posix/03-fork/01-hello$ 4121  : Hello world!
4123  : Hello world!
```
>fork() 的過程: 
>1. 4120-----> 4120&4121
>2. 4120----->4120&4122 , 4121----->4121&4123
* fork2.c
```
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>

int main() { 
    printf("%-5d : enter\n", getpid());
    fork(); // 一個行程分叉成父子兩個行程
    printf("%-5d : after 1st fork\n", getpid());
    fork(); // 兩個行程又分別分叉出兩對父子，所以變成四個行程。
    printf("%-5d : Hello world!\n", getpid());
}
```
* result 
```
zxc21949049@ubuntu:~/sp/08-posix/03-fork/01-hello$ gcc fork2.c -o fork2
yzxc21949049@ubuntu:~/sp/08-posix/03-fork/01-hello$ ./fork2
4261  : enter
4261  : after 1st fork
4261  : Hello world!
4263  : Hello world!
zxc21949049@ubuntu:~/sp/08-posix/03-fork/01-hello$ 4262  : after 1st fork
4262  : Hello world!
4264  : Hello world!
```
> fork() 的過程:
> 1. 4261----->4261&4262
> 2. 4261----->4261----->4261&4263 , 4262----->4262&4264
* fork3.c 
```
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>

int main() { 
    printf("%-5d : enter\n", getpid());
    fork(); // 一個行程分叉成父子兩個行程
    printf("%-5d : after 1st fork\n", getpid());
    fork(); // 兩個行程又分別分叉出兩對父子，所以變成四個行程。
    printf("%-5d : Hello world!\n", getpid());
    while (1) {}
}

```
* result
```
zxc21949049@ubuntu:~/sp/08-posix/03-fork/01-hello$ gcc fork3.c -o fork3
zxc21949049@ubuntu:~/sp/08-posix/03-fork/01-hello$ ./fork3&
[1] 4395
zxc21949049@ubuntu:~/sp/08-posix/03-fork/01-hello$ 4395  : enter
4395  : after 1st fork
4395  : Hello world!
4397  : Hello world!
4396  : after 1st fork
4396  : Hello world!
4398  : Hello world!
```
>進行背景執行方便觀察

* /02-child fork2.c
```
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>

int main() { 
    fork();  // 一個行程分叉成父子兩個行程
    if (fork()==0) { // 兩個行程又分別分叉出兩對父子，所以變成四個行程。
      printf("%-5d: I am child!\n", getpid());
    } else {
      printf("%-5d: I am parent!\n", getpid());
    }
}
```
* result 
```
zxc2194049@ubuntu:~/sp/08-posix/03-fork/02-child$ gcc fork2.c -o fork2
zxc2194049@ubuntu:~/sp/08-posix/03-fork/02-child$ ./fork2
4553 : I am parent!
4555 : I am child!
zxc2194049@ubuntu:~/sp/08-posix/03-fork/02-child$ 4554 : I am parent!
4556 : I am child!
```
>fork()=0則為parent，其他值則為child，利用此方法分辨子母行程

* execvp1.c
```
#include <stdio.h>
#include <unistd.h>

int main() {
  char *arg[] = {"ls", "-l", NULL };
  printf("execvp():before\n");
  execvp(arg[0], arg);
  printf("execvp():after\n");
}
```
* result
```
zxc2194049@ubuntu:~/sp/08-posix/03-fork/03-exec$ gcc execvp1.c -o execvp1
zxc2194049@ubuntu:~/sp/08-posix/03-fork/03-exec$ ./execvp1
execvp():before
total 28
drwxrwxr-x 2 zxc2194049 zxc2194049  4096  3月 26 20:40 backup
-rwxrwxr-x 1 zxc2194049 zxc2194049 16792  6月 11 19:31 execvp1
-rw-rw-r-- 1 zxc2194049 zxc2194049   176  3月 26 20:40 execvp1.c
```
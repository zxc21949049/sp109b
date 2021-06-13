## 練習

* task.c
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *msg = argv[1];

    for (int i=0; i<5; i++) {
        printf("%d:%s\n", i, msg);
        sleep(1);//在unistd內的非標準函示庫
    }
    return 0;
}
```
* 執行結果
```
ko@ko-VirtualBox:~$ cd sp
ko@ko-VirtualBox:~/sp$ cd 08-posix
ko@ko-VirtualBox:~/sp/08-posix$ cd 01-basic
ko@ko-VirtualBox:~/sp/08-posix/01-basic$ gcc task.c -o task
ko@ko-VirtualBox:~/sp/08-posix/01-basic$ ls
cbasic.md  file  file.c  fileWinLinux  fileWinLinux.c  forever  forever.c  hello  hello.c  hello.txt  mem0.c  mem.c  task  task.c  vmem.c
ko@ko-VirtualBox:~/sp/08-posix/01-basic$ ./task
0:(null)
1:(null)
2:(null)
3:(null)
4:(null)
ko@ko-VirtualBox:~/sp/08-posix/01-basic$ ./task abcd
0:abcd
1:abcd
2:abcd
3:abcd
4:abcd
```
* vmem.c
```
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("location of code : %p\n", main);//存放在記憶體的位置
    printf("location of heap : %p\n", malloc(100e6));//分配記憶體的位置
    int x = 3;
    printf("location of stack: %p\n", &x);//堆疊的最上層目前的位置
    return 0;
}
```
* 執行結果
```
ko@ko-VirtualBox:~/sp/08-posix/01-basic$ gcc vmem.c -o vmem
ko@ko-VirtualBox:~/sp/08-posix/01-basic$ ./vmem
location of code : 0x563832fee189
location of heap : 0x7f34225e9010
location of stack: 0x7fff6b3dd994
```
* mem.c
```
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int counter = 0;

int main(int argc, char *argv[]) {
    printf("(%d) addr of counter: %p\n", (int) getpid(), &counter);
    for (int i=0; i<5; i++) {
	    sleep(1);
	    counter = counter + 1;
	    printf("%d:(%d) value of counter: %d\n", i, getpid(), counter);
    }
    return 0;
}

```
* 執行結果
```
ko@ko-VirtualBox:~/sp/08-posix/01-basic$ gcc mem.c -o mem
ko@ko-VirtualBox:~/sp/08-posix/01-basic$ ./mem
(5158) addr of counter: 0x565333409014
0:(5158) value of counter: 1
1:(5158) value of counter: 2
2:(5158) value of counter: 3
3:(5158) value of counter: 4
4:(5158) value of counter: 5
```
* mem0.c
```
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int counter;

int main(int argc, char *argv[]) {
    int *p = malloc(sizeof(int));
    printf("(%d) addr pointed to by p: %p\n", (int) getpid(), p);
    *p = 0;
    for (int i=0; i<5; i++) {
	    sleep(1);
	    *p = *p + 1;
	    printf("%d:(%d) value of p: %d\n", i, getpid(), *p);//取得行程代號
    }
    return 0;
}

```
* 執行結果
```
ko@ko-VirtualBox:~/sp/08-posix/01-basic$ ./mem0
(5183) addr pointed to by p: 0x55c2f13442a0
0:(5183) value of p: 1
1:(5183) value of p: 2
2:(5183) value of p: 3
3:(5183) value of p: 4
4:(5183) value of p: 5
```
* georgeMary.c
```
#include <pthread.h>     // 引用 pthread 函式庫
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> 

void *print_george(void *argu) {    // 每隔一秒鐘印出一次 George 的函數
  while (1) {    
    printf("George\n");    
    sleep(1);    
  }    
  return NULL;    
}    

void *print_mary(void *argu) {     // 每隔2秒鐘印出一次 Mary 的函數
  while (1) {    
    printf("Mary\n");    
    sleep(2);    
  }    
  return NULL;    
}    

int main() {     // 主程式開始
  pthread_t thread1, thread2;     // 宣告兩個執行緒
  pthread_create(&thread1, NULL, &print_george, NULL);    // 執行緒 print_george
  pthread_create(&thread2, NULL, &print_mary, NULL);    // 執行緒 print_mary
  while (1) {     // 主程式每隔一秒鐘
    printf("----------------\n");    // 就印出分隔行
    sleep(1);     // 停止一秒鐘
  }    
  return 0;    
}

```
* 執行結果
```
ko@ko-VirtualBox:~/sp/08-posix$ cd 02-thread
ko@ko-VirtualBox:~/sp/08-posix/02-thread$ gcc georgeMary.c -o georgeMary -lpthread
ko@ko-VirtualBox:~/sp/08-posix/02-thread$ ls
deadlock2.c  deadlock.c  georgeMary  georgeMary.c  linux.md  norace.c  norace.s  philospher.c  producerConsumer.c  race.c  race.s  README.md
ko@ko-VirtualBox:~/sp/08-posix/02-thread$ ./georgeMary
----------------
Mary
George
----------------
George
----------------
Mary
George
----------------
George
Mary
----------------
George
----------------
George
Mary
----------------
George
^C
```
## 練習
* stderr1.c
```
#include <stdio.h>

int main() {
  fprintf(stdout, "Some message!\n");
  fprintf(stderr, "Warning: xxx\n");
  fprintf(stderr, "Error: yyy\n");
}
```
>標準輸出，輸出預設顯示在終端機上
* result 
```
zxc21949049@ubuntu:~/sp/08-posix/04-fs/04-stderr$ ./stderr1
Some message!
Warning: xxx
Error: yyy
```
* stderr2.c
```
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
  int fdb = open("log.txt", O_CREAT|O_RDWR, 0644);  // 打開檔案 log.txt 並取得代號 fdb
  dup2(fdb, 2); // 複製 fdb 檔案描述子到 2 (stderr)
  fprintf(stderr, "Warning: xxx\n");
  fprintf(stderr, "Error: yyy\n");
}
```
>輸出至檔案而非終端機上，可透過ls找到該檔案
* result
```
zxc21949049@ubuntu:~/sp/08-posix/04-fs/04-stderr$ ./stderr2
zxc21949049@ubuntu:~/sp/08-posix/04-fs/04-stderr$ 
```
* blocking1.c
```
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
    int fd = open("/dev/tty",O_RDONLY); //Open the standard I / O file, which is blocked.
    if(fd == -1){
        perror("open /dev/tty");
        exit(1);
    }
    int ret = 0;
    char buf[1024] = {0};
    while(1){
        ret = read(fd, buf, sizeof(buf));
        if(ret == -1){
            perror("read");
            exit(1);
        }
        else if(ret == 0)
            printf("buf is null\n");
        else if(ret > 0)
            printf("buf is %s\n",buf);
        printf("test\n");
        sleep(1);
    }
    close(fd);

    return 0;
}
```
>不會隨時間更新須手動enter輸入
>/dev/tty為終端機位置
* result
```
zxc21949049@ubuntu:~/sp/08-posix/07-nonblocking$ ./blocking1
ffff
buf is ffff

test
qqqq
buf is qqqq

test
```
* nonblocking1.c
```
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
    int fd = open("/dev/tty", O_RDONLY | O_NONBLOCK); // O ﹣ Nonblock set file input and output to non blocking
    if(fd == -1){
        perror("open /dev/tty");
        exit(1);
    }
    int ret = 0;
    char buf[1024] = {0};
    while(1){
        ret = read(fd, buf, sizeof(buf));
        if(ret == -1){
            perror("read /dev/tty"); // fputs(stderr, "read /dev/tty")
            printf("no input,buf is null\n");
        }
        else {
            printf("ret = %d, buf is %s\n",ret, buf);
        }
        sleep(1);
    }
    close(fd);

    return 0;
}
```
>在file open的地方設置nonblock，每隔一秒進行輸入的偵測並輸入
* result
```
zxc21949049@ubuntu:~/sp/08-posix/07-nonblocking$ ./nonblocking1
read /dev/tty: Resource temporarily unavailable
no input,buf is null
read /dev/tty: Resource temporarily unavailable
no input,buf is null
aaa
ret = 4, buf is aaa

aaaa
ret = 5, buf is aaaa
```
* nonblocking2.c
```
```
>與前例不同之處在於利用file control的方式將flag設置成nonblock
* result
```
zxc21949049@ubuntu:~/sp/08-posix/07-nonblocking$ ./nonblocking2
read /dev/tty: Resource temporarily unavailable
no input,buf is null
read /dev/tty: Resource temporarily unavailable
no input,buf is null
aaaaaaa
ret = 8, buf is aaaaaaa

aaaaaaaread /dev/tty: Resource temporarily unavailable
no input,buf is null

aaaaaret = 8, buf is aaaaaaa


aaaaa
ret = 6, buf is aaaaa
```
* time.c
```
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
  while(1) {
    time_t ticks = time(NULL);
    printf("%.24s\n", ctime(&ticks));
    sleep(1);
  }
}

```
>可間隔一秒可讀取一次時間
* result
```
Mon Jun 14 20:28:21 2021
Mon Jun 14 20:28:22 2021
Mon Jun 14 20:28:23 2021
Mon Jun 14 20:28:24 2021
Mon Jun 14 20:28:25 2021
Mon Jun 14 20:28:26 2021
Mon Jun 14 20:28:27 2021
Mon Jun 14 20:28:28 2021
Mon Jun 14 20:28:29 2021
Mon Jun 14 20:28:30 2021
```
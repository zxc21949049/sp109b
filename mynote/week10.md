## 練習
* race.c
```
#include <stdio.h>
#include <pthread.h>

#define LOOPS 100000000
int counter = 0;

void *inc()
{
  for (int i=0; i<LOOPS; i++) {
    counter = counter + 1;
  }
  return NULL;
}

void *dec()
{
  for (int i=0; i<LOOPS; i++) {
    counter = counter - 1;
  }
  return NULL;
}


int main() 
{
  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, inc, NULL);
  pthread_create(&thread2, NULL, dec, NULL);

  pthread_join( thread1, NULL);
  pthread_join( thread2, NULL);
  printf("counter=%d\n", counter);
}
```
* 執行結果
```
ko@ko-VirtualBox:~/sp/08-posix$ cd 02-thread
ko@ko-VirtualBox:~/sp/08-posix/02-thread$ gcc race.c -o race -lpthread
ko@ko-VirtualBox:~/sp/08-posix/02-thread$ ./race
counter=0
ko@ko-VirtualBox:~/sp/08-posix/02-thread$ ./race
counter=2393041
ko@ko-VirtualBox:~/sp/08-posix/02-thread$ ./race
counter=1573276
ko@ko-VirtualBox:~/sp/08-posix/02-thread$ ./race
counter=1896295
```
* norace.c
```
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
#define LOOPS 100000
int counter = 0;

void *inc()
{
  for (int i=0; i<LOOPS; i++) {
    pthread_mutex_lock( &mutex1 );
    counter = counter + 1;
    pthread_mutex_unlock( &mutex1 );
  }
  return NULL;
}

void *dec()
{
  for (int i=0; i<LOOPS; i++) {
    pthread_mutex_lock( &mutex1 );
    counter = counter - 1;
    pthread_mutex_unlock( &mutex1 );
  }
  return NULL;
}


int main() 
{
	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, inc, NULL);
  pthread_create(&thread2, NULL, dec, NULL);

  pthread_join( thread1, NULL);
  pthread_join( thread2, NULL);
  printf("counter=%d\n", counter);
}
```
* 執行結果
```
ko@ko-VirtualBox:~/sp/08-posix/02-thread$ gcc norace.c -o norace -lpthread
ko@ko-VirtualBox:~/sp/08-posix/02-thread$ ./norace
counter=0
ko@ko-VirtualBox:~/sp/08-posix/02-thread$ ./norace
counter=0
```

* deadlock
```
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t x;
pthread_mutex_t y;

void *A(); 
void *B(); 

int main(int argc, char *argv[])
{
    pthread_t threadA, threadB;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_mutex_init(&x, NULL);
    pthread_mutex_init(&y, NULL);

    pthread_create(&threadA, &attr, A, NULL);
    pthread_create(&threadB, &attr, B, NULL);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    pthread_mutex_destroy(&x);
    pthread_mutex_destroy(&y);
}

void *A() 
{
    pthread_mutex_lock(&x);
    printf("A lock x\n");

    sleep(1);
    pthread_mutex_lock(&y);
    printf("A lock y\n");

    pthread_mutex_unlock(&y); 
    pthread_mutex_unlock(&x); 

    printf("finished A\n");

    pthread_exit(0);
}

void *B()
{
    
    pthread_mutex_lock(&y);
    printf("B lock y\n");
    sleep(1);
    pthread_mutex_lock(&x);
    printf("B lock x\n");
    pthread_mutex_unlock(&x);
    pthread_mutex_unlock(&y);

    pthread_exit(0);
}

```
* 執行結果
```
ko@ko-VirtualBox:~/sp/08-posix/02-thread$ gcc deadlock.c -o deadlocd -lpthread
ko@ko-VirtualBox:~/sp/08-posix/02-thread$ ./deadlocd
B lock y
A lock x
^C
```
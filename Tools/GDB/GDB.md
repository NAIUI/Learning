## 参考：GDB调试---bilibili

# 一、如何使用gdb调试coredump文件

## 1、什么coredump文件，怎么产生coredump文件
coredump文件又称之为核心转储文件，进程运行时，突然崩溃的那一瞬间的进程在内存中的一个快照。 会把进程此刻内存、寄存器状态、运行堆栈等信息转储保存在一个文件里
```C
#include <iostream>

int main(){
    int* ptr = nullptr;
    *ptr = 100; //程序运行在这里的时候， 就会发生崩溃。
    return 0;
}
```
### 小结：
1. C/C++程序崩溃的情况下， 可能会产生 coredump文件
2. coredump文件保存了进程崩溃时，内存、寄存器、运行堆栈等等的信息。程序员后续可以通过coredump文件进行查看进程崩溃的原因， 进而修复代码bug


## 2、程序崩溃产生不了coredump文件怎么办？
### core file size
* 当ulimit -a查看的core file size的值
* 当coredump(1000)的大小 < core file size (8000)吗？
  * 小于或者等于 ： 程序崩溃可能会产生coredump文件
    * coredump的大小 < 磁盘空闲空间大小吗？
      * 小于 ： 程序崩溃一定会产生coredump文件
      * 大于 ： 程序一定不会产生coredump文件
  * 大于 ： 程序崩溃一定不会产生coredump文件
* 一般设置core file size的值为 unlimited
  * ulimit  -c unlimited

### 小结：
1. 如果程序崩溃产生不了coredump文件，则排查core file size的值 以及 磁盘空闲空间的大小
2. core file size的值为 unlimited ： ulimit  -c unlimited


## 3、编译一个debug版本的程序， 模拟进程崩溃
```C
#include <iostream>
#include <cstring>

void func(char* ptr){
    //程序运行在这里的时候， 就会发生崩溃。
    strcpy(ptr, "This is test code...");
}

int main(){
    char* ptr = nullptr;
    func(ptr);
    return 0;
}
```
### gdb调试找出bug
* 调试命令
`gdb [binfile] [coredump file]`
* 调试思路
  * 查看调用堆栈，寻找崩溃原因
  * 根据崩溃点，查找代码，分析原因
  * 修复bug

<br/>
<br/>
<br/>

# 二、gdb调试多线程

### 1、代码准备和熟悉

#### 1、模拟一个简单的多线程代码
```C++
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thread_entry_funcA(void* arg){
    int i = 0;
    for(; i < 10; i++){
        printf("[thread_entry_funcA]: %d\n", i);
        sleep(1);
    }
    return NULL;
}

void* thread_entry_funcB(void* arg){
    int i = 0;
    for(; i < 10; i++){
        printf("[thread_entry_funcB]: %d\n", i);
        sleep(1);
    }
    return NULL;
}

int main(){
    pthread_t tidA, tidB;

    int ret = pthread_create(&tidA, NULL, thread_entry_funcA, NULL);
    if(ret < 0){
        perror("pthread_create");
        return 0;
    }

    ret = pthread_create(&tidB, NULL, thread_entry_funcB, NULL);
    if(ret < 0){
        perror("pthread_create");
        return 0;
    }

    pthread_join(tidA, NULL);
    pthread_join(tidB, NULL);
    return 0;
}
```

### 2、编译成为可执行程序(debug版本)
```BASH
[Lynn77@VM-4-12-centos thread_gdb]$ gcc thread_gdb.c -o thread_gdb -lpthread -g
[Lynn77@VM-4-12-centos thread_gdb]$ ls
thread_gdb  thread_gdb.c
[Lynn77@VM-4-12-centos thread_gdb]$
```

### 3、pstack命令 观察多线程
```BASH
[Lynn77@VM-4-12-centos thread_gdb]$ ps aux | grep thread
Lynn77   26477  0.0  0.0  22900   396 pts/3    Sl+  08:48   0:00 ./thread_gdb
Lynn77   26533  0.0  0.0 112816   976 pts/4    S+   08:48   0:00 grep --color=auto thread

[Lynn77@VM-4-12-centos thread_gdb]$ pstack 26477
Thread 3 (Thread 0x7f51a5ed4700 (LWP 26478)):
#0  0x00007f51a5f9a9fd in nanosleep () from /lib64/libc.so.6
#1  0x00007f51a5f9a894 in sleep () from /lib64/libc.so.6
#2  0x00000000004006c0 in thread_entry_funcA (arg=0x0) at thread_gdb.c:9
#3  0x00007f51a62aaea5 in start_thread () from /lib64/libpthread.so.0
#4  0x00007f51a5fd3b0d in clone () from /lib64/libc.so.6
Thread 2 (Thread 0x7f51a56d3700 (LWP 26479)):
#0  0x00007f51a5f9a9fd in nanosleep () from /lib64/libc.so.6
#1  0x00007f51a5f9a894 in sleep () from /lib64/libc.so.6
#2  0x0000000000400704 in thread_entry_funcB (arg=0x0) at thread_gdb.c:18
#3  0x00007f51a62aaea5 in start_thread () from /lib64/libpthread.so.0
#4  0x00007f51a5fd3b0d in clone () from /lib64/libc.so.6
Thread 1 (Thread 0x7f51a66d2740 (LWP 26477)):
#0  0x00007f51a62ac017 in pthread_join () from /lib64/libpthread.so.0
#1  0x0000000000400798 in main () at thread_gdb.c:38
[Lynn77@VM-4-12-centos thread_gdb]$ 
```

## 2、调试程序的技能点
### 1、查看线程信息
```C++
info threads

(gdb) info threads
[New Thread 0x7ffff6fef700 (LWP 3636)]
  Id   Target Id         Frame 
  3    Thread 0x7ffff6fef700 (LWP 3636) "thread_gdb" 0x00007ffff7bcd51c in __lll_lock_wait_private () from /lib64/libpthread.so.0
* 2    Thread 0x7ffff77f0700 (LWP 3635) "thread_gdb" thread_entry_funcA (arg=0x0) at thread_gdb.c:8
  1    Thread 0x7ffff7fec740 (LWP 3631) "thread_gdb" 0x00007ffff78efad1 in clone () from /lib64/libc.so.6
```

### 2、切换线程
```C++
t [线程ID]

C++
(gdb) t 1
[Switching to thread 1 (Thread 0x7ffff7fec740 (LWP 3631))]
#0  0x00007ffff78efad1 in clone () from /lib64/libc.so.6
(gdb) t 2
[Switching to thread 2 (Thread 0x7ffff77f0700 (LWP 3635))]
#0  thread_entry_funcA (arg=0x0) at thread_gdb.c:8
8               printf("[thread_entry_funcA]: %d\n", i);
```

### 3、切换到某一层堆栈
```C++
f [堆栈号]

C++
(gdb) f 0
#0  thread_entry_funcA (arg=0x0) at thread_gdb.c:8
8               printf("[thread_entry_funcA]: %d\n", i);
```

## 3、调度器锁模式
### 1、理解调度器锁模式
调试时除了当前线程在运行，想要规定其他线程的运行情况， 可以使用`set scheduler-locking [mode]`命令来进行设置

有三个选择：
* set scheduler-locking off：不锁定任何线程，所有线程都可以继续执行。
* set scheduler-locking on：只有当前线程可以执行，其他线程暂停运行。
* set scheduler-locking step： 
  * 当单步执行某一线程时，保证在调试过程中当前线程不会发生改变。其他线程也会随着被调试线程的单步执行而执行。 
  * 但如果该模式下执行 continue、until、finish 命令，则其它线程也会执行，并且如果某一线程执行过程遇到断点，则 GDB 调试器会将该线程作为当前线程。
* PS：只有线程创建之后这个命令的暂停效果才有效。

### 2、查看和设置调度器锁
```C++
//查看调度器锁模式
show scheduler-locking 
//mode的取值为off, on， step, 默认为step
set scheduler-locking [mode] 
```
### 3、测试调度器锁为on模式

### 4、测试调度器锁为step模式


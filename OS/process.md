# 一、信号

## 1、信号的基本概念

信号（signal）是软件中断，是进程之间相互传递消息的一种方法，用于通知进程发生了事件，但是，不能给进程传递任何数据。

信号产生的原因有很多，在Linux下，可以用 `kill`和 `killall`命令发送信号。

## 2、信号的类型

| 信号名            | 信号值       | 默认处理动作  | 发出信号的原因                                              |
| ----------------- | ------------ | ------------- | ----------------------------------------------------------- |
| SIGHUP            | 1            | A             | 终端挂起或者控制进程终止                                    |
| **SIGINT**  | **2**  | **A**   | **键盘中断Ctrl+c**                                    |
| SIGQUIT           | 3            | C             | 键盘的退出键被按下                                          |
| SIGILL            | 4            | C             | 非法指令                                                    |
| SIGABRT           | 6            | C             | 由abort(3)发出的退出指令                                    |
| SIGFPE            | 8            | C             | 浮点异常                                                    |
| **SIGKILL** | **9**  | **AEF** | **采用kill -9进程编号 强制杀死程序。**                |
| SIGSEGV           | 11           | C             | 无效的内存引用                                              |
| SIGPIPE           | 13           | A             | 管道破裂，写一个没有读端口的管道。                          |
| **SIGALRM** | **14** | **A**   | **由alarm(2)发出的信号**                              |
| **SIGTERM** | **15** | **A**   | **采用“kill进程编号”或“killall程序名”通知程序。** |
| **SIGUSR1** | **10** | **A**   | **用户自定义信号1**                                   |
| **SIGUSR2** | **12** | **A**   | **用户自定义信号2**                                   |
| **SIGCHLD** | **17** | **B**   | **子进程结束信号**                                    |
| SIGCONT           | 18           |               | 进程继续（曾被停止的进程）                                  |
| SIGSTOP           | 19           | DEF           | 终止进程                                                    |
| SIGTSTP           | 20           | D             | 控制终端（tty）上按下停止键                                 |
| SIGTTIN           | 21           | D             | 后台进程企图从控制终端读                                    |
| SIGTTOU           | 22           | D             | 后台进程企图从控制终端写                                    |

处理动作一项中的字母含义如下

A 缺省的动作是终止进程。

B 缺省的动作是忽略此信号，将该信号丢弃，不做处理。

C 缺省的动作是终止进程并进行内核映像转储（core dump），内核映像转储是指将进程数据在内存的映像和进程在内核结构中的部分内容以一定格式转储到文件系统，并且进程退出执行，这样做的好处是为程序员 提供了方便，使得他们可以得到进程当时执行时的数据值，允许他们确定转储的原因，并且可以调试他们的程序。

D 缺省的动作是停止进程，进入停止状态的程序还能重新继续，一般是在调试的过程中。

E 信号不能被捕获。

F 信号不能被忽略。

## 3、信号的处理

进程对信号的处理方法有三种：

1）对该信号的处理采用系统的默认操作，大部分的信号的默认操作是终止进程。

2）设置中断的处理函数，收到信号后，由该函数来处理。

3）忽略某个信号，对该信号不做任何处理，就像未发生过一样。

`signal`函数可以设置程序对信号的处理方式。

函数声明：

```C
sighandler_t signal(int signum, sighandler_t handler);
```

参数 `signum`表示信号的编号。

参数 `handler`表示信号的处理方式，有三种情况：

1）SIG_DFL：恢复参数 `signum`所指信号的处理方法为默认值。

2）一个自定义的处理信号的函数，信号的编号为这个自定义函数的参数。

3）SIG_IGN：忽略参数 `signum`所指的信号。

## 4、信号有什么用

服务程序运行在后台，如果想让中止它，杀掉不是个好办法，因为程序被杀的时候，程序突然死亡，没有安排善后工作。

如果向服务程序发送一个信号，服务程序收到这个信号后，调用一个函数，在函数中编写善后的代码，程序就可以有计划的退出。

向服务程序发送0的信号，可以检测程序是否存活。

## 5、信号应用示例

在实际开发中，在 `main`函数开始的位置，程序员会先屏蔽掉全部的信号。

```C
for (int ii=1;ii<=64;ii++) signal(ii,SIG_IGN);
```

这么做的目的是不希望程序被干扰。然后，再设置程序员关心的信号的处理函数。

程序在运行的进程中，如果按Ctrl+c，将向程序发出SIGINT信号，编号是2。

采用“`kill 进程编号`”或“`killall 程序名`”向程序发出的是SIGTERM信号，编号是15。

采用“`kill -9 进程编号`”向程序发出的是SIGKILL信号，编号是9，此信号不能被忽略，也无法捕获，程序将突然死亡。

设置SIGINT和SIGTERM两个信号的处理函数，这两个信号可以使用同一个处理函数，函数的代码是释放资源。

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
void EXIT(int sig)
{
  printf("收到了信号%d，程序退出。\n",sig);
  // 在这里添加释放资源的代码
  exit(0);   // 程序退出。
}

int main()
{
  for (int ii=1;ii<=64;ii++) signal(ii,SIG_IGN); // 屏蔽全部的信号

  signal(SIGINT,EXIT);  signal(SIGTERM,EXIT); // 设置SIGINT和SIGTERM的处理函数
  
  while (true)  // 每隔一秒执行一次任务。
  {
    printf("执行了一次任务。\n");
    sleep(1);
  }
}

```

不管是用Ctrl+c还是kill，程序都能体面的退出。

## 6、发送信号

Linux操作系统提供了 `kill`和 `killall`命令向程序发送信号，C语言也提供了kill库函数，用于在程序中向其它进程或者线程发送信号。

函数声明：

```C
int kill(pid_t pid, int sig);
```

kill函数将参数sig指定的信号给参数pid 指定的进程。

参数pid 有几种情况：

1）pid>0 将信号传给进程号为pid 的进程。

2）pid=0 将信号传给和目前进程相同进程组的所有进程，常用于父进程给子进程发送信号，注意，发送信号者进程也会收到自己发出的信号。

3）pid=-1 将信号广播传送给系统内所有的进程，例如系统关机时，会向所有的登录窗口广播关机信息。

sig：准备发送的信号代码，假如其值为零则没有任何信号送出，但是系统会执行错误检查，通常会利用sig值为零来检验某个进程是否仍在运行。

返回值说明： 成功执行时，返回0；失败返回-1，errno被设为以下的某个值。

EINVAL：指定的信号码无效（参数 sig 不合法）。

EPERM：权限不够无法传送信号给指定进程。

ESRCH：参数 pid 所指定的进程或进程组不存在。

# 二、信号量

## 一、信号量的概念

信号量（信号灯）本质上是一个计数器，用于协调多个进程（包括但不限于父子进程）对共享数据对象的读/写。它不以传送数据为目的，主要是用来保护共享资源（共享内存、消息队列、socket连接池、数据库连接池等），保证共享资源在一个时刻只有一个进程独享。

信号量是一个特殊的变量，只允许进程对它进行等待信号和发送信号操作。最简单的信号量是取值0和1的二元信号量，这是信号量最常见的形式。

通用信号量（可以取多个正整数值）和信号量集方面的知识比较复杂，应用场景也比较少。

本文只介绍二元信号量。

## 二、相关函数

Linux中提供了一组函数用于操作信号量，程序中需要包含以下头文件：

```C
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
```

### 1、semget函数

`semget`函数用来获取或创建信号量，它的原型如下：

```C
int semget(key_t key, int nsems, int semflg);
```

1）参数 `key`是信号量的键值，`typedef unsigned int key_t`，是信号量在系统中的编号，不同信号量的编号不能相同，这一点由程序员保证。`key`用十六进制表示比较好。

2）参数 `nsems`是创建信号量集中信号量的个数，该参数只在创建信号量集时有效，这里固定填1。

3）参数 `sem_flags`是一组标志，如果希望信号量不存在时创建一个新的信号量，可以和值IPC_CREAT做按位或操作。如果没有设置IPC_CREAT标志并且信号量不存在，就会返错误（errno的值为2，No such file or directory）。

4）如果 `semget`函数成功，返回信号量集的标识；失败返回-1，错误原因存于error中。

示例：

1）获取键值为0x5000的信号量，如果该信号量不存在，就创建它，代码如下：

```C
int semid=semget(0x5000,1,0640|IPC_CREAT);
```

2）获取键值为0x5000的信号量，如果该信号量不存在，返回-1，errno的值被设置为2，代码如下：

```c
int semid= semget(0x5000,1,0640)；
```

### 2、semctl函数

该函数用来控制信号量（常用于设置信号量的初始值和销毁信号量），它的原型如下：

```C
int semctl(int semid, int sem_num, int command, ...);
```

1）参数 `semid`是由 `semget`函数返回的信号量标识。

2）参数 `sem_num`是信号量集数组上的下标，表示某一个信号量，填0。

3）参数 `cmd`是对信号量操作的命令种类，常用的有以下两个：

**IPC_RMID**：销毁信号量，不需要第四个参数；

**SETVAL**：初始化信号量的值（信号量成功创建后，需要设置初始值），这个值由第四个参数决定。第四参数是一个自定义的共同体，如下：

```C
  // 用于信号灯操作的共同体。
  union semun
  {
    int val;
    struct semid_ds *buf;
    unsigned short *arry;
  };
```

4）如果 `semctl`函数调用失败返回-1；如果成功，返回值比较复杂，暂时不关心它。

示例：

1）销毁信号量。

```C
semctl(semid,0,IPC_RMID);
```

2）初始化信号量的值为1，信号量可用。

```C
union semun sem_union;
sem_union.val = 1;
semctl(semid,0,SETVAL,sem_union);
```

### 3、semop函数

该函数有两个功能：1）等待信号量的值变为1，如果等待成功，立即把信号量的值置为0，这个过程也称之为等待锁；2）把信号量的值置为1，这个过程也称之为释放锁。

```c
int semop(int semid, struct sembuf *sops, unsigned nsops);
```

1）参数 `semid`是由 `semget`函数返回的信号量标识。

2）参数 `nsops`是操作信号量的个数，即 `sops`结构变量的个数，设置它的为1（只对一个信号量的操作）。

3）参数 `sops`是一个结构体，如下：

```C
struct sembuf
{
  short sem_num;   // 信号量集的个数，单个信号量设置为0。
  short sem_op;    // 信号量在本次操作中需要改变的数据：-1-等待操作；1-发送操作。
  short sem_flg;   // 把此标志设置为SEM_UNDO，操作系统将跟踪这个信号量。
                 // 如果当前进程退出时没有释放信号量，操作系统将释放信号量，避免资源被死锁。
};
```

示例：

1）等待信号量的值变为1，如果等待成功，立即把信号量的值置为0；

```c
  struct sembuf sem_b;
  sem_b.sem_num = 0;
  sem_b.sem_op = -1;
  sem_b.sem_flg = SEM_UNDO;
  semop(sem_id, &sem_b, 1);
```

2）把信号量的值置为1。

```C
  struct sembuf sem_b;
  sem_b.sem_num = 0;
  sem_b.sem_op = 1;
  sem_b.sem_flg = SEM_UNDO;
  semop(sem_id, &sem_b, 1);
```

## 三、示例程序

为了便于理解，把信号量的操作封装成CSEM类，称之为信号灯，类似互斥锁，包括初始化信号灯、等待信号灯、挂出信号灯和销毁信号灯。

```C
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>

class CSEM
{
private:
  union semun  // 用于信号灯操作的共同体。
  {
    int val;
    struct semid_ds *buf;
    unsigned short *arry;
  };

  int  sem_id;  // 信号灯描述符。
public:
  bool init(key_t key); // 如果信号灯已存在，获取信号灯；如果信号灯不存在，则创建信号灯并初始化。
  bool wait();          // 等待信号灯挂出。
  bool post();          // 挂出信号灯。
  bool destroy();       // 销毁信号灯。
};
 
int main(int argc, char *argv[])
{
   CSEM sem;

   // 初始信号灯。
   if (sem.init(0x5000)==false) { printf("sem.init failed.\n"); return -1; }
   printf("sem.init ok\n");

   // 等待信信号挂出，等待成功后，将持有锁。
   if (sem.wait()==false) { printf("sem.wait failed.\n"); return -1; }
   printf("sem.wait ok\n");
   sleep(50);  // 在sleep的过程中，运行其它的book259程序将等待锁。
  
   // 挂出信号灯，释放锁。
   if (sem.post()==false) { printf("sem.post failed.\n"); return -1; }
   printf("sem.post ok\n");
  
   // 销毁信号灯。
   // if (sem.destroy()==false) { printf("sem.destroy failed.\n"); return -1; }
   // printf("sem.destroy ok\n");
}
 
bool CSEM::init(key_t key)
{
  // 获取信号灯。
  if ( (sem_id=semget(key,1,0640)) == -1) 
  { 
    // 如果信号灯不存在，创建它。
    if (errno==2) 
    {
      if ( (sem_id=semget(key,1,0640|IPC_CREAT)) == -1) { perror("init 1 semget()"); return false; }
      // 信号灯创建成功后，还需要把它初始化成可用的状态。
      union semun sem_union;
      sem_union.val = 1;
      if (semctl(sem_id,0,SETVAL,sem_union) <  0) { perror("init semctl()"); return false; }
    }
    else
    { perror("init 2 semget()"); return false; }
  }
  return true;
}
 
bool CSEM::destroy()
{
  if (semctl(sem_id,0,IPC_RMID) == -1) { perror("destroy semctl()"); return false; }
  return true;
}
 
bool CSEM::wait()
{
  struct sembuf sem_b;
  sem_b.sem_num = 0;
  sem_b.sem_op = -1; 
  sem_b.sem_flg = SEM_UNDO;
  if (semop(sem_id, &sem_b, 1) == -1) { perror("wait semop()"); return false; }
  
  return true;
}
 
bool CSEM::post()
{
  struct sembuf sem_b;
  sem_b.sem_num = 0;
  sem_b.sem_op = 1;   
  sem_b.sem_flg = SEM_UNDO;
  if (semop(sem_id, &sem_b, 1) == -1) { perror("post semop()"); return false; }
  return true;
}
```

## 四、其它的操作命令

用 `ipcs -s`可以查看系统的信号量，内容有键值（key），信号量编号（semid），创建者（owner），权限（perms），信号量数（nsems）。

用 `ipcrm sem` 信号量编号，可以手工删除信号量，如下：

# 三、共享内存

## 一、共享内存的概念

共享内存（Shared Memory）就是允许多个进程访问同一个内存空间，是在多个进程之间共享和传递数据最高效的方式。操作系统将不同进程之间共享内存安排为同一段物理内存，进程可以将共享内存连接到它们自己的地址空间中，如果某个进程修改了共享内存中的数据，其它的进程读到的数据也将会改变。

共享内存并未提供锁机制，也就是说，在某一个进程对共享内存的进行读写的时候，不会阻止其它的进程对它的读写。如果要对共享内存的读/写加锁，可以使用信号量。

## 二、相关函数

Linux中提供了一组函数用于操作共享内存，程序中需要包含以下头文件：

```C
#include <sys/ipc.h>
#include <sys/shm.h>
```



### 1、shmget函数

`shmget`函数用来获取或创建共享内存，它的声明为：

```C
int shmget(key_t key, size_t size, int shmflg);
```

参数key是共享内存的键值，是一个整数，typedef unsigned int key_t，是共享内存在系统中的编号，不同共享内存的编号不能相同，这一点由程序员保证。key用十六进制表示比较好。

参数size是待创建的共享内存的大小，以字节为单位。

参数shmflg是共享内存的访问权限，与文件的权限一样，0666|IPC_CREAT表示全部用户对它可读写，如果共享内存不存在，就创建一个共享内存。

### 2、shmat函数

把共享内存连接到当前进程的地址空间。它的声明如下：

```c
void *shmat(int shm_id, const void *shm_addr, int shmflg);
```

参数shm_id是由shmget函数返回的共享内存标识。

参数shm_addr指定共享内存连接到当前进程中的地址位置，通常为空，表示让系统来选择共享内存的地址。

参数shm_flg是一组标志位，通常为0。

调用成功时返回一个指向共享内存第一个字节的指针，如果调用失败返回-1.

### 3、shmdt函数

该函数用于将共享内存从当前进程中分离，相当于shmat函数的反操作。它的声明如下：

```c
int shmdt(const void *shmaddr);
```

参数shmaddr是shmat函数返回的地址。

调用成功时返回0，失败时返回-1.

### 4、shmctl函数

删除共享内存，它的声明如下：

```c
int shmctl(int shm_id, int command, struct shmid_ds *buf);
```

参数shm_id是shmget函数返回的共享内存标识符。

参数command填IPC_RMID。

参数buf填0。

解释一下，shmctl是控制共享内存的函数，其功能不只是删除共享内容，但其它的功能没什么用，所以不介绍了。

**注意，用root创建的共享内存，不管创建的权限是什么，普通用户无法删除。**

## 三、示例程序

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
struct st_pid
{
  int  pid;       // 进程编号。
  char name[51];  // 进程名称。
};

int main(int argc,char *argv[])
{
  // 共享内存的标志。
  int shmid;
  
  // 获取或者创建共享内存，键值为0x5005。
  if ( (shmid=shmget(0x5005, sizeof(struct st_pid), 0640|IPC_CREAT))==-1)
  { printf("shmget(0x5005) failed\n"); return -1; }

  // 用于指向共享内存的结构体变量。
  struct st_pid *stpid=0;

  // 把共享内存连接到当前进程的地址空间。
  if ( (stpid=(struct st_pid *)shmat(shmid,0,0))==(void *)-1)
  { printf("shmat failed\n"); return -1; }
  printf("pid=%d,name=%s\n",stpid->pid,stpid->name);
  stpid->pid=getpid();
  strcpy(stpid->name,argv[1]);
  printf("pid=%d,name=%s\n",stpid->pid,stpid->name);

  // 把共享内存从当前进程中分离。
  shmdt(stpid);

  // 删除共享内存。
  // if (shmctl(shmid,IPC_RMID,0)==-1)
  // { printf("shmctl failed\n"); return -1; }

  return 0;
}
```



## 四、其它的操作命令

用`ipcs -m`可以查看系统的共享内存，内容有键值（key），共享内存编号（shmid），创建者（owner），权限（perms），大小（bytes）。

用`ipcrm -m` 共享内存编号，可以手工删除共享内存，如下：

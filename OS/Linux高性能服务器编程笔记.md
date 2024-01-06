## 一、TCP/IP协议族

### 1、数据链路层

```C++
1、ARP协议：IP地址--->物理地址（MAC）
2、arp -a 查看ARP列表
```



## 二、Linux网络编程基础API

### 1、socket

```C++
//1、自Linux内核版本2.6.17起，type参数可接受两标志相与：SOCK_NONBLOCK,SOCK_CLOEXEC,新创建的socket设为非阻塞，用fork调用创建子进程时在子进程中关闭该socket。
int socket(int domain, int type, int protocol);
```

### 2、bind

```C++
//两种常见错误
//EACCES:被绑定的地址是受保护的，仅超级用户能访问。
//EADDRINUSE:被绑定地址正在使用中，如：TIME_WAIT。
int bind(int sockfd, const struct sockaddr* my_addr, socklen_t addrlen);
```

### 3、listen

```C++
int listen(int sockfd, int backlog);
// backlog：内核监听队列的最大长度。Linux2.2前，所有处于半连接状态（SYN_RCVD）和完全连接状态（ESTABLISHED）的socket，后为完全连接，/proc/sys/net/ipv4/tcp_max_syn_backlog内核参数。
```

### 4、close

```C++
int close(int sockfd);
//将fd的引用计数减一，为0时真正关闭。

int shutdown(int sockfd, int howto); // SHUT_RD, SHUT_WR, SHUT_RDWR
//立即终止，而不是计数减一。
```

### 5、地址信息函数

```C++
// 获取socket地址信息
int getsockname(int sockfd, struct sockaddr* address, socklen_t* address_len);
int getpeername(int sockfd, struct sockaddr* address, socklen_t* address_len);
```

### 6、socket选项

```C++
// 读取和设置socket文件描述符属性
int getsockopt(int sockfd, int level, int option_name, 
			  void* option_value, socklen_t* restrict option_len);
int setsockopt(int sockfd, int level, int option_name, 
			  const void* option_value, socklen_t* restrict option_len);

// 强制使用TIME_WAIT状态端口
setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
```



## 三、高级I/O函数

### 1、pipe函数

```C++
1、管道写端文件描述符引用数减少为0，read读端返回0。反之，write写端操作失败，引发SIGPIPE信号。
    
2、Linux 2.6.11 ，管道默认大小65536字节。
```

### 2、dup/dup2函数

```C++
1、创建的文件描述符并不继承原文件描述符的属性，如close-on-exec和non-blocking。
    
// CGI服务器基本工作原理
close(STDOUT_FILENO);	// 关闭标准输出文件描述符
dup(connfd);		    // 返回值为1，系统最小文件描述符
printf("abcd\n");		// 输出到标准输出的内容直接发送到与客户端连接的socket，被客户获得，而非打印在终端。
close(connfd);
```

### 3、sendfile函数

```C++
1、在两个文件描述符之间传递数据（全内核），避免了内核缓冲区与用户缓冲区数据拷贝，零拷贝。

ssize_t sendfile(int out_fd, int in_fd, off_t* offset, size_t count);
// in_fd：待读出内容
// out_fd：待写入内容
// offset：读入文件流的位置，空为默认起始位置。
// count：传输字节数
// in_fd必须为支持类似mmap函数的文件描述符，指向真实的文件，不能为socket或管道；out_fd必须socket。
```

### 4、mmap和munmap函数

```C++
1、用于申请一段内存，可以作为进程间通信的共享内存或将文件直接映射到其中，释放由mmap申请的内存。

void* mmap(void* start, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void* start, size_t length)
```

### 5、splice函数

```C++
1、两个文件描述符中移动数据，零拷贝。
2、fd_in 和 fd_out 必须至少一个为管道文件描述符。
    
ssize_t splice(int fd_in, loff_t* off_in, int fd_out, loff_t* off_out, size_t len, unsigned int flags);

// 将connfd上流入的客户端数据定向到管道中
ret = splice(connfd, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
// 将管道的输出定向到connfd客户端连接文件描述符
ret = splice(pipefd[0], NULL, connfd, NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
```

### 6、tee函数

```C++
1、两个文件描述符中复制数据，零拷贝。
2、fd_in 和 fd_out 必须为管道文件描述符
    
ssize_t tee(int fd_in, int fd_out, size_t len, unsigned int flags);
```

### 7、fcntl函数

```C++
1、对文件描述符的各种控制操作
int fcntl(int fd, int cmd, ...);

// 将一个文件描述符设置为非阻塞
int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}
```



## 四、Linux服务器程序规范

### 1、日志

```C++
应用进程使用syslog函数与rsyslogd守护进程通信。
void syslog(int priority, const char* message, ...);
```

### 2、服务器程序后台化

```C++
bool daemonize()
{
	// 创建子进程，关闭父进程
    pid_t pid = fork();
    if (pid < 0) rerun false;
    if (pid > 0) exit(0);
    
    // 设置文件掩码，当进程创建新文件(open)时，文件权限是mode & 0777
    umask(0);
    
    // 创建新会话，设置本进程为进程组的首领。
    pid_t sid = setsid();
    if (sid < 0) return false;
    
    // 切换工作目录
    if ((chidir("/")) < 0) return false;
    
    // 关闭标准输入设备、标准输出设备和标准错误输出设备
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    // 将标准输入、标准输出和标准错误输出都定向到/dev/bull文件
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);
    return true;
}

// Linux同样功能库函数
int daemon(int nochdir, int noclose);
```



## 五、高性能服务器框架

#### 1、select系统调用

```C++
1、在一段指定时间内，监听用户感兴趣的文件描述符上的可读、可写和异常等事件。
int select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds,
           struct timeval* timeout);
// nfds:被监听的文件描述符的总数。通常为select监听的所有文件描述符中的最大值加1
2、fd_set 结构体：使用宏访问位：
	FD_ZERO(fd_set *fdset);					//  清除fdset的所有位
	FD_SET(int fd, fd_set *fdset);			//	设置fdset的位fd
	FD_CLR(int fd, fd_set *fdset);			//	清除fdset的位fd
	int FD_ISSET(int fd, fd_set *fdset);	//	测试fdset的位fd是否被设置
3、timeval 结构体：
    struct timeval
    {
		long tv_sec;	// 秒
         long tv_usec;	// 微妙
    }
	// 传递NULL，select一直阻塞，直到某个文件描述符就绪
4、select成功返回就绪文件描述符的总数。
```

#### 2、poll系统调用

```C++
int poll(struct pollfd *fds, nfds_t nfds, int timeout);
// fds:结构体数组
	struct pollfd
    {
        int fd;				// 文件描述符
        short events;		// 注册的事件
        short revents;		// 实际发生的事件，内核填充
    }
// nfds:fds的大小
typedef unsigned long int nfds_t;
// timeout:毫秒：-1：阻塞到事件发生；0：poll调用立即返回
```

#### 3、epoll

```C++
1、一组函数而不是一个函数来完成任务。把用户关心的文件描述符上的事件放在内核里的一个事件表，无须像select或poll重复传入文件描述符集或事件集。但需要额外的文件描述符标识时间表。
int epoll_create(int size);

2、操作内核事件表
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
// op:操作类型
//    EPOLL_CTL_ADD:往事件表中注册fd上的事件
//	  EPOLL_CTL_MOD:修改fd上的注册事件
//	  EPOLL_CTL_DEL:删除fd上的注册事件
// event:指定事件
struct epoll_event
{
	_uint32_t events;	// epoll事件
    epoll_data_t data;	// 用户数据
}
typedef union epoll_data
{
	void* ptr;
    int fd;
    uint32_t u32;
    uint64_t u64;
} epoll_data_t;

3、epoll_wait：一段时间内等待一组文件描述符上的事件
int epoll_wait(int epfd, struct epoll_event* events, int maxevents, int timeout);
// 若检测到事件，将所有就绪的事件从内核时间表中复制到events指向的数组。
```

#### 4、LT和ET模式

```C++
1、LT：epoll_wait检测到其上有事件发生并通知应用程序后，可不立即处理。下次再次通知直到处理。
    
2、ET：必须立即处理，后续不再通知。
    
3、ET模式的文件描述符应该是非阻塞的，若阻塞，读或写操作会因为没有后续操作而一直处于阻塞。
```



### 六、信号

#### 1、信号概述

```C++
1、发送信号
int kill(pid_t pid, int sig);

2、信号处理:typedef void (*_sighandler_t) (int);
两种处理方式：
    #define SIG_DFL((_sighandler_t) 0)	// 忽略目标信号
    #define SIG_IGN((_sighandler_t) 1)	// 使用信号的默认处理方式
```

#### 2、信号函数

```C++
1、signal系统调用：为一个信号设置处理函数
    _sighandler_t signal(int sig, _sighandler_t _handler);
    
2、sigaction系统调用
	int sigaction(int sig, const struct sigaction* act, struct sigaction* oact);
	// act:新的信号处理方式
	// oact:信号先前的处理方式
```



### 七、定时器（暂时未看）



### 八、高性能I/O框架库Libevent（...）



### 九、多进程编程

#### 1、处理僵尸进程

```C++
pid_t waitpid(pid_t pid, int* stat_loc, int options);
1、options的取值是WNOHANG时，waitpid调用将是非阻塞的。
    
2、进程结束时，将给父进程发送SIGCHLD信号。父进程可捕获，在信号处理函数中调用waitpid彻底结束子进程。
static void handle_child(int sig)
{
    pid_t pid;
    int stat;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
		// ...
    }
}
```

#### 2、信号量

```C++
1、semget函数
semget函数用来获取或创建信号量，它的原型如下：
int semget(key_t key, int nsems, int semflg);
1）参数key是信号量的键值，typedef unsigned int key_t，是信号量在系统中的编号，不同信号量的编号不能相同，这一点由程序员保证。key用十六进制表示比较好。
2）参数nsems是创建信号量集中信号量的个数，该参数只在创建信号量集时有效，这里固定填1。
3）参数sem_flags是一组标志，如果希望信号量不存在时创建一个新的信号量，可以和值IPC_CREAT做按位或操作。如果没有设置IPC_CREAT标志并且信号量不存在，就会返错误（errno的值为2，No such file or directory）。
4）如果semget函数成功，返回信号量集的标识；失败返回-1，错误原因存于error中。
示例：
1）获取键值为0x5000的信号量，如果该信号量不存在，就创建它，代码如下：
int semid=semget(0x5000,1,0640|IPC_CREAT);  // IPC_EXCL 多进程同时创建
2）获取键值为0x5000的信号量，如果该信号量不存在，返回-1，errno的值被设置为2，代码如下：
int semid= semget(0x5000,1,0640)；

2、semctl函数
该函数用来控制信号量（常用于设置信号量的初始值和销毁信号量），它的原型如下：
int semctl(int semid, int sem_num, int command, ...);
1）参数semid是由semget函数返回的信号量标识。
2）参数sem_num是信号量集数组上的下标，表示某一个信号量，填0。
3）参数cmd是对信号量操作的命令种类，常用的有以下两个：
IPC_RMID：销毁信号量，不需要第四个参数；
SETVAL：初始化信号量的值（信号量成功创建后，需要设置初始值），这个值由第四个参数决定。第四参数是一个自定义的共同体，如下：
  // 用于信号灯操作的共同体。
  union semun
  {
    int val;
    struct semid_ds *buf;
    unsigned short *arry;
  };
4）如果semctl函数调用失败返回-1；如果成功，返回值比较复杂，暂时不关心它。
示例：
1）销毁信号量。
  semctl(semid,0,IPC_RMID);
2）初始化信号量的值为1，信号量可用。
  union semun sem_union;
  sem_union.val = 1;
  semctl(semid,0,SETVAL,sem_union);

3、semop函数
该函数有两个功能：1）等待信号量的值变为1，如果等待成功，立即把信号量的值置为0，这个过程也称之为等待锁；2）把信号量的值置为1，这个过程也称之为释放锁。
int semop(int semid, struct sembuf *sops, unsigned nsops);
1）参数semid是由semget函数返回的信号量标识。
2）参数nsops是操作信号量的个数，即sops结构变量的个数，设置它的为1（只对一个信号量的操作）。
3）参数sops是一个结构体，如下：
struct sembuf
{
  short sem_num;   // 信号量集的个数，单个信号量设置为0。
  short sem_op;    // 信号量在本次操作中需要改变的数据：-1-等待操作；1-发送操作。
  short sem_flg;   // 把此标志设置为SEM_UNDO，操作系统将跟踪这个信号量。
                   // 如果当前进程退出时没有释放信号量，操作系统将释放信号量，避免资源被死锁。
};
示例：
1）等待信号量的值变为1，如果等待成功，立即把信号量的值置为0；
  struct sembuf sem_b;
  sem_b.sem_num = 0;
  sem_b.sem_op = -1;
  sem_b.sem_flg = SEM_UNDO;
  semop(sem_id, &sem_b, 1);
2）把信号量的值置为1。
  struct sembuf sem_b;
  sem_b.sem_num = 0;
  sem_b.sem_op = 1;
  sem_b.sem_flg = SEM_UNDO;
  semop(sem_id, &sem_b, 1);


4、操作命令
ipcs -s：查看系统信号量
ipcrm sem 信号量编号：手动删除
```

#### 3、共享内存

```C++
1.shmget函数：获取或创建共享内存
int shmget(key_t key,  size_t size,  int shmflg);
参数key是共享内存的键值，是一个整数，typedef unsigned int key_t，是共享内存在系统中的编号，不同共享内存的编号不能相同，这一点由程序员保证。key用十六进制表示比较好。
参数size是待创建的共享内存的大小，以字节为单位。
参数shmflg是共享内存的访问权限，与文件的权限一样，0666|IPC_CREAT表示全部用户对它可读写，如果共享内存不存在，就创建一个共享内存。

2.shmat函数：共享内存连接到当前进程的地址空间
void *shmat(int shm_id, const void *shm_addr, int shmflg);
参数shm_id是由shmget函数返回的共享内存标识。
参数shm_addr指定共享内存连接到当前进程中的地址位置，通常为空，表示让系统来选择共享内存的地址。
参数shm_flg是一组标志位，通常为0。
调用成功时返回一个指向共享内存第一个字节的指针，如果调用失败返回-1.

3、shmdt函数：将共享内存从当前进程中分离，相当于shmat函数的反操作
int shmdt(const void *shmaddr);
参数shmaddr是shmat函数返回的地址。
调用成功时返回0，失败时返回-1.

4、shmctl函数：删除共享内存
int shmctl(int shm_id, int command, struct shmid_ds *buf);
参数shm_id是shmget函数返回的共享内存标识符。
参数command填IPC_RMID。
参数buf填0。
解释一下，shmctl是控制共享内存的函数，其功能不只是删除共享内容，但其它的功能没什么用，所以不介绍了。
注意，用root创建的共享内存，不管创建的权限是什么，普通用户无法删除。
    
5.用ipcs -m可以查看系统的共享内存
用ipcrs -m 共享内存编号，可以手工删除共享内存
```

#### 4、调用可执行程序

```C++
1、exec函数族
exec函数族提供了一个在进程中启动另一个程序执行的方法。它可以根据指定的文件名或目录名找到可执行文件，并用它来取代原调用进程的数据段、代码段和堆栈段，在执行完之后，原调用进程的内容除了进程号外，其他全部被新的进程替换了。还有，这里的可执行文件既可以是二进制文件，也可以是Linux下任何可执行的脚本文件。
int execl(const char *path, const char *arg, ...);
int execlp(const char *file, const char *arg, ...);
int execle(const char *path, const char *arg,..., char * const envp[]);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execvpe(const char *file, char *const argv[],char *const envp[]);
// path：要执行的程序路径。可以是绝对路径或者是相对路径。在execv、execl和execle这三个函数中，使用带路径名的文件名作为参数。
// file：要执行的程序名称。如果该参数中包含“/”字符，则视为路径名直接执行；否则视为单独的文件名，系统将根据PATH环境变量指定的路径顺序搜索指定的文件。
// argv：命令行参数的数组。
// envp：带有该参数的exec函数可以在调用时指定一个环境变量数组。其他不带该参数的exec函数则使用调用者进程的环境变量。
// arg：程序的第0个参数，即程序名自身。相当于argv[0]。
// …：命令行参数列表。调用相应程序时有多少命令行参数，就需要有多少个输入参数项。注意：在使用此类函数时，在所有命令行参数的最后应该增加一个空的参数项(NULL)，表明命令行参数结束。
// 如果执行失败则直接返回-1，失败原因存于errno 中。
// 如果执行成功则函数不会返回，这句话可能难以理解，当在主程序中成功调用execl后，被调用的程序将取代调用者程序，也就是说，execl函数之后的代码都不会被执行
// 在实际开发中，最常用的是execl函数，其它的极少使用，我就不介绍了，如果大家认为execl满足不了实际开发的需求，再去研究其它几个函数。

2、system函数
int system(const char * string);
// 调用不成功的代码。
iret=system("/bin/lss -l /usr/include/stdio.h"); 
// 可以调用成功的代码。
iret=system("/bin/ls -l /usr/include/stdio.h"); 
// system会调用fork产生子进程，由子进程来调用/bin/sh -c string来执行参数string字符串所代表的命令，此命令执行完后随即返回原调用的进程。在调用system期间SIGCHLD信号会被暂时搁置，SIGINT和SIGQUIT 信号则会被忽略。
// 如果fork失败 返回-1，出现错误。
// 如果execl失败，表示不能执行shell，返回值相当于shell执行了exit（127）。
// 如果执行成功则返回子shell的终止状态。
// 如果system在调用/bin/sh时失败则返回127，其他失败原因返回-1。若参数string为空指针（NULL），仅当命令处理程序可用时，返回非零值。如果system调用成功则最后会返回执行shell命令后的返回值，但是此返回值也有可能为system调用/bin/sh失败所返回的127，因此最好能再检查errno 来确认执行成功。
```

#### 5、进程清理函数

### 十、多线程编程

#### 1、概念

```C++
线程是程序中完成一个独立任务的完整执行序列，即一个可调度的实体。根据运行环境和调度者的身份，线程可分为内核线程和用户线程。内核线程，在有的系统上也称为LWP(Light weight Process，轻量级进程)，运行在内核空间，由内核来调度﹔用户线程运行在用户空间，由线程库来调度。.当进程的一个内核线程获得CPU的使用权时，它就加载并运行一个用户线程。可见，内核线程相当于用户线程运行的“容器”。一个进程可以拥有M个内核线程和N个用户线程，其中M≤N。并且在一个系统的所有进程中，M和N的比值都是固定的。按照、M:N的取值，线程的实现方式可分为三种模式:完全在用户空间实现、完全由内核调度和双层调度( two level scheduler)。


和多进程相比，多线程是一种比较节省资源的多任务操作方式。启动一个新的进程必须分配给它独立的地址空间，每个进程都有自己的堆栈段和数据段，系统开销比较高，进行数据的传递只能通过进行间通信的方式进行。在同一个进程中，可以运行多个线程，运行于同一个进程中的多个线程，它们彼此之间使用相同的地址空间，共享全局变量和对象，启动一个线程所消耗的资源比启动一个进程所消耗的资源要少。
```

#### 2、线程的使用

```C++
1、pthread_create函数：创建线程
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
// 1、参数thread为为指向线程标识符的地址。
// 2、参数attr用于设置线程属性，一般为空，表示使用默认属性。
// 3、参数start_routine是线程运行函数的地址，填函数名就可以了。
// 4、参数arg是线程运行函数的参数。新创建的线程从start_routine函数的地址开始运行，该函数只有一个无类型指针参数arg。若要想向start_routine传递多个参数，可以将多个参数放在一个结构体中，然后把结构体的地址作为arg参数传入，但是要非常慎重，程序员一般不会这么做。
// 5、在编译时注意加上-lpthread参数，以调用静态链接库。因为pthread并非Linux系统的默认库。

2、pthread_exit函数：终止线程
void pthread_exit(void *retval);    // retval填空，即0
如果进程中的任一线程调用了exit，则整个进程会终止，所以，在线程的start_routine函数中，不能采用exit。
线程的终止有三种方式：
1）线程的start_routine函数代码结束，自然消亡。
2）线程的start_routine函数调用pthread_exit结束。
3）被主进程或其它线程中止。
    
3、多线程的socket服务端
/*
 * 程序名：book261.cpp，此程序用于演示多线程的socket通信服务端
 * 作者：C语言技术网(www.freecplus.net) 日期：20190525
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class CTcpServer
{
public:
  int m_listenfd;   // 服务端用于监听的socket
  int m_clientfd;   // 客户端连上来的socket

  CTcpServer();

  bool InitServer(int port);  // 初始化服务端

  bool Accept();  // 等待客户端的连接

  // 向对端发送报文
  int  Send(const void *buf,const int buflen);
  // 接收对端的报文
  int  Recv(void *buf,const int buflen);

  // void CloseClient();    // 关闭客户端的socket，多线程服务端不需要这个函数。
  // void CloseListen();    // 关闭用于监听的socket，多线程服务端不需要这个函数。

 ~CTcpServer();
};

CTcpServer TcpServer;

// SIGINT和SIGTERM的处理函数
void EXIT(int sig)
{
  printf("程序退出，信号值=%d\n",sig);

  TcpServer.~CTcpServer();  // 手动调用析构函数，释放资源

  exit(0);
}

// 与客户端通信线程的主函数
void *pth_main(void *arg);

int main()
{
  // 忽略全部的信号
  for (int ii=0;ii<50;ii++) signal(ii,SIG_IGN);

  // 设置SIGINT和SIGTERM的处理函数
  signal(SIGINT,EXIT); signal(SIGTERM,EXIT);

  if (TcpServer.InitServer(5051)==false)
  { printf("服务端初始化失败，程序退出。\n"); return -1; }

  while (1)
  {
    if (TcpServer.Accept() == false) continue;

    pthread_t pthid;   // 创建一线程，与新连接上来的客户端通信
    if (pthread_create(&pthid,NULL,pth_main,(void*)((long)TcpServer.m_clientfd))!=0)
    { printf("创建线程失败，程序退出。n"); return -1; }

    printf("与客户端通信的线程已创建。\n");
  }
}

CTcpServer::CTcpServer()
{
  // 构造函数初始化socket
  m_listenfd=m_clientfd=0;
}

CTcpServer::~CTcpServer()
{
  if (m_listenfd!=0) close(m_listenfd);  // 析构函数关闭socket
  if (m_clientfd!=0) close(m_clientfd);  // 析构函数关闭socket
}

// 初始化服务端的socket，port为通信端口
bool CTcpServer::InitServer(int port)
{
  if (m_listenfd!=0) { close(m_listenfd); m_listenfd=0; }

  m_listenfd = socket(AF_INET,SOCK_STREAM,0);  // 创建服务端的socket

  // 把服务端用于通信的地址和端口绑定到socket上
  struct sockaddr_in servaddr;    // 服务端地址信息的数据结构
  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family = AF_INET;  // 协议族，在socket编程中只能是AF_INET
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  // 本主机的任意ip地址
  servaddr.sin_port = htons(port);  // 绑定通信端口
  if (bind(m_listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) != 0 )
  { close(m_listenfd); m_listenfd=0; return false; }

  // 把socket设置为监听模式
  if (listen(m_listenfd,5) != 0 ) { close(m_listenfd); m_listenfd=0; return false; }

  return true;
}

bool CTcpServer::Accept()
{
  if ( (m_clientfd=accept(m_listenfd,0,0)) <= 0) return false;

  return true;
}

int CTcpServer::Send(const void *buf,const int buflen)
{
  return send(m_clientfd,buf,buflen,0);
}

int CTcpServer::Recv(void *buf,const int buflen)
{
  return recv(m_clientfd,buf,buflen,0);
}

// 与客户端通信线程的主函数
void *pth_main(void *arg)
{
  int clientfd=(long) arg; // arg参数为新客户端的socket。

  // 与客户端通信，接收客户端发过来的报文后，回复ok。
  char strbuffer[1024];

  while (1)
  {
    memset(strbuffer,0,sizeof(strbuffer));
    if (recv(clientfd,strbuffer,sizeof(strbuffer),0)<=0) break;
    printf("接收：%s\n",strbuffer);

    strcpy(strbuffer,"ok");
    if (send(clientfd,strbuffer,strlen(strbuffer),0)<=0) break;
    printf("发送：%s\n",strbuffer);
  }

  printf("客户端已断开连接。\n");

  close(clientfd);  // 关闭客户端的连接。

  pthread_exit(0); 
}

需要注意几个问题：
1）线程主函数的函数体中，不能使用return;语句，如果想退出线程，可以用pthread_exit(0);返回。
2）线程可以共享全局变量，当然也可以共享TcpServer的m_clientfd成员变量，但是，创建线程的时候，为什么要把客户端的socket用参数传给线程主函数，而不是直接获取TcpServer.m_clientfd的值，因为主进程调用pthread_create创建线程后，立即返回循环重新Accept，创建线程需要时间，如果在这段时间内有新的客户端连接上来，TcpServer.m_clientfd的值会发生改变。
3）TcpServer.m_clientfd的强制转换，在创建线程的时候，代码如下：
if (pthread_create(&pthid,NULL,pth_main,(void*)((long)TcpServer.m_clientfd))!=0)
线程中的代码如下：
int clientfd=(long) arg; // arg参数为新客户端的socket。
这种数据类型的转换方法可能会让初学者不理解，在学习指针的时候说过，指针是用来存放变量的地址，不能把整数赋给指针，那现在这是怎么回事？这么说吧，C语言很灵活，数据类型可以强制转换，怎么转过去就怎么转回来。
4）book261.cpp程序有一个漏洞，没有保存客户端的socket，主程序退出时，没有关闭客户端的socket，资源没有释放，这么说您可能难以理解，没有关系，等您真的需要编写多线程的socket服务端程序的时候就明白了。
    
3、线程资源的回收
线程有joinable和unjoinable两种状态，如果线程是joinable状态，当线程主函数终止时（自己退出或调用pthread_exit退出）不会释放线程所占用内存资源和其它资源，这种线程被称为“僵尸线程”。创建线程时默认是非分离的，或者称为可连接的（joinable）。
避免僵尸线程就是如何正确的回收线程资源，有四种方法：
1）方法一：创建线程前，调用pthread_attr_setdetachstate将线程设为detached，这样线程退出时，系统自动回收线程资源。
pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);  // 设置线程的属性。
pthread_create(&pthid,&attr,pth_main,(void*)((long)TcpServer.m_clientfd);
2）方法二：创建线程后，在创建线程的程序中调用pthread_detach将新创建的线程设置为detached状态。
pthread_detach(pthid);
3）方法3：创建线程后，在创建线程的程序中调用pthread_join等待线程退出，一般不采用这种方法，因为pthread_join会发生阻塞。
pthread_join(pthid,NULL);
4）方法4：在线程主函数中调用pthread_detach改变自己的状态。
pthread_detach(pthread_self());

4、查看线程
1）在top命令中，如果加上-H参数，top中的每一行显示的不是进程，而是一个线程。
top -H
2）在ps命令中加-xH参数也可以显示线程，加grep可以过滤内容。
ps -xH
ps -xH|grep book261
               
5、应用经验
Linux没有真正意义上的线程，它的实现是由进程来模拟，属于用户级线程。所以，在Linux系统下，进程与线程在性能和资源消耗方面没有本质的差别。进程不能共享全局数据，线程可以共享全局数据，可以根据应用场景选择采用多进程或多线程。
               
6、线程非正常终止
1）如果主线程退出，全部线程将强行终止;
2）在子线程调用exit()将终止整个进程;
3）缺省行为是终止程序的信号将导致整个进程终止。
4）在多进程程序中，子进程Core dump掉不影响其它进程;
5）在多线程程序中，子线程Core dump掉，整个进程玩完。

7、线程优缺点
1）可以在一个进程内实现并发
2）开销少，创建线程比创建进程要快。
3）数据通信、数据共享方便，同时也增加了开发的难度。
               
8、线程终止
1）线程可以简单的从线程函数中返回(return)，返回值是线程的退出码;
2）线程可以被同一进程中的其它线程调用pthread_cancel()取消;
3）在线程函数中，调用pthread_exit()退出。
4）return与pthread_exit区别：线程函数调用其他函数，其他函数体内return返回线程函数，pthread_exit终止该线程。
               
9、线程清理函数
1）线程终止的时候，可以调用清理函数释放资源;
2）清理函数入栈: pthread_cleanup_push();
3）清理函数出栈:pthread_cleanup_pop();
4）pthread_cleanup_push().pthread_cleanup_pop()必须成对书写在同一语句块中;
5）线程终止(return、pthread_exit()、pthreaa_cance))、结束的时候，清理函数将被执行;

10、线程取消
1）线程在运行的过程中，可以调用pthread_cancel()取消它;
2）线程被取消后，返回状态是PTHREAD_CANLeLED，即-l，
3）设置线程的取消状态pthread_setcancelstate();
4）设置线程的取消方式pthread_setcanceltype();
5）设置线程的取消点pthread_testcancel();

11、线程和信号
1）在多线程程序中，外部向进程发送信号不会中断系统调用;
2）在多线程程序中，信号的处理是所有线程共享的;
3）进程中的信号可以送达单个线程(pthread_kill)，会中断系统调用;
4）如果某线程因为信号而终止，整个进程将终止。
    
5）比signal()更强大的sigaction()函数;
6）进程信号屏蔽sigprocmask()，线程pthread_sigmask();
7）其它信号处理函数: sigwait()、sigwaitinfo()、sigtimedwait).

```

#### 3、线程同步

```C++
1、线程的锁的种类有互斥锁、自旋锁、读写锁、条件变量、信号量、生产消费者模型。
    
2、互斥锁：互斥锁机制是同一时刻只允许一个线程占有共享的资源。
1）加锁和解锁，确保同一时间只有一个线程访问共享资源;
2）访问共享资源之前加锁，访问完成后释放锁;
3）如果某线程持有锁，其它的线程形成等待队列。
pthread_mutex_t mutex; 			// 声明锁
int pthread_mutex_init();		// 初始化锁
int pthread_mutex_lock();		// 等待并加锁
int pthread_mutex_trylock();	// 尝试加锁，不等待
int pthread_mutex_timedlock();	// 带超时机制的加锁
int pthread_mutex_unlock();		// 解锁
int pthread_mutex_destroy();	// 销毁锁

3、自旋锁
pthread_spinlock_t mutex;		// 声明锁
int pthread_spin_init();		// 初始化锁
int pthread_spin_lock();		// 等待并加锁
int pthread_spin_trylock();		// 尝试加锁，不等待
int pthread_spin_unlock();		// 解锁
int pthread_spin_destroy();		// 销毁锁

4、读写锁
1）读写锁允许更高的并发性;
2）三种状态:读模式加锁、写模式加锁和不加锁。
3）只要没有线程持有写锁，任意线程都可以成功申请读锁;
4）只有在不加锁状态时，才能成功申请写锁。
5）读写锁适合于对读的次数远大于写的情况;
6）Linux系统优先考虑读锁，这种实现方式有可能导致写入线程饿死的情况。
int pthread_rwlock_rdlock();		// 申请读锁
int pthread_rwlock_tryrdlock();		// 尝试申请读锁，不阻塞
int pthread_rwlock_timedrdlock();	// 申请读锁，带超时机制
int pthread_rwlock_wrlock();		// 申请写锁
int pthread_rwlock_trywrlock();		// 尝试申请写锁，不阻塞
int pthread_rwlock_timedwrlock();	// 申请写锁，带超时机制
int pthread_rwlock_unlock();		// 解锁
int pthread_rwlockattr_getpshared();// 获取读写锁属性
int pthread_rwlockattr_setpshared();// 设置读写锁属性
PTHREAD_PROXESS_PRIVATE、PTHREAD_PROCESS_SHARED
7）只要没有线程持有写锁，任意线程都可以成功申请读锁;
8）只有在不加锁状态时，才能成功申请写锁。

5、条件变量
pthread_cond_t cond;					// 声明条件变量
int pthread_cond_init();				// 初始化条件变量
int pthread_cond_destroy();				// 销毁条件变量。
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int pthread_cond_wait(&cond,&mutex);	// 等待被唤醒
1）把互斥锁解锁;
2)阻塞，等待条件（被唤醒);
3)条件被触发+给互斥锁加锁。
int pthread_cond_timedwait(); 			// 等待被唤醒，带超时机制
int pthread_cond_signal();				// 唤醒一个等待中的线程
int pthread_cond_broadcast();			// 唤醒全部等待中的线程
int pthread_condattr_getpshared();		// 获取共享属性
int pthread_condattr_setpshared(); 		// 设置共享属性
int pthread_condattr_getclock();		// 获取时钟属性
int pthread_condattr_setclock();		// 设置时钟属性

6、信号量：可实现互斥锁的功能
API略

7、公平锁和写优先锁

8、编程区别：参数传递、资源回收、信号处理、通讯方式
   C++11线程
    线程属性：优先级、CPU亲缘性
    
3、初始化锁
int pthread_mutex_init(pthread_mutex_t *mutex,const pthread_mutex_attr_t *mutexattr);
其中参数 mutexattr 用于指定锁的属性（见下），如果为NULL则使用缺省属性。
互斥锁的属性在创建锁的时候指定，当资源被某线程锁住的时候，其它的线程在试图加锁时表现将不同。当前有四个值可供选择：
1）PTHREAD_MUTEX_TIMED_NP，这是缺省值，也就是普通锁。当一个线程加锁以后，其余请求锁的线程将形成一个等待队列，并在解锁后按优先级获得锁。这种锁策略保证了资源分配的公平性。
2）PTHREAD_MUTEX_RECURSIVE_NP，嵌套锁，允许同一个线程对同一个锁成功获得多次，并通过多次unlock解锁。
3）PTHREAD_MUTEX_ERRORCHECK_NP，检错锁，如果同一个线程请求同一个锁，则返回EDEADLK，否则与PTHREAD_MUTEX_TIMED_NP类型动作相同。
4）PTHREAD_MUTEX_ADAPTIVE_NP，适应锁，动作最简单的锁类型，等待解锁后重新竞争。

4、阻塞加锁
// 如果是锁是空闲状态，本线程将获得这个锁；如果锁已经被占据，本线程将排队等待，直到成功的获取锁。
int pthread_mutex_lock(pthread_mutex *mutex);

5、非阻塞加锁
int pthread_mutex_trylock( pthread_mutex_t *mutex);
// 该函数语义与 pthread_mutex_lock() 类似，不同的是在锁已经被占据时立即返回EBUSY，不是挂起等待。

6、解锁
// 线程把自己持有的锁释放。
int pthread_mutex_unlock(pthread_mutex *mutex);

7、毁锁（此时锁必需unlock状态，否则返回EBUSY）
// 销毁锁之前，锁必需是空闲状态（unlock）。
int pthread_mutex_destroy(pthread_mutex *mutex);
```

#### 4、线程安全

```
1）多个线程访问共享资源（全局和静态)的时候会冲突;
2）三个概念:原子性、可见性和顺序性;

如何解决线程安全？？？
1、volatile关键字
1）保证了变量的内存可见性;
2）禁止代码重排序;
3）不是原子的

2、原子操作
1）本质是总线锁;
2）三条汇编指令:xadd、cmpxchg或xchg;
3）硬件级别的锁。
返回原值并操作
type __sync_fetch_and_add (type *ptr, type value);	// i++
type _sync_fetch_and_sub (type *ptr, type value);	// i--
type_sync_fetch_and_or (type *ptr, type value);		// or
type_sync_fetch_and_and (type *ptr, type value);	// and
type _sync_fetch_and_nand (type *ptr, type value); 	// not and,(not a or b)
type_sync_fetch_and_xor (type *ptr, type value);	// xor
操作并返回操作后的值
type_sync_add_and_fetch (type *ptr, type value);	// ++i
type _sync_sub_and_fetch (type *ptr, type value);	// --i
type _sync_or_and_fetch (type *ptr, type value);	// or
type _sync_and_and_fetch (type *ptr, type value); 	// and
type_sync_nand_and_fetch (type *ptr, type value); 	// not and,(not a or b)
type_sync_xor_and_fetch (type *ptr, type value);	// xor
CAS指令(compare and swap)
bool _sync_bool_compare_and_swap(type *ptr,type oldval,type newval);
type_sync_val_compare_and_swap(type *ptr,type oldval,type newval);
读出*ptr的值，如果*ptr == oldval，就将newval写入*ptr。
第一个函数在相等并写入的情况下返回true。
第二个函数在返回操作之前的值。

C11原子类型
std::atomic模板类封装了原子操作，支持布尔、整数和字符。

3、线程同步（锁）
```







### 十一、单例模式

```C++
// 懒汉模式
class singleClass
{
public:
    static singleClass* getinstance()
    {
		if (instance == nullptr)
        {
            i_mutex.lock();
            if (instance == nullptr)
            {
				instance = new singleClass();
            }
            i_mutex.unlock();
        }
        return instance;
    }
private:
    static singleClass* instance;
    static mutex i_mutex;
    singleClass(){};
};
singleClass* singleClass::instance = nullptr;
mutex singleClass::i_mutex;


// 饿汉模式
class singleClass
{
public:
    static singleClass* getinstance()
    {
        return instance;
    }
private:
    static singleClass* instance;
    singleClass(){};
};
singleClass* singleClass::instance = new singleClass;
```


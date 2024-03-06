# 目录操作

## 一、获取当前工作目录

shell中我们可以直接输入命令pwd 来显示当前的工作目录，在C程序中调用getcwd函数可以获取当前的工作目录。函数声明： 

`char *getcwd(char * buf,size_t size);`

 `getcwd`函数把当前工作目录存入`buf`中，如果目录名超出了参数`size`长度，函数返回`NULL`，如果成功，返回`buf`。例如：

```C
char strpwd[301];  
memset(strpwd,0,sizeof(strpwd));  
getcwd(strpwd,300);  
printf("当前目录是：%s\n",strpwd);
```


## 二、切换工作目录

函数声明：

`int chdir(const char *path);`

就像我们在`shell`中使用`cd`命令切换目录一样，在C程序中使用`chdir`函数来改变工作目录。

返回值：0-切换成功；非0-失败。

## 三、目录的创建和删除

 在`shell`中可以通过`mkdir/rmdir`命令来创建/删除目录，C程序中用`mkdir/rmdir`函数来创建/删除目录。

创建目录函数的声明：

`int mkdir(const char *pathname, mode_t mode);`

`mode`的含义将按`open`系统调用的`O_CREAT`选项中的有关定义设置，当然，它还要服从`umask`的设置况，是不是看不明白？那先固定填0755，注意，0不要省略哦，它表示八进制。  例如：

`  mkdir("/tmp/aaa",0755);   // 创建/tmp/aaa目录`

删除目录函数的声明：

`int rmdir(const char *pathname);`

## 四、获取目录中的文件列表

在实际开发中，文件是存放在目录中的，在处理文件之前，必须先知道目录中有哪些文件，所以要获取目录中的文件列表。涉及到的库函数如下：

### 1、包含头文件

`#include <dirent.h>`

### 2、相关的库函数

打开目录的函数opendir的声明：

`DIR *opendir(const char *pathname);`

读取目录的函数readdir的声明：

`struct dirent *readdir(DIR *dirp);`

关闭目录的函数closedir的声明：

`int closedir(DIR *dirp);`

### 3、数据结构

1）目录指针DIR

`DIR *目录指针名;`

2）struct dirent结构体

每调用一次`readdir`函数会返回一个`struct dirent`的地址，存放了本次读取到的内容，它的原理与`fgets`函数读取文件相同。

```c
struct dirent
{
   long d_ino;                    // inode number 索引节点号
   off_t d_off;                   // offset to this dirent 在目录文件中的偏移 
   unsigned short d_reclen;     // length of this d_name 文件名长 
   unsigned char d_type;         // the type of d_name 文件类型
   char d_name [NAME_MAX+1];    // file name文件名，最长255字符
};
```


我们只需要关注结构体的`d_type`和`d_name`成员，其它的不必关心。

`d_name`文件名或目录名。

`d_type`描述了文件的类型，有多种取值，最重要的是8和4，`8-常规文件（A regular file）；4-目录（A directory）`，其它的暂时不关心。


# 相关库函数

## 一、access库函数

access函数用于判断当前操作系统用户对文件或目录的存取权限。

包含头文件：

`#include <unistd.h>`

函数声明：

`int access(const char *pathname, int mode);`

参数说明：

pathname文件名或目录名，可以是当前目录的文件或目录，也可以列出全路径。

mode需要判断的存取权限。在头文件unistd.h中的预定义如下：

```C
#define R_OK 4     // R_OK 只判断是否有读权限
#define W_OK 2    // W_OK 只判断是否有写权限
#define X_OK 1     // X_OK 判断是否有执行权限
#define F_OK 0     // F_OK 只判断是否存在
```

返回值：

当pathname满足mode的条件时候返回0，不满足返回-1。

在实际开发中，access函数主要用于判断文件或目录是否是存在。

## 二、stat库函数

### 1、stat结构体

`struct stat`结构体用于存放文件和目录的状态信息，如下：

```C
struct stat
{
  dev_t st_dev;   // device 文件的设备编
  ino_t st_ino;   // inode 文件的i-node
  mode_t st_mode;   // protection 文件的类型和存取的权限
  nlink_t st_nlink;   // number of hard links 连到该文件的硬连接数目, 刚建立的文件值为1.
  uid_t st_uid;   // user ID of owner 文件所有者的用户识别码
  gid_t st_gid;   // group ID of owner 文件所有者的组识别码
  dev_t st_rdev;  // device type 若此文件为设备文件, 则为其设备编号
  off_t st_size;  // total size, in bytes 文件大小, 以字节计算
  unsigned long st_blksize;  // blocksize for filesystem I/O 文件系统的I/O 缓冲区大小.
  unsigned long st_blocks;  // number of blocks allocated 占用文件区块的个数, 每一区块大小为512 个字节.
  time_t st_atime;  // time of lastaccess 文件最近一次被存取或被执行的时间, 一般只有在用mknod、 utime、read、write 与tructate 时改变.
  time_t st_mtime;  // time of last modification 文件最后一次被修改的时间, 一般只有在用mknod、 utime 和write 时才会改变
  time_t st_ctime;  // time of last change i-node 最近一次被更改的时间, 此参数会在文件所有者、组、 权限被更改时更新
};
```

struct stat结构体的成员变量比较多，对程序员来说，重点关注`st_mode`、`st_size`和`st_mtime`成员就可以了。注意`st_mtime`是一个整数表达的时间，需要程序员自己写代码转换格式。

`st_mode`成员的取值很多，或者使用如下两个宏来判断。

```C
S_ISREG(st_mode)//是否为一般文件
S_ISDIR(st_mode)//是否为目录
```


### 2、stat库函数

包含头文件：

```C
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
```

函数声明：

`int stat(const char *path, struct stat *buf);`

`stat`函数获取 `path`指定文件或目录的信息，并将信息保存到结构体 `buf`中，执行成功返回0，失败返回-1。

## 三、utime库函数

`utime`函数用于修改文件的存取时间和更改时间。

包含头文件：

`#include <utime.h>`

函数声明：

`int utime(const char *filename, const struct utimbuf *times);`

函数说明：`utime()`用来修改参数`filename `文件所属的`inode `存取时间。如果参数`times`为空指针`(NULL)`, 则该文件的存取时间和更改时间全部会设为目前时间。结构`utimbuf `定义如下：

```C
struct utimbuf
{
  time_t actime;
  time_t modtime;
};
```

返回值：执行成功则返回0，失败返回-1。

## 四、rename库函数

`rename`函数用于重命名文件或目录，相当于操作系统的`mv`命令，对程序员来说，在程序中极少重命名目录，但重命名文件是经常用到的功能。

包含头文件：

`#include <stdio.h>`

函数声明：

`int rename(const char *oldpath, const char *newpath);`

参数说明：

`oldpath `文件或目录的原名。

`newpath `文件或目录的新的名称。

返回值：0-成功，-1-失败。

## 五、remove库函数

`remove`函数用于删除文件或目录，相当于操作系统的`rm`命令。

包含头文件：

`#include <stdio.h>`

函数声明：

`int remove(const char *pathname);`

参数说明：

`pathname `待删除的文件或目录名。

返回值：0-成功，-1-失败。


# 时间操作

UNIX操作系统根据计算机产生的年代和应用采用1970年1月1日作为UNIX的纪元时间，1970年1月1日0点作为计算机表示时间的是中间点，将从1970年1月1日开始经过的秒数用一个整数存放，这种高效简洁的时间表示方法被称为“Unix时间纪元”，向左和向右偏移都可以得到更早或者更后的时间。

在实际开发中，对日期和时间的操作场景非常多，例如程序启动和退出的时间，程序执行任务的时间，数据生成的时间，数据处理的各环节的时间等，无处不在。

在学习时间之前，请把Linux操作系统的时区设置为中国上海时间。

## 一、time_t别名

在C语言中，用`time_t`来表示时间数据类型，它是一个`long`（长整数）类型的别名，在`time.h`文件中定义，表示一个日历时间，是从1970年1月1日0时0分0秒到现在的秒数。

`typedef long time_t;`

## 二、time库函数

`time`函数的用途是返回一个值，也就是从1970年1月1日0时0分0秒到现在的秒数。

`time`函数是C语言标准库中的函数，在 `time.h`文件中声明。

`time_t time(time_t *t);`

`time`函数有两种调用方法：

```C
time_t tnow;
tnow =time(0);     // 将空地址传递给time函数，并将time返回值赋给变量tnow
```

或

```C
time(&tnow);       // 将变量tnow的地址作为参数传递给time函数
```

您可以写代码测试一下这两种方式，效果完全相同。

## 三、tm结构体

`time_t`只是一个长整型，不符合我们的使用习惯，需要转换成可以方便表示时间的结构体，即`tm`结构体，`tm`结构体在`time.h`中声明，如下：

```C
struct tm
{
  int tm_sec;     // 秒：取值区间为[0,59] 
  int tm_min;     // 分：取值区间为[0,59] 
  int tm_hour;    // 时：取值区间为[0,23] 
  int tm_mday;    // 日期：一个月中的日期：取值区间为[1,31]
  int tm_mon;     // 月份：（从一月开始，0代表一月），取值区间为[0,11]
  int tm_year;    // 年份：其值等于实际年份减去1900
  int tm_wday;    // 星期：取值区间为[0,6]，其中0代表星期天，1代表星期一，以此类推 
  int tm_yday;    // 从每年的1月1日开始的天数：取值区间为[0,365]，其中0代表1月1日，1代表1月2日，以此类推 
  int tm_isdst;   // 夏令时标识符，该字段意义不大，我们不用夏令时。
};
```

这个结构定义了年、月、日、时、分、秒、星期、当年中的某一天、夏令时。用这个结构体可以很方便的显示时间。

## 四、localtime库函数

`localtime`函数用于把`time_t`表示的时间转换为`struct tm`结构体表示的时间，函数返回`struct tm`结构体的地址。

函数声明：

```C
 struct tm * localtime(const time_t *);
```

`struct tm`结构体包含了时间的各要素，但还不是我们习惯的时间表达方式，我们可以用格式化输出`printf`、`sprintf`或`fprintf`等函数，把`struct tm`结构体转换为我们想要的结果。

```C
#include <stdio.h>
#include <time.h>

int main(int argc,char *argv[])
{
  time_t tnow;
  tnow=time(0);      // 获取当前时间
  printf("tnow=%lu\n",tnow);   // 输出整数表示的时间

  struct tm *sttm;  
  sttm=localtime(&tnow);  // 把整数的时间转换为struct tm结构体的时间

  // yyyy-mm-dd hh24:mi:ss格式输出，此格式用得最多
  printf("%04u-%02u-%02u %02u:%02u:%02u\n",sttm->tm_year+1900,sttm->tm_mon+1,\
          sttm->tm_mday,sttm->tm_hour,sttm->tm_min,sttm->tm_sec);

  printf("%04u年%02u月%02u日%02u时%02u分%02u秒\n",sttm->tm_year+1900,\
          sttm->tm_mon+1,sttm->tm_mday,sttm->tm_hour,sttm->tm_min,sttm->tm_sec);

  // 只输出年月日
  printf("%04u-%02u-%02u\n",sttm->tm_year+1900,sttm->tm_mon+1,sttm->tm_mday); 
}
```

## 五、mktime库函数

`mktime`函数的功能与`localtime`函数相反。

`localtime`函数用于把`time_t`表示的时间转换为`struct tm`表示的时间。

`mktime ` 函数用于把`struct tm`表示的时间转换为`time_t`表示的时间。

```C
time_t mktime(struct tm *tm);
```

函数返回`time_t`的值。

## 六、程序睡眠

在实际开发中，我们经常需要把程序挂起一段时间，可以使用`sleep`和`usleep`两个库函数，需要包含`unistd.h`头文件中。函数的声明如下：

```C
unsigned int sleep(unsigned int seconds);
int usleep(useconds_t usec);
```

`sleep`函数的参数是秒，`usleep`函数的参数是微秒，1秒=1000000微秒。

​	不关心sleep和usleep函数的返回值。

## 七、精确到微秒的计时器

### 1、精确到微秒的timeval结构体

`timeval`结构体在`sys/time.h`文件中定义，声明为：

```C
struct timeval
{
  long  tv_sec;  // 1970年1月1日到现在的秒。
  long  tv_usec; // 当前秒的微妙，即百万分之一秒。
};
```



### 2、时区timezone 结构体

`timezone` 结构体在`sys/time.h`文件中定义，声明为：

```C
struct timezone
{
  int tz_minuteswest;  // 和UTC（格林威治时间）差了多少分钟。
  int tz_dsttime;      // type of DST correction，修正参数据，忽略
};
```



### 3、gettimeofday库函数

`gettimeofday`是获得当前的秒和微秒的时间，其中的秒是指1970年1月1日到现在的秒，微秒是指当前秒已逝去的微秒数，可以用于程序的计时。调用`gettimeofday`函数需要包含`sys/time.h`头文件。

函数声明：

```C
int gettimeofday(struct  timeval *tv, struct  timezone *tz )
```

当前的时间存放在`tv `结构体中，当地时区的信息则放到tz所指的结构体中，`tz`可以为空。

函数执行成功后返回0，失败后返回-1。

在使用`gettimeofday()`函数时，第二个参数一般都为空，我们一般都只是为了获得当前时间，不关心时区的信息。

还有一个要注意的问题，`time.h `是ISO C99 标准日期时间头文件。`sys/time.h` 是Linux 系统的日期时间头文件，也就是说，`timeval`、`timezone`结构体和`gettimeofday`函数在windows平台中不能使用。



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



# 九、多进程编程

# 一、信号

## 1、信号的基本概念

信号（signal）是软件中断，是进程之间相互传递消息的一种方法，用于通知进程发生了事件，但是，不能给进程传递任何数据。

信号产生的原因有很多，在Linux下，可以用 `kill`和 `killall`命令发送信号。

## 2、信号的类型

| 信号名      | 信号值 | 默认处理动作 | 发出信号的原因                                    |
| ----------- | ------ | ------------ | ------------------------------------------------- |
| SIGHUP      | 1      | A            | 终端挂起或者控制进程终止                          |
| **SIGINT**  | **2**  | **A**        | **键盘中断Ctrl+c**                                |
| SIGQUIT     | 3      | C            | 键盘的退出键被按下                                |
| SIGILL      | 4      | C            | 非法指令                                          |
| SIGABRT     | 6      | C            | 由abort(3)发出的退出指令                          |
| SIGFPE      | 8      | C            | 浮点异常                                          |
| **SIGKILL** | **9**  | **AEF**      | **采用kill -9进程编号 强制杀死程序。**            |
| SIGSEGV     | 11     | C            | 无效的内存引用                                    |
| SIGPIPE     | 13     | A            | 管道破裂，写一个没有读端口的管道。                |
| **SIGALRM** | **14** | **A**        | **由alarm(2)发出的信号**                          |
| **SIGTERM** | **15** | **A**        | **采用“kill进程编号”或“killall程序名”通知程序。** |
| **SIGUSR1** | **10** | **A**        | **用户自定义信号1**                               |
| **SIGUSR2** | **12** | **A**        | **用户自定义信号2**                               |
| **SIGCHLD** | **17** | **B**        | **子进程结束信号**                                |
| SIGCONT     | 18     |              | 进程继续（曾被停止的进程）                        |
| SIGSTOP     | 19     | DEF          | 终止进程                                          |
| SIGTSTP     | 20     | D            | 控制终端（tty）上按下停止键                       |
| SIGTTIN     | 21     | D            | 后台进程企图从控制终端读                          |
| SIGTTOU     | 22     | D            | 后台进程企图从控制终端写                          |

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
1、sighandler_t signal(int signum, sighandler_t handler);

2、信号处理:typedef void (*_sighandler_t) (int);
两种处理方式：
    #define SIG_DFL((_sighandler_t) 0)	// 忽略目标信号
    #define SIG_IGN((_sighandler_t) 1)	// 使用信号的默认处理方式
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

### 四、其它的操作命令

用 `ipcs -s`可以查看系统的信号量，内容有键值（key），信号量编号（semid），创建者（owner），权限（perms），信号量数（nsems）。

用 `ipcrm sem` 信号量编号，可以手工删除信号量，如下：

## 三、共享内存

### 一、共享内存的概念

共享内存（Shared Memory）就是允许多个进程访问同一个内存空间，是在多个进程之间共享和传递数据最高效的方式。操作系统将不同进程之间共享内存安排为同一段物理内存，进程可以将共享内存连接到它们自己的地址空间中，如果某个进程修改了共享内存中的数据，其它的进程读到的数据也将会改变。

共享内存并未提供锁机制，也就是说，在某一个进程对共享内存的进行读写的时候，不会阻止其它的进程对它的读写。如果要对共享内存的读/写加锁，可以使用信号量。

### 二、相关函数

Linux中提供了一组函数用于操作共享内存，程序中需要包含以下头文件：

```C
#include <sys/ipc.h>
#include <sys/shm.h>
```



#### 1、shmget函数

`shmget`函数用来获取或创建共享内存，它的声明为：

```C
int shmget(key_t key, size_t size, int shmflg);
```

参数key是共享内存的键值，是一个整数，typedef unsigned int key_t，是共享内存在系统中的编号，不同共享内存的编号不能相同，这一点由程序员保证。key用十六进制表示比较好。

参数size是待创建的共享内存的大小，以字节为单位。

参数shmflg是共享内存的访问权限，与文件的权限一样，0666|IPC_CREAT表示全部用户对它可读写，如果共享内存不存在，就创建一个共享内存。

#### 2、shmat函数

把共享内存连接到当前进程的地址空间。它的声明如下：

```c
void *shmat(int shm_id, const void *shm_addr, int shmflg);
```

参数shm_id是由shmget函数返回的共享内存标识。

参数shm_addr指定共享内存连接到当前进程中的地址位置，通常为空，表示让系统来选择共享内存的地址。

参数shm_flg是一组标志位，通常为0。

调用成功时返回一个指向共享内存第一个字节的指针，如果调用失败返回-1.

#### 3、shmdt函数

该函数用于将共享内存从当前进程中分离，相当于shmat函数的反操作。它的声明如下：

```c
int shmdt(const void *shmaddr);
```

参数shmaddr是shmat函数返回的地址。

调用成功时返回0，失败时返回-1.

#### 4、shmctl函数

删除共享内存，它的声明如下：

```c
int shmctl(int shm_id, int command, struct shmid_ds *buf);
```

参数shm_id是shmget函数返回的共享内存标识符。

参数command填IPC_RMID。

参数buf填0。

解释一下，shmctl是控制共享内存的函数，其功能不只是删除共享内容，但其它的功能没什么用，所以不介绍了。

**注意，用root创建的共享内存，不管创建的权限是什么，普通用户无法删除。**

### 三、示例程序

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



### 四、其它的操作命令

用`ipcs -m`可以查看系统的共享内存，内容有键值（key），共享内存编号（shmid），创建者（owner），权限（perms），大小（bytes）。

用`ipcrm -m` 共享内存编号，可以手工删除共享内存，如下：



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



#### 2、调用可执行程序

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

#### 3、进程清理函数





# 十、多线程编程

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


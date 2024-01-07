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

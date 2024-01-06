# MySQL案例实战教程

## 案例1：MySQL的安装和基本使用

安装需要设置编码为UTF-8，管理用户root,密码设置root或123456

## 案例2：MySQL的数据类型

MySQL支持多种类型，大致可以分为三类：数值、日期/时间和字符串(字符)类型。

备注:char和varchar一定要指定长度，float会自动提升为double，timestamp是时间的混合类型，理论上可以存储时间格式和时间戳。

| 类型      | 用途                               |
| --------- | ---------------------------------- |
| int       | 整型，相当于java的int              |
| bigint    | 整型，相当于java的long             |
| float     | 浮点型                             |
| double    | 浮点型                             |
| datetime  | 日期类型                           |
| timestamp | 日期类型（可存储时间戳）           |
| char      | 定长字符                           |
| varchar   | 不定长字符                         |
| text      | 大文本，用于存储很长的字符内容     |
| blob      | 字节数据类型，存储图片、音频等文件 |

## 案例3：建表操作

语法

```mysql
--删除表
DROPTABLEIFEXISTS表名;

--新建表
createtable表名(
	字段名 类型 约束（主键，非空，唯一，默认值），
	字段名 类型 约束（主键，非空，唯一，默认值），
)编码，存储引擎；
```



在SQL中，我们有如下约束：

`NOTNULL`-指示某列不能存储NULL值。

`UNIQUE`-保证某列的每行必须有唯一的值。

`PRIMARYKEY-NOTNULL`和`UNIQUE`的结合。确保某列（或两个列多个列的结合）有唯一标识，有助于更容易更快速地找到表中的一个特定的记录。

`FOREIGNKEY`-保证一个表中的数据匹配另一个表中的值的参照完整性。

`CHECK-`保证列中的值符合指定的条件。

`DEFAULT`-规定没有给列赋值时的默认值。

实例

```mysql
DROP  TABLE  IF  EXISTS  `websites`; 
CREATE  TABLE  `websites`  (
	id  int(11)  NOT  NULL  AUTO_INCREMENT,
	name  char(20)  NOT  NULL  DEFAULT  ''  COMMENT  '站点名称',
	url  varchar(255)  NOT  NULL  DEFAULT  '',
	alexa  int(11)  NOT  NULL  DEFAULT  '0'  COMMENT  'Alexa  排名', sal  double  COMMENT  '广告收入',
	country  char(10)  NOT  NULL  DEFAULT  ''  COMMENT  '国家',
	PRIMARY  KEY  (id)
)  ENGINE=InnoDB  DEFAULT  CHARSET=utf8;
```



## 案例4：插入、删除、更新

插入语句

`INSERT INTO websites(name,url,alexa,sal,country) VALUES('腾讯','https://www.qq.com',18,1000,'CN');`

删除语句

`delete from websites where id=5;`

更新语句

`update websites set sal=null where id=3`

## 案例5：基本select查询语句

初始化数据

```mysql
DROP TABLE IF EXISTS `websites`;
CREATETABLE `websites`(
	idint(11)NOTNULLAUTO_INCREMENT,
	namechar(20)NOTNULLDEFAULT''COMMENT'站点名称',
	urlvarchar(255)NOTNULLDEFAULT'',
	alexaint(11)NOTNULLDEFAULT'0'COMMENT'Alexa排名',saldoubleCOMMENT'广告收入',
	countrychar(10)NOTNULLDEFAULT''COMMENT'国家',
	PRIMARYKEY(id)
)ENGINE=InnoDBDEFAULTCHARSET=utf8;

INSERTINTO `websites`VALUES
(1,'Google','https://www.google.cm/','1',2000,'USA'),(2,'淘宝','https://www.taobao.com/','13',2050,'CN'),
(3,'菜鸟教程','http://www.runoob.com/','4689',0.0001,'CN'),(4,'微博','http://weibo.com/','20',50,'CN'),
(5,'Facebook','https://www.facebook.com/','3',500,'USA');

CREATE TABLE IF NOT EXISTS `access_log`(`aid`
	int(11)NOTNULLAUTO_INCREMENT,
	`site_id`int(11)NOTNULLDEFAULT'0'COMMENT'网站id',`count`int(11)
	NOT NULL DEFAULT '0' COMMENT '访问次数',`date`dateNOTNULL,
	PRIMARYKEY(`aid`)
)ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `access_log`(`aid`,`site_id`,`count`,`date`)VALUES(1,1,45,'2016-05-10'),
	(2,3,100,'2016-05-13'),(3,1,230,'2016-05-14'),(4,2,10,'2016-05-14'),(5,5,205,'2016-05-14'),(6,4,13,'2016-05-15'),(7,3,220,'2016-05-15'),(8,5,545,'2016-05-16'),(9,3,201,'2016-05-17'),(10,88,9999,'2016-09-09');
```



查询语句

`select*fromwebsites`

`selectid,name,url,alexa,sal,countryfromwebsites`（推荐使用的方式）

## 案例6.分页查询

mysql的分页是最优雅

`select * from websites limit2,3;--从第2条(下标从0开始)开始查，查3条数据`

`select * from websites limit3--从第0条(下标从0开始)开始查，查3条数据`

## 案例7.distinct关键字

DISTINCT关键词用于返回唯一不同的值。

`select distinct country from websites`

## 案例8.where语句

作为条件筛选,运算符:><>=<=<>!==

`is null is notn ull`(因为在sql语句中null和任何东西比较都是假，包括它本身)

`likein`

`select * from websites where sal>500`

## 案例9.逻辑条件:and、or

```
select * from websites where sal>=0 and sal<=2000;--收入在0到2000之间
select * from websites where sal between 0 and 2000；--和上面一样的，没事找事
select * from websites where sal<5 or sal is null;--收入小于5或者没收入
```

注意：`null`的条件判断用`is null`或`is not null`

## 案例10.order by

排序:默认情况下是升序，asc可以省略。

`select * fro websites order by sal asc,alexa desc;--先根据sal升序排序，再根据alexa降序`

## 案例11.like和通配符

like模糊查询通配符

%：0个或多个字符_:1个字符

## 案例12.in

匹配多个条件

`select * from websites where country in ('USA','鸟国','CN');`

等价于

`select * from websites where country = 'USA' or country = '鸟国' or country = 'CN'`

## 案例13.别名

`selecttt.name'网站名字'fromwebsitestt`

## 案例14.Groupby分组查询

注意：分组时候的筛选用`having`

常见的几个组函数：`max()` `min()` `avg()` `count()` `sum()`

`select avg(sal) aa from websites where sal is not null group by country having aa > 1500`

## 案例15.子查询

把查询的结果当作一个表来使用

## 案例16.连接查询

`select name,count,date from websites w,access_loga;--著名的笛卡尔积，没什么意义的`

`select name,count,date from websites w,access_loga where w.id = a.site_id；--这是1992的语法`

`select name,count,date from websites w inner join access_logaonw.id = a.site_id；--这是1999年的语法，推荐使用`

`select name,count,date from websites w left outer join access_logaonw.id = a.site_id；--把没有访问的网站也显示出来  --注意:inner和outer是可以默认省略的。`

## 案例17.Null处理l函数

`select name,ifnull(count,0),ifnull(date,'') from websites w left outer join access_logaonw.id = a.site_id`
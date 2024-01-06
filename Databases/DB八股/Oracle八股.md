## 1、简述Oracle中左连接与右连接 ？

在Oracle数据库中，左连接（left join）和右连接（right join）是两种数据表的连接方式。

* 左连接是根据左侧表中的所有记录和右侧表中满足连接条件的记录进行匹配，结果集包含左侧表的所有记录以及与之相匹配的右侧表的记录。如果左侧表的记录在右侧表中没有匹配项，那么结果集中对应的右侧表的部分将会显示为NULL。
* 右连接与左连接相反，是根据右侧表中的所有记录和左侧表中满足连接条件的记录进行匹配，结果集包含右侧表的所有记录以及与之相匹配的左侧表的记录。如果右侧表的记录在左侧表中没有匹配项，那么结果集中对应的左侧表的部分将会显示为NULL。
* 这两种连接方式在数据分析中非常有用，可以用来查找两个表之间相关的数据，或者用来查找在一个表中存在但在另一个表中不存在的数据。


## 2、Oracle跟SQL Server的区别？

Oracle和SQL Server是两种广泛使用的数据库管理系统，它们在以下方面存在一些差异：

1. 架构：Oracle数据库使用基于实例（Instance）的架构，而SQL Server使用基于数据库（Database）的架构。
2. 操作系统支持：Oracle数据库可运行于各种操作系统，如Windows、Linux、Unix等，而SQL Server只能在Windows操作系统上运行。
3. 数据库管理方式：Oracle数据库有自己的管理工具，如Oracle Enterprise Manager和SQL*Plus，而SQL Server则有SQL Server Management Studio。
4. 存储过程和触发器的实现方式：Oracle数据库使用PL/SQL语言实现存储过程和触发器，而SQL Server使用T-SQL语言实现。
5. 安全性：Oracle数据库在安全性方面较为严格，支持更多的安全特性和选项，如数据加密和身份验证。而SQL Server的安全性较为灵活，可以根据需要进行配置。
6. 价格：Oracle数据库的授权费用比SQL Server高，但Oracle数据库在高可用性、性能、安全性等方面较为出色。

总之，Oracle和SQL Server各有优势，选择哪种数据库管理系统取决于具体的业务需求和系统环境。


## 3、简述如何使用Oracle的游标？

在Oracle数据库中，游标是一种用于处理查询结果集的机制。使用游标，您可以逐行访问查询结果，并对每一行执行特定的操作。

以下是使用Oracle游标的基本步骤：

1. 声明游标：在声明部分，使用DECLARE语句声明一个游标，并指定游标的名称和类型。例如：

```sql
DECLARE cursor_name CURSOR FOR SELECT column1, column2 FROM table_name WHERE condition;
```

2. 打开游标：在打开部分，使用OPEN语句打开游标，并传递实际参数（如果有）。例如：

```sql
OPEN cursor_name (actual_parameters);
```

3. 提取数据：在提取部分，使用FETCH语句将游标工作区中的数据取到变量中。例如：

```sql
FETCH cursor_name INTO variable1, variable2;
```

4. 循环处理数据：使用循环语句（如WHILE或FOR）来逐行处理游标中的数据。在循环内部，您可以执行任何需要的数据处理操作。例如：

```sql
WHILE loop_condition LOOP
   -- 在这里执行数据处理操作
END LOOP;
```

5. 关闭游标：在关闭部分，使用CLOSE语句关闭游标。例如：

```scss
CLOSE cursor_name;
```

需要注意的是，游标的使用需要谨慎，因为不当的使用可能会导致性能问题。在使用游标之前，建议先评估是否有其他更有效的查询方式来获取所需的数据。

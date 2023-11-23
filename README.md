本项目用来学习QT

---

一、eMarket

网络电子商城demo，主要有两个部分，登录与商品管理

碰到的主要难点：QT与MYSQL数据库的连接，解决：

    1）QT5.13以上，参考博客编译MySQL库https://blog.csdn.net/iriczhao/article/details/120687688

    2）数据库使用，query之前需要QSqlDatabase loaclDB = QSqlDatabase::database();

    3）配置的时候尽量写完整连接参数

---

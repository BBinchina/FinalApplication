# FinalApplication
加密文件的去重存储系统
该系统主要功能，完成文件加密后，在本地保存密文文件，对密文加HASH值运算后，将其HASH值存放到数据库。当数据库内有重复内容时，返回表示已存在而不存储。

开发环境：centos 6.4
mysql 5.1
开发语言：C
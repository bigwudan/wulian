gcc test_mysql.c mysql/mysql_connect.c -I/usr/include/mysql/  -L/usr/lib/mysql/ -lmysqlclient -o test_mysql && ./test_mysql
gcc test.c -lssl -lcrypto -o test && ./test
gcc test_mysql.c mysql/mysql_connect.c -I/usr/include/mysql/  -L/usr/lib64/mysql/ -lmysqlclient -o test_mysql && ./test_mysql

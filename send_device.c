#include <stdio.h>  
#include <string.h>  
#include <errno.h>  
#include <sys/socket.h>  
#include <resolv.h>  
#include <stdlib.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <openssl/ssl.h>  
#include <openssl/err.h>  
#define MAXBUF 1024
char taken[80];
int send_command_1(){
    int i,j,sockfd, len, fd, size, flag;  
    char fileName[50],sendFN[20];  
    struct sockaddr_in dest;  
    char buffer[MAXBUF + 1];  
    SSL_METHOD *meth;
    SSL_CTX *ctx;  
    SSL *ssl;  
    char pwd[100];
    char* temp;


    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    meth=SSLv23_client_method();
    ctx=SSL_CTX_new(meth);
    if(!ctx){
        exit(1);
    }
    /* 创建一个 socket 用于 tcp 通信 */  
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)  
    {  
    perror("Socket");  
    exit(errno);  
    }  
    printf("socket created\n");  

    /* 初始化服务器端（对方）的地址和端口信息 */  
    bzero(&dest, sizeof(dest));  
    dest.sin_family = AF_INET;  
    dest.sin_port = htons(8743);  
    if (inet_aton("180.101.147.89", (struct in_addr *) &dest.sin_addr.s_addr) == 0)  
    {  
    perror("inet_aton");  
    exit(errno);  
    }  
    printf("address created\n");  

    /* 连接服务器 */  
    if (connect(sockfd, (struct sockaddr *) &dest, sizeof(dest)) != 0)  
    {  
    perror("Connect ");  
    exit(errno);  
    }  
    printf("server connected\n\n");  

    if (SSL_CTX_use_certificate_file(ctx,"client.pem", SSL_FILETYPE_PEM) <= 0)  
    {  
    ERR_print_errors_fp(stdout);  
    exit(1);  
    }  


    if (SSL_CTX_use_PrivateKey_file(ctx, "clientkey.pem", SSL_FILETYPE_PEM) <= 0)  
    {  
    ERR_print_errors_fp(stdout);  
    exit(1);  
    }

  /* 检查用户私钥是否正确 */  
 /* if (!SSL_CTX_check_private_key(ctx))  
  {  
    ERR_print_errors_fp(stdout);  
    exit(1);  
  }*/  

        /* 基于ctx 产生一个新的SSL */
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sockfd);


  flag=  SSL_connect(ssl);
    printf("flag=%d\n", flag);
    ssize_t size_len = 0;
    char buff[1300];
    strcat(buff, "POST /iocm/app/reg/v1.2.0/devices?appId=Xqwyn4lJPuLIPYqHBH8UN_zK8fsa HTTP/1.1\r\n");
    strcat(buff, "Host: 180.101.147.89:8743\r\n");
    strcat(buff, "Accept: */*\r\n");
    strcat(buff, "app_key: Xqwyn4lJPuLIPYqHBH8UN_zK8fsa\r\n");
    strcat(buff, "Authorization: bdbade7b29542d69351f7a4baccb560\r\n");
    strcat(buff, "Content-type: application/json\r\n");
    strcat(buff, "Content-Length: 300\r\n\r\n");

	strcat(buff, "{\"verifyCode\":\"863703038145467\",\"nodeId\":\"863703038145467\",\"timeout\":6000}"); 
    len = SSL_write(ssl, buff, 1300);

    char buffer_len[2024];

    /* 接收服务器来的消息*/
    len = SSL_read(ssl, buffer_len, 2024);

    if(len > 0 ){
    
        printf("接收消息成功:'%s'，共%d 个字节的数据\n",
               buffer_len, len);
    
    
    }

    /*else {*/
        /*char *error_msg = strerror(errno);*/
        /*printf("errorno=%d,%s\n",errno,error_msg );*/
        /*exit(1);*/
    /*}*/
    return 1;
}


int send_command_del(){
    int i,j,sockfd, len, fd, size, flag;  
    char fileName[50],sendFN[20];  
    struct sockaddr_in dest;  
    char buffer[MAXBUF + 1];  
    SSL_METHOD *meth;
    SSL_CTX *ctx;  
    SSL *ssl;  
    char pwd[100];
    char* temp;


    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    meth=SSLv23_client_method();
    ctx=SSL_CTX_new(meth);
    if(!ctx){
        exit(1);
    }
    /* 创建一个 socket 用于 tcp 通信 */  
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)  
    {  
    perror("Socket");  
    exit(errno);  
    }  
    printf("socket created\n");  

    /* 初始化服务器端（对方）的地址和端口信息 */  
    bzero(&dest, sizeof(dest));  
    dest.sin_family = AF_INET;  
    dest.sin_port = htons(8743);  
    if (inet_aton("180.101.147.89", (struct in_addr *) &dest.sin_addr.s_addr) == 0)  
    {  
    perror("inet_aton");  
    exit(errno);  
    }  
    printf("address created\n");  

    /* 连接服务器 */  
    if (connect(sockfd, (struct sockaddr *) &dest, sizeof(dest)) != 0)  
    {  
    perror("Connect ");  
    exit(errno);  
    }  
    printf("server connected\n\n");  

    if (SSL_CTX_use_certificate_file(ctx,"client.pem", SSL_FILETYPE_PEM) <= 0)  
    {  
    ERR_print_errors_fp(stdout);  
    exit(1);  
    }  


    if (SSL_CTX_use_PrivateKey_file(ctx, "clientkey.pem", SSL_FILETYPE_PEM) <= 0)  
    {  
    ERR_print_errors_fp(stdout);  
    exit(1);  
    }

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sockfd);


  flag=  SSL_connect(ssl);
    printf("flag=%d\n", flag);
    ssize_t size_len = 0;
    char buff[1300];
    strcat(buff, "POST port/iocm/app/dm/v1.1.0/devices/0ef748d8-33fd-45d6-934a-c63d33817292?appId=Xqwyn4lJPuLIPYqHBH8UN_zK8fsa HTTP/1.1\r\n");
    strcat(buff, "Host: 180.101.147.89:8743\r\n");
    strcat(buff, "Accept: */*\r\n");
    strcat(buff, "app_key: Xqwyn4lJPuLIPYqHBH8UN_zK8fsa\r\n");
    strcat(buff, "Authorization: d08fdb4da87171feb5d0e9623dc2bf3a\r\n");
    strcat(buff, "Content-type: application/json\r\n");
    strcat(buff, "Content-Length: 300\r\n\r\n");

    len = SSL_write(ssl, buff, 1300);

    char buffer_len[2024];

    /* 接收服务器来的消息*/
    len = SSL_read(ssl, buffer_len, 2024);

    if(len > 0 ){
    
        printf("接收消息成功:'%s'，共%d 个字节的数据\n",
               buffer_len, len);
    
    
    }

    /*else {*/
        /*char *error_msg = strerror(errno);*/
        /*printf("errorno=%d,%s\n",errno,error_msg );*/
        /*exit(1);*/
    /*}*/
    return 1;
}

int send_command_up(){
    int i,j,sockfd, len, fd, size, flag;  
    char fileName[50],sendFN[20];  
    struct sockaddr_in dest;  
    char buffer[MAXBUF + 1];  
    SSL_METHOD *meth;
    SSL_CTX *ctx;  
    SSL *ssl;  
    char pwd[100];
    char* temp;


    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    meth=SSLv23_client_method();
    ctx=SSL_CTX_new(meth);
    if(!ctx){
        exit(1);
    }
    /* 创建一个 socket 用于 tcp 通信 */  
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)  
    {  
    perror("Socket");  
    exit(errno);  
    }  
    printf("socket created\n");  

    /* 初始化服务器端（对方）的地址和端口信息 */  
    bzero(&dest, sizeof(dest));  
    dest.sin_family = AF_INET;  
    dest.sin_port = htons(8743);  
    if (inet_aton("180.101.147.89", (struct in_addr *) &dest.sin_addr.s_addr) == 0)  
    {  
    perror("inet_aton");  
    exit(errno);  
    }  
    printf("address created\n");  

    /* 连接服务器 */  
    if (connect(sockfd, (struct sockaddr *) &dest, sizeof(dest)) != 0)  
    {  
    perror("Connect ");  
    exit(errno);  
    }  
    printf("server connected\n\n");  

    if (SSL_CTX_use_certificate_file(ctx,"client.pem", SSL_FILETYPE_PEM) <= 0)  
    {  
    ERR_print_errors_fp(stdout);  
    exit(1);  
    }  


    if (SSL_CTX_use_PrivateKey_file(ctx, "clientkey.pem", SSL_FILETYPE_PEM) <= 0)  
    {  
    ERR_print_errors_fp(stdout);  
    exit(1);  
    }

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sockfd);


  flag=  SSL_connect(ssl);
    printf("flag=%d\n", flag);
    ssize_t size_len = 0;
    char buff[1300];
    strcat(buff, "PUT /iocm/app/dm/v1.2.0/devices/7d47ec21-69a3-4c70-804e-a6a879d485b9?appId=Xqwyn4lJPuLIPYqHBH8UN_zK8fsa HTTP/1.1\r\n");
    strcat(buff, "Host: 180.101.147.89:8743\r\n");
    strcat(buff, "Accept: */*\r\n");
    strcat(buff, "app_key: Xqwyn4lJPuLIPYqHBH8UN_zK8fsa\r\n");
    strcat(buff, "Authorization: bdbade7b29542d69351f7a4baccb560\r\n");
    strcat(buff, "Content-type: application/json\r\n");
    strcat(buff, "Content-Length: 300\r\n\r\n");
//	strcat(buff, "{\"name\":\"863703038145467\",\"manufacturerId\":\"GONTO\",\"manufacturerName\":\"GONTO\",\"deviceType\":\"WSYL001\",\"protocolType\":\"CoAP\"}");

	strcat(buff, "{\"name\":\"863703038145467\",\"manufacturerId\":\"GONTO\",\"manufacturerName\":\"GONTO\",\"deviceType\":\"WSYL001\",\"protocolType\":\"CoAP\",\"model\":\"WSYL001\"}");

    len = SSL_write(ssl, buff, 1300);

    char buffer_len[2024];

    /* 接收服务器来的消息*/
    len = SSL_read(ssl, buffer_len, 2024);

    if(len > 0 ){
    
        printf("接收消息成功:'%s'，共%d 个字节的数据\n",
               buffer_len, len);
    
    
    }

    /*else {*/
        /*char *error_msg = strerror(errno);*/
        /*printf("errorno=%d,%s\n",errno,error_msg );*/
        /*exit(1);*/
    /*}*/
    return 1;
}
int main(){
	//send_command_1();	
	//send_command_del();	
	send_command_up();
	exit(1);
}


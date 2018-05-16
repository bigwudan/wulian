
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

 #define PORT 8743
 #define DINADDR_ANY "180.101.147.89"


int main(){

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
    char buff[1000];
    strcat(buff, "POST /iocm/app/cmd/v1.3.0/devices/ede76b44-7823-40f8-a258-a0c68f2fd8c9/commands HTTP/1.1\r\n");
    strcat(buff, "Host: 180.101.147.89:8743\r\n");
    strcat(buff, "Accept: */*\r\n");
    strcat(buff, "app_key: Xqwyn4lJPuLIPYqHBH8UN_zK8fsa\r\n");
    strcat(buff, "Authorization: 71784e738e0c274514b0599051f5f8\r\n");
    strcat(buff, "Content-type: application/json\r\n");
    strcat(buff, "Content-Length: 85\r\n\r\n");
    strcat(buff, "{\"command\":{\"serviceId\":\"LOCK\",\"method\":\"cmd\",\"paras\":{\"cmd01\":\"77\"}},\"expireTime\":0}");


    len = SSL_write(ssl, buff, 1000);

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

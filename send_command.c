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
    strcat(buff, "POST /iocm/app/cmd/v1.3.0/devices/0a6d19dc-a2b4-49b1-be1d-20e4d3034400/commands HTTP/1.1\r\n");
    strcat(buff, "Host: 180.101.147.89:8743\r\n");
    strcat(buff, "Accept: */*\r\n");
    strcat(buff, "app_key: Xqwyn4lJPuLIPYqHBH8UN_zK8fsa\r\n");
    strcat(buff, "Authorization: 44c8528b109ff7bbec1496a79fd8459\r\n");
    strcat(buff, "Content-type: application/json\r\n");
    strcat(buff, "Content-Length: 200\r\n\r\n");
    //strcat(buff, "{\"command\":{\"serviceId\":\"LOCK\",\"method\":\"cmd\",\"paras\":{\"cmd01\":\"77\"}},\"expireTime\":0}");
	strcat(buff, "{\"command\":{\"serviceId\": \"WXYL\",\"method\": \"SetCmd\",\"paras\": {\"C2_EM\": 4,\"C2_EN\": 1,\"C2_SM\": 3,\"C2_ED\": 1,\"C2_SD\": 1,\"CYCLE_1\": 5,\"CYCLE_2\": 5}},\"expireTime\":0}");


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

int get_token()
{

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
	    /* 基于ctx 产生一个新的SSL */
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sockfd);


 // flag=  SSL_connect(ssl);
    if (SSL_connect(ssl) == -1)
        ERR_print_errors_fp(stderr);
    else {
		printf("connected\n");
        printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
    }
char *p_head1 = "/iocm/app/sec/v1.1.0/login/";
char *p_head2 = "180.101.147.89:8743";
int bodynum = 70;
char *p_appid = "Xqwyn4lJPuLIPYqHBH8UN_zK8fsa";
char *p_appkey = "XIcGewffJE8LpfMWksO4Vipvfsga";

 ssize_t size_len = 0;
 char buff[300];
 sprintf(
              buff,
              "POST %s HTTP/1.1\nHost: %s\nContent-Type:application/x-www-form-urlencoded\nContent-Length: %d\r\n\r\nappId=%s&secret=%s",
              p_head1,
              p_head2,
              bodynum,
              p_appid,
              p_appkey
      );
	len = SSL_write(ssl, buff, 300);

	char buffer_len[1024];

    /* 接收服务器来的消息*/
    len = SSL_read(ssl, buffer_len, 1024);
    if (len > 0){
	}
    else {
		exit(1);
    }
	
	char *p_add = NULL;                                                                                                                   
	p_add = strstr(buffer_len, "\"accessToken\":");
	p_add = p_add+15;    
	  
	char *p_start = NULL;
	int dur = 0;
	p_start =  strstr(p_add, "\""); 
	dur = p_start- p_add;
	memcpy(taken, p_add, dur); 
	
SSL_shutdown(ssl);
SSL_free(ssl);
SSL_CTX_free(ctx);   


	close(socket);
	return 1;

}


int main(){
	//get_token();
	send_command_1();	
	//printf("taken=%s\n", taken);
	printf("ok\r\n");

	exit(1);
}


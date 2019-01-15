//
//  socket_HTTP_GET_POST.c
//  C
//
//  Created by 黄骏东 on 2018/7/1.
//  Copyright © 2018 黄骏东. All rights reserved.
//

#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int GET()
{
    struct sockaddr_in serv_addr;
    int sfd,portnum,num;
    portnum=5001;
    char sdbuf[1024],rcbuf[1024];
    if((sfd=socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        printf("socket error\n");
        exit(1);
        
    }
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(80);
    serv_addr.sin_addr.s_addr=inet_addr( "140.206.60.73");//www.sse.com.cn
    if (connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        printf("connect error\n");
        exit(2);
    }
    /* strcat(sdbuf, "POST ");
     strcat(sdbuf, "http://www.baidu.com");
     strcat(sdbuf, " HTTP/1.0\r\n");
     strcat(sdbuf, "Host: ");
     strcat(sdbuf, "baidu.com");
     strcat(sdbuf, "\r\n");
     strcat(sdbuf, "CONNECTION: keep-alive\r\n");
     strcat(sdbuf, "\r\n");
     */
    
    strcat(sdbuf, "OPTIONS * HTTP/1.1\r\n");
    strcat(sdbuf,"CONNECT www.sse.com.cn:80");
    strcat(sdbuf, "\r\n");
    printf("REQUEST:\n%s\n",sdbuf);
    
    if((num=send(sfd,sdbuf,1024,0))<0)
    {
        printf("send erro/n");
        exit(3);
    }
    printf("num=%d\n",num);
    num = recv(sfd, rcbuf, 2048, 0);
    printf("recnum:%d\n",num);
    if (num<0)
    {
        printf("recv error!");
        exit(1);
    }
    printf("%s\n", rcbuf);
    
    return 0;//return  0 
    
}


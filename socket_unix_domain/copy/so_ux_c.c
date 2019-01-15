#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <ctype.h>
#define BUF_SIZE 10
#define SV_SOCK_PATH "/tmp/ud_ucase"
int main(int argc ,char *argv[])
{
    struct sockaddr_un svaddr,claddr;
    int sfd,j;
    ssize_t numBytes;
    ssize_t msglen;
    socklen_t len;
    char buf[BUF_SIZE];
    
    sfd=socket(AF_UNIX,SOCKET_DGRAM,0);
    if (sfd==-1) {
        perror("fail open socket");
        exit(-1);
    }
    else
    {
       
        
            memset(&claddr,0,sizeof(struct sockaddr_un));
            memset(&svaddr,0,sizeof(struct sockaddr_un));
            claddr.sun_family=AF_UNIX;
            snprintf(claddr.sun_path,sizeof(claddr.sun_path),"/temp/ud_ucase_cl.%ld",(long)getpid());
            
            if(bind(sfd,(struct sockaddr *)&claddr,sizeof(struct sockaddr_un))==-1 )
            {
                perror("fail bind");
                exit(-3);
            }
            else
            {
                //construct address of server
                svaddr.sun_family=AF_UNIX;
                strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path) - 1);
                for (j=1; j<argc; j++)
                {
                    msglen=strlen(argv[j]);
                    if(sendto(sfd,argv[j],msglen,0,(struct sockaddr *)&svaddr),sizeof(struct sockaddr_un))!=maglen)
                    {
                        perror("fail sendto");
                        exit(-4)
                    }
                    numBytes = recvfrom(sfd, resp, BUF_SIZE, 0, NULL, NULL);
                    if (numBytes == -1)
                    {
                        perror("fail recvfrom");
                        exit(-5)
                    }
                    printf("Response %d: %.*s\n", j, (int) numBytes, resp);
                }
                remove(claddr.sun_path); /* Remove client socket pathname */
                exit(1);
                }
        
    }
}


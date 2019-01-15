q


int main(int argc ,char *argv[])
{
    struct sockaddr_un svaddr,claddr;
    int sfd,j;
    ssize_t numBytes;
    socklen_t len;
    char buf[BUF_SIZE];
    //create socket()
    sfd=socket(AF_UNIX,SOCK_DGRAM,0);
    if (sfd==-1) {
        perror("fail open socket");
        exit(-1);
    }
    else
    {
        if(remove(SV_SOCK_PATH)==-1)//remove all file in SV_SOCK_PATH
        {
            perror("fail remove");
            exit(-2);
        }
        else
        {
            memset(&svaddr,0,sizeof(struct sockaddr_un));
            memset(&claddr,0,sizeof(struct sockaddr_un));
            svaddr.sun_family=AF_UNIX;
            strncpy(svaddr.sun_path,SV_SOCK_PATH,sizeof(svaddr.sun_path));
            if(bind(sfd,(struct sockaddr *)&svaddr,sizeof(struct sockaddr_un))==-1 )
            {
                perror("fail bind");
                exit(-3);
            }
            else
            {
                for(;;)
                {
                    len=sizeof(struct sockaddr_un);
                    numBytes=recvfrom(sfd,buf,BUF_SIZE,0,(struct sockaddr *)&claddr,&len);
                    if(numBytes==-1)
                    {
                        perror("fail revfrom");
                        exit(-4);
                    }
                    else
                    {
                        printf("Server received %ld bytes from %s\n", (long) numBytes, claddr.sun_path);
                        for(j=0;j<numBytes;j++)
                        {
                            buf[j]=toupper((unsigned char ) buf[j]);
                        }
                        if (sendto(sfd,buf,numBytes,0,(struct sockaddr *)&claddr,len)!=numBytes) {
                            perror("fail sendto");
                            exit(-5);
                        }
                    }
                }
                    
            }
        }
    }
}

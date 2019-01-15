#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <ctype.h>
#include<string.h>
int erroP_E(char * in )//print the erron and exit
{
    perror(in);
    exit(1);
}


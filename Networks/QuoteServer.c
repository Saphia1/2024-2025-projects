/*
 *  QuoteServer
 *
 *  Created by <insert name> 
 *  Username: <inser username>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>

#define kQUOTEPORT 1717

/*void ReadQuote(int sd,  char* argv, char * line);*/
int main(int argc, const char * argv[])
{
    int serverSocket, connectionSocket;
    struct sockaddr_in server;
	struct sockaddr_in client;
	unsigned int alen;
    char line[256];
    size_t n;
    /*char c;*/
    int i;
    FILE *file;

    /*socket creation*/
    serverSocket=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);/*IPV4, stream socket, TCP*/

    /*port creation*/
    memset(&server,0,sizeof(struct sockaddr_in));/*set server struct info to zeros*/
    server.sin_family=AF_INET;/*Socket will use IPv4*/
    server.sin_port=htons(1717);/*convert port numb to network byte order(big endian)*/
    server.sin_addr.s_addr=INADDR_ANY;/*accept any incoming connections, from any network interfaces*/

    /*binding socket*/
    if(bind(serverSocket,(struct sockaddr *)&server,sizeof(struct sockaddr_in)) < 0){
        fprintf(stderr,"ERROR:failed to bind\n");
        exit(1);
    }

    /*listening*/
    if(listen(serverSocket,15)<0){
        fprintf(stderr,"ERROR:failed to listen\n");
        exit(2);
    }

    /*connect*/
    while(1)
    {
        alen=sizeof(client);
        connectionSocket=accept(serverSocket,(struct sockaddr*)&client,&alen);
        
       /*printf("Connection from %x on port %d\n", ntohl(client.sin_addr.s_addr), ntohs(client.sin_port));
        printf("Client is on socket %d, server socket was %d\n", connectionSocket, serverSocket);*/
        /*printf("ARGV1: %s\n",argv[1]);*/
       /* n =recv(connectionSocket,&c,1,0);*/
        /*printf("opening file\n");*/
        file=fopen(argv[1],"r");
        if (!file){
            printf("ERROR:failed to open file");
            return 1;
        }
       /*printf("successfully opened\n");*/
        fgets(line,sizeof(line),file);
        i=0;
        do
        {

           /* printf("%d\n",i);*/
            
            n=line[i];
            i++;
            n=line[i];
            if((i>0)&&(line[i]=='\n')&&(line[i-1]=='\r')){
                break;
            }
            i++;
        }while (i<sizeof(line)||i<256);
        line[i-1]='\0';/*null terminates the string*/
        /*ReadQuote(connectionSocket,argv,line);*/
       /* printf("out of do loop\n");*/
        send(connectionSocket,line,strlen(line),0);
        close(connectionSocket);

        
        /*printf("sent");*/
        
        
        
    }

    
    return 0;
}


/*void ReadQuote(int sd, char* argv, char *line)
{
    size_t n;
    int i;
    char *filename=argv;
    FILE *file=fopen(filename,"r");
    if (!file){
        printf("ERROR:failed to open file");
        return;
    }
    
    fgets(line,sizeof(line),file);
    do
    {
        i=1;
        n=line[i-1];
        if((i>0)&&(line[i]=='\n')&&(line[i-1]=='\r')){
            break;
        }
        i++;
    }while (i<257);
    line[i-1]='\0';null terminates the string

}*/


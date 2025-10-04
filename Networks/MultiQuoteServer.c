/*
 *  MultiQuoteServer
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

#define kMULTIQUOTEPORT 1818

int main(int argc, const char * argv[])
{
     int serverSocket, connectionSocket;
    struct sockaddr_in server;
	struct sockaddr_in client;
	unsigned int alen;
    char line[512];
    size_t n,linelen;
    /*char c;*/
    int i;
    FILE *file;
    char response[256];
    char *bye="BYE\r\n";
    char *error="ERROR\r\n";

    /*socket creation*/
    serverSocket=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);/*IPV4, stream socket, TCP*/

    /*port creation*/
    memset(&server,0,sizeof(struct sockaddr_in));/*set server struct info to zeros*/
    server.sin_family=AF_INET;/*Socket will use IPv4*/
    server.sin_port=htons(1818);/*convert port numb to network byte order(big endian)*/
    server.sin_addr.s_addr=INADDR_ANY;/*accept any incoming connections, from any network interfaces*/

    /*binding socket*/
    if(bind(serverSocket,(struct sockaddr *)&server,sizeof(struct sockaddr_in)) < 0){
        fprintf(stderr,"ERROR:failed to bind\n");
        exit(1);
    }
    else{
        printf("binded successfully\n");
    }

    /*listening*/
    if(listen(serverSocket,15)<0){
        fprintf(stderr,"ERROR:failed to listen\n");
        exit(2);
    }
    else{
        printf("listening\n");
    }

    /*connect*/
    while(1)
    { 
        alen=sizeof(client);
        connectionSocket=accept(serverSocket,(struct sockaddr*)&client,&alen);
        if (connectionSocket<0){
            fprintf(stderr,"ERROR accepting connection\n");
            close(connectionSocket);
            continue;
        }
        else{
            printf("connected\n");
        }

        file=fopen(argv[1],"r");
        if (!file){
                printf("ERROR:failed to open file");
                close(connectionSocket);
                continue;
        }
            
        else{
            printf("opening file\n");
        }
        i=1;
        if ((fgets(line,sizeof(line),file))!=NULL){
            line[strcspn(line,"\n")]='\0';
            linelen=strlen(line);
            if(line[linelen-1]=='\n'){
                line[linelen-1]='\r';
                line[linelen]='\n';
                line[linelen+1]='\0';
            }
            else{
                line[linelen]='\r';
                line[linelen+1]='\n';
                line[linelen+2]='\0';
            }
            printf("sending quote\n");
            send(connectionSocket,line,strlen(line),0);
        }
        else{
            printf("empty file\n");
        }
        while(1)
        {
            printf("while loop\n");  
            memset(response,0,sizeof(response));
            printf("waiting for response\n");
            n=recv(connectionSocket,response,sizeof(response)-1,0);
            printf("recieving response\n");
            if (n<=0){
                fprintf(stderr,"ERROR recieving response\n");
                printf("error recieving response\n");
                close(connectionSocket);
                break;
            }
            else{
                printf("recieved response\n");
            }
            response[n]='\0';

            if(strncmp(response,"CLOSE",5)==0){
                send(connectionSocket,bye,strlen(bye),0);
                break;
            }
            else if(strncmp(response,"ANOTHER",7)==0){
                if ((fgets(line,sizeof(line),file))!=NULL){
                    line[strcspn(line,"\n")]='\0';
                    linelen=strlen(line);
                    if(line[linelen-1]=='\n'){
                        line[linelen-1]='\r';
                        line[linelen]='\n';
                        line[linelen+1]='\0';
                    }
                    else{
                        line[linelen]='\r';
                        line[linelen+1]='\n';
                        line[linelen+2]='\0';
            }
                    send(connectionSocket,line,strlen(line),0);
                }
                else{
                    printf("bye sending\n");
                    send(connectionSocket,bye,strlen(bye),0);
                    break;
                }
            }
            else{
                send(connectionSocket,error,strlen(error),0);
            }
            
        }

        fclose(file);
        close(connectionSocket);
    }




        


        
        /*printf("sent");*/
        
        
    close(serverSocket);   
    
    return 0;
}
        /*printf("successfully opened\n");*/
            /*while((line[i]!='\n')&&(line[i-1]!='\r')){
                i++;
                if((i>0)&&(line[i]=='\n')&&(line[i-1]=='\r')){
                    break;
                }
            }*/

                        /*else if(strncmp(response,"ANOTHER",7)!=0){
                send(connectionSocket,error,strlen(error),0);
                recv(connectionSocket,response,sizeof(response)-1,0);
            }
            else{
               response must be ANOTHER
            }*/

            /*            else if(strncmp(response,"ANOTHER",7)==0){
                continue;
            }
            else{
                send(connectionSocket,error,strlen(error),0);
                recv(connectionSocket,response,sizeof(response)-1,0);
            }*/ 
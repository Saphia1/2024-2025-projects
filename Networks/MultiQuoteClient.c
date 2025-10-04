/*
 *  MultiQuoteClient
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
    
    char buf[512];/*stores GTTP GET request before sending to server*/
	int sd;/*socket descriptor - holds integer identifier for socket created*/
	char c;/*allows program print each character one at a time*/
	size_t n;/*numb bytes returned by recv() function, check if data recieved correctly*/
	int ret;/*return value of getaddrinfo(), check if hostname resolution successful*/
	struct addrinfo hints;/*holds criteria for getaddrinfo() function, what type of socket and address family*/
	struct sockaddr_in sa;/*specifies socket addresses*/
	struct addrinfo *ip;/*pointer to strcut, addinfo holding result of getaddrinfo(). linked list if possible given hostname addresses*/
    char next[256];
    char response[512];
    const char *number = argv[2];
    int numb=*number-'0',count,i,total;

    memset(&hints, 0, sizeof(hints));/*sets hints struct to 0*/
	hints.ai_family = AF_UNSPEC; /*support IPV4/IPV6*/
	hints.ai_socktype = SOCK_STREAM;/* use TCP sockets*/
	hints.ai_protocol = IPPROTO_TCP;/*use TCP protocol*/

    if(0==(ret=getaddrinfo(argv[1],"1818",&hints,&ip)))/*resloving host name*/
	{
		struct addrinfo *p =ip;
		while(p)/*while there is still adress info to point to*/
		{/*OPEN SOCKET*/
			sd =socket(p->ai_family,p->ai_socktype,p->ai_protocol);
			if(sd !=-1){/*socket creation successful*/
				if(connect(sd,p->ai_addr,p->ai_addrlen) == 0){/*connects to server using socket sd and address ppinted to by p. ==0, successful*/
					break;/*stop trying to connect*/
				}
				else{/*fails to connect*/
					close(sd);
					sd =-1;/*set to -1 to later display error*/
				}
			}
			else{
				fprintf(stderr,"ERROR:Error in socket creation\n");
			}
			p =p->ai_next;/*increment pointer to next possible address*/
		}
	}
	else{
	fprintf(stderr,"ERROR:Resolving host name failure %s: %d\n", argv[1], ret);/*host name never resolved*/
		exit(1);
    }
	freeaddrinfo(ip);/*free adress struct from using memory*/
	if(sd==-1){/*if socket failed to connect*/
	    fprintf(stderr,"ERROR: could not connect to %s\n", argv[1]);
		exit(1);
	}
    

	
    /*counter=0;*/
	
    /*while(count<numb)*/

	for (count=0;count<numb;count++)
	{
		memset(response,0,sizeof(response));
		total=0;
		do
		{
			n=recv(sd,response+total,sizeof(response)-total-1,0);
			total+=n;
			response[total]='\0';

		}while(response[total-2]!='\r'|| response[total-1]!='\n');
		printf("%s\n\n",response);
		if (count<numb-1){
			sprintf(buf,"%s\r\n","ANOTHER");
        	send(sd, buf, strlen(buf), 0);/*sends get request to server*/
        
		}
	}
	sprintf(buf,"%s\r\n","CLOSE\r\n");
    send(sd, buf, strlen(buf), 0);
	/*memset(response,0,sizeof(response));
	recv(sd,response,sizeof(response)-1,0);
	response[strlen(response)]='\0';
	printf("%s\n",response);*/
	/*scanf("%s",next);
	while(strcmp(next,"CLOSE")!=0&&strcmp(next,"ANOTHER")!=0){
			printf("ERROR PLEASE ENTER VALID RESPONSE \n");
        	scanf("%s",next);
		}

	if (strcmp(next,"CLOSE")==0){

			close(sd);
		}

	if ((strcmp(next,"ANOTHER")==0)&&count>=numb){
			printf("Reached specified quote limit\n");
		}*/ 
    

	close(sd);
	
    return 0;
}  /*sprintf(buf,"%s\r\n",next);creates get request using buffer*/
				/*do{recieve server response and print character by character
	

		c=response[i];
			i++;
			printf("%c",c);
			
			
			

		} while(n!='\0');*/
		/*printf("ANOTHER? \n");*/
        /*scanf("%s",next);;*/
		/*while(strcmp(next,"CLOSE")!=0&&strcmp(next,"ANOTHER")!=0){
			printf("ERROR PLEASE ENTER VALID RESPONSE \n");
        	scanf("%s",next);
		}

		if (strcmp(next,"CLOSE")==0){
			break;
		}*/
		/*else if (strcmp(next,"ANOTHER")==0){
			printf("Another chosen\n");
		}*/
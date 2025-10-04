/*
 *  QuoteClient
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

int main(int argc, const char * argv[])
{
    char buf[256];/*stores GTTP GET request before sending to server*/
	int sd;/*socket descriptor - holds integer identifier for socket created*/
	char c;/*allows program print each character one at a time*/
	size_t n;/*numb bytes returned by recv() function, check if data recieved correctly*/
	int ret;/*return value of getaddrinfo(), check if hostname resolution successful*/
	struct addrinfo hints;/*holds criteria for getaddrinfo() function, what type of socket and address family*/
	struct sockaddr_in sa;/*specifies socket addresses*/
	struct addrinfo *ip;/*pointer to strcut, addinfo holding result of getaddrinfo(). linked list if possible given hostname addresses*/

    memset(&hints, 0, sizeof(hints));/*sets hints struct to 0*/
	hints.ai_family = AF_UNSPEC; /*support IPV4/IPV6*/
	hints.ai_socktype = SOCK_STREAM;/* use TCP sockets*/
	hints.ai_protocol = IPPROTO_TCP;/*use TCP protocol*/

    if(0==(ret=getaddrinfo(argv[1],"1717",&hints,&ip)))/*resloving host name*/
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
	/*sprintf(buf,"GET %s\r\n", argv[2]);/*creates get requestw using buffer
	send(sd, buf, strlen(buf), 0);/*sends get request to server
	printf("Sent\n");*/
	do{/*recieve server response and print character by character*/
	
		n =recv(sd,&c,1,0);/*save server response as n*/
		/*printf("Recieved\n");*/
		if(n==1){
			printf("%c",c);
		}
	} while(n==1);

	close(sd);
	
    return 0;

}

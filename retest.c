#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <string.h>  
#include <stdio.h>  
#define PORT 6000 /*使用的port*/
#define IP "192.168.109.1"

#define PACKET_LEN 65535

int main()
{
    int sockfd, len=0;
    struct sockaddr_in addr;
    char buffer[PACKET_LEN];
	int i=0;
	int max=65535;
	int j=1500;
	int addr_len=sizeof(struct sockaddr);
    //建立socket
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror ("socket");
        exit(1);
    }
    //填写sockaddr_in 结构
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
	inet_pton(AF_INET,IP,&addr.sin_addr.s_addr);
    while(1)
    {
		for(i=0;i<j;i++)
		{
			buffer[i]=i%10+65;
		}
		j++;
		if(j>=max)
		{
			j=1500;
		}
		len=i;
        //bezro(buffer, sizeof(buffer));
        //len = recvfrom(socket, buffer, sizeof(buffer), 0, &addr &addr_len);
        //显示client 端的网络地址
        //printf("receive from %s\n ", inet_ntoa(addr.sin_addr));
        //将字串返回给client 端
		sendto(sockfd, buffer, len, 0,(struct sockaddr*)&addr,addr_len );
		sleep(2);
	}
	return 0;
}

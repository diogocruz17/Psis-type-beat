#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "list_groups.h"
#include "list_key_value.h"

int auth_sock;
struct sockaddr_in server_addr;

struct Pair
{
    char group[64];
    char secret[128];
}Pair;


struct Receive
{
    struct Pair pair;
    int status;             //1-Create, 2-Authenticate, 0 or else-error
}Receive;

int CreateINETSock()
{
	struct sockaddr_in local_addr;
	int auth_sock= socket(AF_INET, SOCK_DGRAM, 0);

	if (auth_sock == -1){
		perror("socket: ");
		exit(-1);
	}
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = INADDR_ANY;
	local_addr.sin_port = htons(3000);

	int err = bind(auth_sock, (struct sockaddr *)&local_addr, sizeof(local_addr));

	if(err == -1) {
		perror("bind");
		exit(-1);
	}


	printf("Socket created \n Ready to send\n");

	server_addr.sin_family = AF_INET;
	inet_aton("127.0.0.1", &server_addr.sin_addr);
	server_addr.sin_port = htons(3001);

	return auth_sock;
}

char* CommAuth(char *group_id, char *secret, char *command)
{
	struct Receive info;
	int nbytes;
	char *auth=(char*)malloc(sizeof(char)*128);


	strcpy(info.pair.group, group_id);
	strcpy(info.pair.secret, secret);

	if(strcmp(command, "create")==0)
	{
		info.status=1;
	}
	if(strcmp(command, "connect")==0)
	{
		info.status=2;
	}
	
	nbytes = sendto(auth_sock, &info, sizeof(info), 0,(const struct sockaddr *) &server_addr, sizeof(server_addr));
	printf("sent %d byte ---%s---, ---%s---, %d\n", nbytes, info.pair.group, info.pair.secret, info.status);

	nbytes = recv(auth_sock, auth, 128, 0);
	printf("received %d bytes ---%s---\n", nbytes, auth);

	return auth;
}
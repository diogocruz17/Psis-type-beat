#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "pair_list.h"


struct Pair
{
    char group[64];
    char secret[128];
};


struct Receive
{
    struct Pair pair;
    int status;                 //1-Create, 2-Authenticate, 0 or else-error
};


char* generateSecret()         //Gerar segredo aleatorio
{
    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";        
    char *randomString = NULL;

    int length=5;      

    if (length) {
        randomString = malloc(sizeof(char) * (length +1));

        if (randomString) {            
            for (int n = 0;n < length;n++) {          
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}


int main(){
    struct sockaddr_in local_addr;
	struct sockaddr_in other_addr;
	socklen_t size_other_addr;
	int nbytes, lerror;

    struct Pair pair, pair_comp;

    struct Receive info;

    t_lista* lp;

    lp=iniLista();
    srand(time(NULL));    

    int sock_fd= socket(AF_INET, SOCK_DGRAM, 0);

	if (sock_fd == -1){
		perror("socket: ");
		exit(-1);
	}

    local_addr.sin_family = AF_INET;
    inet_aton("0.0.0.0", &local_addr.sin_addr); //any address
    local_addr.sin_port = htons(3001);
    size_other_addr = sizeof(struct sockaddr_storage);

    int err = bind(sock_fd, (struct sockaddr *)&local_addr, sizeof(local_addr));
	if(err == -1) {
		perror("bind");
		exit(-1);
	}

	printf("Socket created and binded\n");
	

    while(1)
    {
        printf("Ready to receive messages\n");
        nbytes = recvfrom(sock_fd, &info, sizeof(info), 0, (struct sockaddr *) &other_addr, &size_other_addr);
	    int client_port = ntohs(other_addr.sin_port);


	    printf("Received from %s %d\n", inet_ntoa(other_addr.sin_addr), client_port);
	    printf("Received %d bytes --- %s ---, ---%s---, %d\n", nbytes, info.pair.group, info.pair.secret, info.status);


        if(info.status==1)      //Create
        {
            t_lista* aux;
            aux=lp;

            char *segredo= NULL;

            if(aux!=NULL)
            {
                while(1)
                {
                    pair_comp=getItemLista(aux);
		            if(strcmp(info.pair.group, pair_comp.group)==0)
                    {
                        sendto(sock_fd, pair_comp.secret, strlen(pair_comp.secret)+1, 0, (const struct sockaddr *) &other_addr, sizeof(other_addr));
                        break;
                    }

                    aux=getProxElementoLista(aux);
                    if(aux==NULL)
                    {
                        break;
                    }
                }
            }

            if(aux==NULL)
            {
                segredo=generateSecret();
                printf("%s\n", segredo);

                sendto(sock_fd, segredo, strlen(segredo)+1, 0, (const struct sockaddr *) &other_addr, sizeof(other_addr));
                //printf("Sent %s\n",segredo);
                        
                strcpy(pair.group, info.pair.group);
                strcpy(pair.secret, segredo);

                lp=criaNovoNoLista(lp, pair, &lerror);

                if(lerror==1)
                {
                    printf("Erro a criar nó na lista de grupos, exiting...\n");
                    exit(-1);
                }
            }
        }


        if(info.status==2)      //Authenticate; Code sent back(what is correct):1-group and secret, 2-group, 0-none
        {
            t_lista* aux;
            aux=lp;
            char auth[128];

            strcpy(auth, "invalid");

            
            while(1)
            {
                if(aux==NULL){
                    //sendto(sock_fd, &auth, sizeof(auth), 0, (const struct sockaddr *) &other_addr, sizeof(other_addr));
                    //printf("Sent %s\n",auth);
                    break;
                }
                pair_comp=getItemLista(aux);
                if(strcmp(info.pair.group, pair_comp.group)==0)
	            {
		            if(strcmp(info.pair.secret, pair_comp.secret)==0)
                    {
                        strcpy(auth, "connected");
                        break;
                    }

                    strcpy(auth, "wrong");
                    break;
	            }

                aux=getProxElementoLista(aux);
                if(aux==NULL)
                {
                    break;
                }
                
            }
            sendto(sock_fd, &auth, sizeof(auth), 0, (const struct sockaddr *) &other_addr, sizeof(other_addr));

        }
    }
    
}
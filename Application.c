#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "KVS-lib.h"
#include "app_func.h"

int local_server,aux=1,i=0;
int main(int argc, char *argv[])
{
    int connection=0,i=0,n_read,status;
    char buffer[1000];
    char group_id[64], secret[128],key[128], value [128], command[20];
    local_server=init();
    if(local_server==-1)
    {
        printf("Erro na ligação com o servidor local. Exiting...");
        exit(-1);
    }


    while(connection!=1)
    {   
        fgets(buffer,1000,stdin);
        n_read=sscanf(buffer,"%s %s %s",command,group_id,secret);
        if((strcmp(command, "connect"))!=0)
        {   
            printf("Command input is wrong. Also you have to establish connection to a group before editing data. Try again \n");
            continue;
        }
        if(n_read<3)
        {
            printf("Missing arguments.Try again\n");
            continue;
        }
        connection=establish_connection(group_id,secret);
        if(connection==-1)
        {
            printf("Lost connection to local server.Exiting...\n");
            exit(-1);
        }
        if(connection==-2)
        {
            printf("Group doesnt exist.Try again\n");
            continue;
        }
        if(connection==-3)
        {
            printf("Secret is wrong.Try again\n");
            continue;
        }
        if(connection==0)
        {
            printf("Connected to group:%s\n",group_id);
            break;
        }
    }
    while(1)
    {
        fgets(buffer,1000,stdin);
        sscanf(buffer,"%s",command);
        if(strcmp(command,"put")==0)
        {
            n_read=sscanf(buffer,"%s %s %s",command,key,value);
            if(n_read<3)
            {
                printf("Missing arguments.Try again\n");
                continue;
            }
            status=put_value(key,value);
            if(status==-1)
            {
                printf("Lost connection to local server.Exiting...\n");
                exit(-1);
            }
            if(connection==-2)
            {
                printf("Group doesnt exist.Try again\n");
                continue;
            }
            if(connection==-3)
            {
                printf("Secret is wrong.Try again\n");
                continue;
            }
            if(connection==1)
            {
                printf("Value of key:%s edited",key);
                continue;
            }

        }
    }

    return 0 ;


}
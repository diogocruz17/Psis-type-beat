#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "localsv_func.h"
#define KVS_LS_SOCK_PATH "/tmp/kvs_ls"

void *client_thread(void *sock)
{
    printf("dentro thread\n");
    char buffer[10000], c_aux = 'a';
    char group_id[64], secret[128], key[128], command[20], value_aux[9500];
    int client_sock = *(int *)sock, n_read;
    int i,returned;
    while (1)
    {
        do
        {
            if (read(client_sock, &c_aux, sizeof(char)) == -1)
            {
            }
            buffer[i] = c_aux;
            i++;
        } while (c_aux != '\0');
        i = 0;
        printf("%s\n", buffer);
        sscanf(buffer, "%s %s %s",command,group_id,secret);
        //envia para auth server para validar
        //envia resposta para app
        //if for aceite break;
    }
    while (1)
    {
        do
        {
            if (read(client_sock, &c_aux, sizeof(char)) == -1)
            {
            }
            buffer[i] = c_aux;
            i++;
        } while (c_aux != '\0');
        i = 0;
        printf("%s\n", buffer);

        sscanf(buffer, "%s", command);
        if (strcmp(command, "put") == 0)
        {
            n_read = sscanf(buffer, "%s %s %s", command, key, value_aux);
        }
        if (strcmp(command, "get") == 0)
        {
            n_read = sscanf(buffer, "%s %s", command, key);
        }
        if (strcmp(command, "delete") == 0)
        {
            n_read = sscanf(buffer, "%s %s", command, key);
        }
        if (strcmp(command, "close") == 0)
        {
        }
    }

    return 0;
}


void *localserver_ui(void *sock)
{
    char group_id[64], secret[128],command[20],command_2[20],buffer[100];
    int n_read;
    while(1)
    {
        fgets(buffer,100,stdin);
        sscanf(buffer,"%s",command);
        if(strcmp(command,"create")==0)
        {
            n_read=sscanf(buffer,"%s %s",command,group_id);
            if(n_read<2)
            {
                printf("Arguments missing. Try again\n");
                continue;
            }
            //create_group para o auth server
            //criar grupo no local server
        }
        if(strcmp(command,"delete")==0)
        {
            n_read=sscanf(buffer,"%s %s",command,group_id);
            if(n_read<2)
            {
                printf("Arguments missing. Try again\n");
                continue;
            }
            //delete_group(group_id);
        }
        if(strcmp(command,"group")==0)
        {
            sscanf(buffer,"%s %s",command,command_2);
            if(strcmp(command_2,"info")==0)
            {
                //show group info
            }
        }
        if(strcmp(command,"app")==0)
        {
            sscanf(buffer,"%s %s",command,command_2);
            if(strcmp(command_2,"status")==0)
            {
                //show app status
            }
        }
        else
        {
            printf("Command not recognized. Try again\n");
        }
    }
    return ;

}

int main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    int kvs_ls_sock, app_sock, n_client = 0;
    ssize_t numRead;
    pthread_t clients[100],localsv_ui;

    kvs_ls_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (kvs_ls_sock == -1)
    {
        printf("Error creating server socket\n");
        exit(-1);
    }

    remove(KVS_LS_SOCK_PATH);
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, KVS_LS_SOCK_PATH, sizeof(addr.sun_path) - 1);
    if (bind(kvs_ls_sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
    {
        printf("Error binding server socket\n");
        exit(-1);
    }
    if (listen(kvs_ls_sock, 1000) == -1)
    {
        printf("Error listening server socket\n");
        exit(-1);
    }

    //pthread_create(&localsv_ui, NULL, localserver_ui, &sock_auth);
    while (1)
    {
        app_sock = accept(kvs_ls_sock, NULL, NULL);
        if (app_sock == -1)
        {
            printf("Error connecting to application socket\n");
            exit(-1);
        }
        else
        {
            printf("Client connected\n");
            pthread_create(&clients[n_client], NULL, client_thread, &app_sock);
            printf("main depois thread");
            n_client++;
        }
    }
    return 0;
}
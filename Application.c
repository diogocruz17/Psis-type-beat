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

int local_server, aux = 1, i = 0;
int main(int argc, char *argv[])
{
    int connection = 0, i = 0, n_read, status_app, status_sv;
    char buffer[10000];
    char group_id[64], secret[128], key[128], command[20], value_aux[9500];
    char *value = NULL;
    local_server = init();
    if (local_server == -1)
    {
        printf("Erro na ligação com o servidor local. Exiting...");
        exit(-1);
    }

    while (connection != 1)
    {
        fgets(buffer, 1000, stdin);
        n_read = sscanf(buffer, "%s %s %s", command, group_id, secret);
        if ((strcmp(command, "connect")) != 0)
        {
            printf("Command input is wrong. Also you have to establish connection to a group before editing data. Try again \n");
            continue;
        }
        if (n_read < 3)
        {
            printf("Missing arguments.Try again\n");
            continue;
        }
        status_sv = establish_connection(group_id, secret);
        status_app = check_status_connection(status_sv, group_id);
        if (status_app == 1)
            break;
        if (status_app == 0)
            continue;
        if (status_app == -1)
            exit(-1);
    }
    while (1)
    {
        fgets(buffer, 10000, stdin);
        sscanf(buffer, "%s", command);
        if (strcmp(command, "put") == 0)
        {
            n_read = sscanf(buffer, "%s %s %s", command, key, value_aux);
            if (n_read < 3)
            {
                printf("Missing arguments.Try again\n");
                continue;
            }
            value = (char *)malloc(strlen(value_aux) + 1);
            strcpy(value, value_aux);
            status_sv = put_value(key, value);
            status_app = check_status_put(status_sv, key);
            if (status_app == 1)
                continue;
            if (status_app == -1 || status_app == -5)
                exit(-1);
        }
        if (strcmp(command, "get") == 0)
        {
            n_read = sscanf(buffer, "%s %s", command, key);
            if (n_read < 2)
            {
                printf("Missing arguments.Try again\n");
                continue;
            }
            status_sv = get_value(key, &value);
            status_app = check_status_get(status_sv, key, value);
            if (status_app == 1 || status_app == 0)
                continue;
            if (status_app == -1 || status_app == -5)
                exit(-1);
        }
        if (strcmp(command, "close") == 0)
        {

            status_sv = close_connection();
            if (status_app == 1)
            {
                printf("Closed connection to server.Exiting...\n");
                close(local_server);
                exit(0);
            }
            if (status_app == -1)
            {
                close(local_server);
                exit(-1);
            }
        }
        if (strcmp(command, "delete") == 0)
        {
            n_read = sscanf(buffer, "%s %s", command, key);
            if (n_read < 2)
            {
                printf("Missing arguments.Try again\n");
                continue;
            }
            status_sv = delete_value(key);
            status_app = check_status_delete(status_sv, key);
            //printf("%d %d\n",status_sv,status_app);
            if (status_app == 1 || status_app == 0) continue;
            if (status_app == -1 || status_app == -5) exit(-1);
        }
        else
        {
            printf("Command not recognized. Try again\n");
        }
    }

    return 0;
}
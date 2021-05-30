#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int local_server;
int establish_connection (char * group_id, char * secret)
{
    int connected=0,size=strlen("connect ")+strlen(group_id)+strlen(secret)+2;
    char* message=(char*)malloc(size);
    strcpy(message,"connect ");
    strcat(message,group_id);
    strcat(message," ");
    strcat(message,secret);
    if(write(local_server,message,size)==-1)
    {
        //printf("Lost connection to the server. Exiting...\n");
        return -1;
    }
    free(message);

    //read(local_server,&connected,sizeof(int));
    return connected;
    
}
int put_value(char * key, char * value)
{
    int returned,size=strlen("put ")+strlen(key)+strlen(value)+2;
    char* message=(char*)malloc(size);
    strcpy(message,"put ");
    strcat(message,key);
    strcat(message," ");
    strcat(message,value);
    if(write(local_server,message,size)==-1)
    {
        //printf("Lost connection to the server. Exiting...\n");
        return -1;
    }
    free(message);
    //read(local_server,&returned,sizeof(int));
    return returned;
}
int get_value(char *key, char ** value)
{
    return 0;
}
int delete_value(char * key)
{
    int size=strlen("delete ")+strlen(key)+1;
    char* message=(char*)malloc(size);
    strcpy(message,"delete ");
    strcat(message,key);
    if(write(local_server,&message,size)==-1)
    {
        printf("Lost connection to the server. Exiting...\n");
        return -1;
    }

    free(message);
    return 1;
}
int register_callback(char * key, void (*callback_function)(char *));
int close_connection()
{
    char message[6]="close";
    if(write(local_server,&message,strlen(message)+1)==-1)
    {
        printf("Lost connection to the server. Exiting...\n");
        return -1;
    }
    return 1;

}
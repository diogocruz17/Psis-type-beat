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
    int auth_return,size=strlen("connect ")+strlen(group_id)+strlen(secret)+2;
    char* message=(char*)malloc(size);
    strcpy(message,"connect ");
    strcat(message,group_id);
    strcat(message," ");
    strcat(message,secret);
    if(write(local_server,message,size)<1)
    {
        //printf("Lost connection to the server. Exiting...\n");
        return -1;
    }
    if(read(local_server,&auth_return,sizeof(int))<1){
        //printf("Connection error to local server.Exiting...\n");
        return -1;
    }
    free(message);
    return auth_return;
    
}
int put_value(char * key, char * value)
{
    int auth_return,size=strlen("put ")+strlen(key)+strlen(value)+2;
    char* message=(char*)malloc(size);
    strcpy(message,"put ");
    strcat(message,key);
    strcat(message," ");
    strcat(message,value);
    if(write(local_server,message,size) <1)
    {
        //printf("Lost connection to the server. Exiting...\n");
        return -1;
    }
    if(read(local_server,&auth_return,sizeof(int))<1){
        //printf("Connection error to local server.Exiting...\n");
        return -1;
    }
    free(message);
    free(value);
    return auth_return;
}
int get_value(char *key, char ** value)
{
    int auth_return,size=strlen("get ")+strlen(key)+1,value_size;
    char* message=(char*)malloc(size);
    char *value_server;
    strcpy(message,"get ");
    strcat(message,key);
    if(write(local_server,message,size) <1)
    {
        return -1;
    }
    if(read(local_server,&value_size,sizeof(int))<1){
        //printf("Connection error to local server.Exiting...\n");
        return -1;
    }
    if(value_size<0){
        return value_size;
    }
    value_server=(char*)malloc(value_size);
    if(read(local_server,value_server,value_size)<1){
        //printf("Connection error to local server.Exiting...\n");
        return -1;
    }
    strcpy(*(value),value_server);
    return 1;
}
int delete_value(char * key)
{
    int auth_return,size=strlen("delete ")+strlen(key)+1;
    char* message=(char*)malloc(size);
    strcpy(message,"delete ");
    strcat(message,key);
    if(write(local_server,message,size)<1)
    {
        printf("Lost connection to the server. Exiting...\n");
        return -1;
    }
    if(read(local_server,&auth_return,sizeof(int))<1){
        //printf("Connection error to local server.Exiting...\n");
        return -1;
    }

    free(message);
    return auth_return;
}
int register_callback(char * key, void (*callback_function)(char *));
int close_connection()
{
    char message[6]="close";
    if(write(local_server,message,strlen(message)+1)<1)
    {
        printf("Lost connection to the server. Exiting...\n");
        return -1;
    }
    return 1;

}
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define KVS_LS_SOCK_PATH "/tmp/kvs_ls"

int main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    int kvs_ls_sock, app_sock;
    ssize_t numRead;

    kvs_ls_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (kvs_ls_sock == -1){
        printf("Error creating server socket\n");
        exit(-1);
    }
    
    remove(KVS_LS_SOCK_PATH);
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, KVS_LS_SOCK_PATH, sizeof(addr.sun_path) - 1);
    if (bind(kvs_ls_sock, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1){
        printf("Error binding server socket\n");
        exit(-1);
    }
    if (listen(kvs_ls_sock, 1000) == -1){
        printf("Error listening server socket\n");
        exit(-1);
    }
    int num;
    while(1) { 
        app_sock = accept(kvs_ls_sock, NULL, NULL);
        if (app_sock == -1){
            printf("Error connecting to application socket\n");
            exit(-1);
        }
        read(app_sock,&num,sizeof(int));
        printf("%d\n",num);
    }
        
}
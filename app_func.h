/*******************************************
 *  int init() cria a ligação entre a
 *  aplicação e o local server.
 *  Retorna a socket em caso de sucesso
 *  e -1 se a ligação não for feita
 ******************************************/
int init();
int check_status_connection(int status, char *group_id);
int check_status_put(int status, char* key);
int check_status_get(int status,char* key,char* value);
int check_status_delete(int status,char* key);
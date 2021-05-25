/*******************************************
 *  int establish_connection tries to 
 *  connect a app to a group.
 *  Returns 0 if succesfull
 *  Returns -1 if connection to local server is lost
 *  Returns -2 if group doesnt exist
 *  Returns -3 if secret is wrong
 ******************************************/
int establish_connection (char * group_id, char * secret);
int put_value(char * key, char * value);
int get_value(char *key, char ** value);
int delete_value(char * key);
int register_callback(char * key, void (*callback_function)(char *));
int close_connection();

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list_groups.h"
#include "list_key_value.h"

typedef struct _keyvalue{
    char key[128];
    char *value;
}_keyvalue ;

typedef struct _groups{
    char group_id[64];
    char secret[128];
}_groups ;

int create_group(char *group_id, char *secret)
{
    groups new_group;
    strcpy(new_group.group_id,group_id);
    strcpy(new_group.secret,secret);
    

    
}
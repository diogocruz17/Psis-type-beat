/******************************************************************************
* (c) 2010-2019 AED Team
* Last modified: abl 2019-02-28
*
* NAME
*   list.h
*
* DESCRIPTION
*   Structure and prototypes for type t_lista, a 1st order abstract data type
*   that is a container.
*   Each variable of type t_lista implements a node of list of Items.
*
* COMMENTS
*
******************************************************************************/




/* type definition for structure to hold list item */
typedef struct keyvalue{
    char key[128];
    char *value;
    struct keyvalue *next;
}keyvalue;


keyvalue  *initKeyvalue(void);
keyvalue  *putValue (keyvalue *head,char *key, char *value);
char* getValue (keyvalue *head,char *key);
int findKey (keyvalue *head,char *key);
keyvalue *DeleteValue(keyvalue *head, char *key);
int numKeyvalue(keyvalue *head);
void freeKeyvalue(keyvalue *head);


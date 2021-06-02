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
typedef struct groups{
    char group_id[64];
    char secret[128];
    struct keyvalue *keyvalue_list;
    struct groups *next;
}groups;

groups  *initGroups(void);
groups  *createGroup (groups *head, char *group_id, char *secret);
int findGroup (groups *head,char *group_id);
groups *getGroup (groups *head,char *group_id);
char *getSecret (groups *node);
int getNumKeyvalue (groups *node);
int  DeleteGroup(groups *head, char *group_id);
void freeGroups(groups *head);



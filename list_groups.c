/******************************************************************************
* (c) 2010-2019 AED Team
* Last modified: abl 2019-02-28
*
* NAME
*   list.c
*
* DESCRIPTION
*   Implement general linked list functions, for use in word lists
*
* COMMENTS
*
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list_key_value.h"
#include "list_groups.h"

/*typedef struct keyvalue;

typedef struct groups{
    char group_id[64];
    char secret[128];
    struct keyvalue *keyvalue_list;
    struct groups *next;
}groups;*/




/******************************************************************************
* iniLista ()
*
* Arguments: none
* Returns: t_lista *
* Side-Effects: list is initialized
*
* Description: initializes list
*****************************************************************************/
groups  *initGroups(void)
{
    return NULL;
}


/******************************************************************************
* criaNovoNoLista ()
*
* Arguments: nome - Item to save in list node
* Returns: t_lista  *
* Side-Effects: none
*
* Description: creates and returns a new node that can later be added to the  <<<<<<<<<<<<<< FIX
*              list
*****************************************************************************/
groups  *createGroup (groups *head, char *group_id, char *secret)
{
    groups *aux,*new_node;
    aux = head;

    if(aux != NULL){
        while( aux->next != NULL){
            aux = aux->next;
        }
    }

    new_node = (groups*) malloc(sizeof(groups));
    if(new_node==NULL) return NULL;
    strcpy(new_node->group_id,group_id);
    strcpy(new_node->secret,secret);
    new_node->keyvalue_list=initKeyvalue();
    new_node->next=NULL;
    if(aux==NULL)
    {
        aux=new_node;
        return aux;
    }else{
        aux->next = new_node;
        return head;
    }
}


/******************************************************************************
* getItemLista ()
*
* Arguments: this - pointer to element
* Returns: Item
* Side-Effects: none
*
* Description: returns an Item from the list
*****************************************************************************/
int findGroup (groups *head,char *group_id)
{
    groups *aux;
    aux = head;

    if(aux != NULL){
        while( aux != NULL){
            if(strcmp(aux->group_id,group_id)==0){
                return 1;
            }
            aux = aux->next;
        }
    }
    return 0;

}

groups *getGroup (groups *head,char *group_id)
{
    groups *aux;
    aux = head;

    if(aux != NULL){
        while( aux != NULL){
            if(strcmp(aux->group_id,group_id)==0){
                return aux;
            }
            aux = aux->next;
        }
    }
    return NULL;
  
}

char *getSecret (groups *node)
{
    char secret_aux[128],*secret;
    strcpy(secret,node->secret);
    secret=(char*)malloc(strlen(secret_aux+1));
    strcpy(secret,secret_aux);
    return secret;
  
}

int getNumKeyvalue (groups *node)
{
    int num;
    if(node->keyvalue_list==NULL) return 0;
    num=numKeyvalue(node->keyvalue_list);
    return num;
  
}


/******************************************************************************
* getProxElementoLista ()
*
* Arguments: this - pointer to element
* Returns: pointer to next element in list
* Side-Effects: none
*
* Description: returns a pointer to an element of the list
*
*****************************************************************************/

int  DeleteGroup(groups *head, char *group_id)
{

    groups *aux,*temp;
    aux = head;
    if(aux != NULL){
        if(strcmp(aux->group_id,group_id)==0){
            head=head->next;
            freeKeyvalue(aux->keyvalue_list);
            free(aux);
            aux=temp;
            return 1;
        }
        while( aux != NULL){
            if(strcmp(aux->next->group_id,group_id)==0)
            {
                temp=aux->next->next;
                freeKeyvalue(aux->next->keyvalue_list);
                free(aux->next);
                aux->next=temp;
                return 1;
                 
            }
            aux = aux->next;
        }
    }
    return 0;
}


/******************************************************************************
* numItensNaLista ()
*
* Arguments: lp - pointer to list
* Returns:  count of the number of items in list
* Side-Effects: none
*
* Description: returns the number of items (nodes) in the list
*
*****************************************************************************/



/******************************************************************************
* libertaLista ()
*
* Arguments: lp - pointer to list
* Returns:  (void)
* Side-Effects: frees space occupied by list items
*
* Description: free list
*
*****************************************************************************/

void freeGroups(groups *head)
{
    groups *aux, *newhead; 

    for(aux = head; aux != NULL; aux = newhead) {
        newhead = aux->next;
        freeKeyvalue(aux->keyvalue_list);
        free(aux);
    }

    return;
}


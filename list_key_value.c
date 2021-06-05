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

/*typedef struct keyvalue{
    char key[128];
    char *value;
    struct keyvalue *next;
}keyvalue ;*/




/******************************************************************************
* iniLista ()
*
* Arguments: none
* Returns: t_lista *
* Side-Effects: list is initialized
*
* Description: initializes list
*****************************************************************************/
keyvalue  *initKeyvalue(void)
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
keyvalue  *putValue (keyvalue *head,char *key, char *value)
{
    keyvalue *aux,*new_node;
    aux = head;

    if(aux != NULL){
        while( aux->next != NULL){
            if(strcmp(aux->key,key)==0){
                aux->value=(char*)realloc(aux->value,strlen(value)+1);
                strcpy(aux->value,value);
                return head;
            }
            aux = aux->next;
        }
    }

    new_node = (keyvalue*) malloc(sizeof(keyvalue));
    if(new_node==NULL) return NULL;
    strcpy(new_node->key,key);
    new_node->value=(char*)malloc(strlen(value)+1);
    if(new_node->value==NULL) return NULL;
    strcpy(new_node->value,value);
    new_node->next=NULL;
    if(head==NULL)
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
char* getValue (keyvalue *head,char *key)
{
    keyvalue *aux;
    aux = head;
    char *value;

    if(aux != NULL){
        while( aux != NULL){
            if(strcmp(aux->key,key)==0){
                return aux->value;
            }
            aux = aux->next;
        }
    }
    return NULL;

    
}



int findKey (keyvalue *head,char *key)
{
    keyvalue *aux;
    aux = head;

    if(aux != NULL){
        while( aux != NULL){
            if(strcmp(aux->key,key)==0){
                return 1;
            }
            aux = aux->next;
        }
    }
    return 0;

    
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

keyvalue *DeleteValue(keyvalue *head, char *key)
{

    keyvalue *aux,*temp;
    aux = head;
    if(aux != NULL){
        if(strcmp(aux->key,key)==0){
            head=head->next;
            free(aux->value);
            free(aux);
            return head;
        }
        while( aux != NULL){
            if(strcmp(aux->next->key,key)==0)
            {
                temp=aux->next->next;
                free(aux->next->value);
                free(aux->next);
                aux->next=temp;
                return head;
                 
            }
            aux = aux->next;
        }
    }
    //return 0;
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

int numKeyvalue(keyvalue *head)
{
    keyvalue *aux=head;  
    int count = 0;

    while(aux!=NULL){
        count++;
        aux=aux->next;
    }
    return count;
    
}

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

void freeKeyvalue(keyvalue *head)
{
    keyvalue *aux, *newhead; 

    for(aux = head; aux != NULL; aux = newhead) {
        newhead = aux->next;
        free(aux->value);
        free(aux);
    }

    return;
}


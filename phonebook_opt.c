#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char *lastName, hashtable *hash)
{
    /* TODO: implement */
    entry *e;
    int index = hash_djb2(hash, lastName);
    for(e = hash->table[index]; e != NULL; e = e->pNext) {
        if(strcasecmp(lastName,e->lastName)==0) {
            return(e);
        }
    }
    return NULL;
}

entry *append(char *lastName,hashtable *hash)
{
    int index = hash_djb2(hash, lastName);
    entry *newentry;
    newentry = (entry *)malloc(sizeof(entry));
    if(newentry == NULL) {
        return(NULL);
    }

    strcpy(newentry->lastName, lastName);
    newentry->pNext = hash->table[index];
    hash->table[index] = newentry;
    return 0;
}

hashtable *CreateTable(int hash_tablesize)
{

    hashtable *hash = NULL;

    if(hash_tablesize < 1) { /*check size*/
        return(NULL);
    }
    /*allocate hash table*/
    if((hash = (hashtable *)malloc(sizeof(hashtable)))== NULL) {
        return(NULL);
    }
    if((hash->table = malloc(sizeof(entry*) * hash_tablesize))== NULL) {
        return(NULL);
    }
    hash->size = hash_tablesize;
    return(hash);

}
int hash_djb2(hashtable *hash,char *findName)
{
    unsigned int hash_value = 5381;
    while(*findName != '\0') {
        hash_value = ((hash_value << 5) + hash_value) + (*findName++);
    }
    return(hash_value % (hash->size));

}

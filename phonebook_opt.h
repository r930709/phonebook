#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* original version */
typedef struct __PHONE_BOOK_ENTRY {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __PHONE_BOOK_ENTRY *pNext;
} phonebook_detail;

typedef struct __FIND_NAME_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    phonebook_detail *detail;
    struct __FIND_NAME_ENTRY *pNext;
} entry;


entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);

#endif

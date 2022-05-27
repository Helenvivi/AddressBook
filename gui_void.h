#ifndef GUI_H_VOID
#define GUI_H_VOID

#define Error -2;
#define Ok -1;

#include <stdio.h>
#include <string.h>

typedef struct Date 
{
    int sex;
    char age[20];
    char postcode[20];
    char company[20];
}Date;

typedef struct DateNode
{
    Date *datepointer;
    struct DateNode *pnext;
    struct DateNode *plast;
    char name[20];
    char phone[20];
    char email[20];
    char address[20];
    int myclass;
    int numb;
} DateNode;

typedef struct Addressbook
{
    DateNode *pfnode;
    DateNode *plnode;
    int Exitnode;
}Addressbook;

void AddBookGui();
void DeleteAddGui();
void TypeAddGui();
void AddGui();
void CheckAddGui();
void AddBookNoteGui(DateNode *node);
void AddBookNoteFprintf(FILE *fp,DateNode *node);
#endif
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

// #include"SONDS.h"

/*List version for CSon*/
/*DATE 05242022*/
#ifndef __LIST_H
#define __LIST_H

#define EX_RANGE 3
#define double_size sizeof(double)
#define int_size sizeof(int)
#define str_size sizeof(Str *)
#define jobj_size sizeof(int *)
typedef enum{
    type_NULL = 0,
    type_int,
    type_double,
    // type_Str,
    type_jobj,
    type_list,
    type_ptr,
    type_other
}Type_data;

typedef struct{
    int length;
    int currentLength;
    Type_data type;
    int type_size;
    
    void *content_Hook;
}List;


List List_newList(int initSize,Type_data type);
List *List_initList(int initSize,Type_data type);
void List_dropList(List *L);
void List_ClearList(List *L);
void List_append(List *L,void *appendData);
void *List_pop(List *L,int popos);
void *List_divide_Arr(List *L,int low,int high);
List *List_divide_List(List *L,int low,int high);
void *List_insert(List *L,void *insertdata,int pos);
void *List_getItem(List *L,int index);

void List_consoleLog(List *L);
bool List_isFull(List *L);
void List_freelist(List *L);

void *List_loadInt(int *data);
void *List_loadDouble(double *data);
// void *List_loadStr(SONDS *data);
int *List_contentDumpInt(List *L);
double *List_contentDumpDouble(List *L);
// Str *List_contentDumpStr(List *L);


#endif
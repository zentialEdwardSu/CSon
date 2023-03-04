/**
 * @file SONDS.h
 * @author EdwardSu zentialeds@gmail.com
 * @brief SONDS version for CSon
 * @version 0.1
 * @date 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include<stdbool.h>

#ifndef __SONDS__
#define __SONDS__

#define tochar SONDS_to_char

typedef struct SONDS{
    int length;
    int free;
    char *data;
}SONDS;

typedef SONDS Str;

size_t SONDS_str_size(SONDS *s);
SONDS SONDS_new(char *string);
SONDS *SONDS_new_pointer(char *string);
SONDS SONDS_new_noalloc(char *string);
SONDS *SONDS_new_pointer_noalloc(char *string);
void SONDS_consoleLog(SONDS *s);
int SONDS_printf(SONDS *s);
char *SONDS_to_char(SONDS *s);
SONDS* SONDS_add_char(SONDS *base, char *toadd);
SONDS* SONDS_add(SONDS *base, SONDS *toadd);
SONDS SONDS_divide(SONDS *todivide,int low,int high);
SONDS* spiltSONDS(SONDS *tospilt,char signal);
SONDS* spiltSONDS_keepStruct(SONDS *tospilt,char signal);
int SONDS_checkSame(SONDS *s1, SONDS *s2);
void SONDS_free(SONDS *s);
int SONDS_is_null(SONDS *s);
void _Next(SONDS *T,int *next);
int SONDS_serach(SONDS *S,SONDS *T);

#endif
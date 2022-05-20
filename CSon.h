/**
 * @file CSon.h
 * @author EdwardSu 
 * @brief Json decoder and Compiler base on C
 * @version 0.0.1
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __CSON_H
#define __CSON_H

#ifndef __SONDS_H
#include"SONDS.h"
#endif

#ifndef __LIST_H
#include"List.h"
#endif
typedef enum{
    base = 0,
    INT,
    DOUBLE,
    STRING,
    LIST,
    OBJ
}TYPE;

typedef struct Jobj{
    SONDS name;//Key for the Jobj obj
    TYPE type;//Mark the type of this Jobj
    struct Jobj *pre;//Point to the previous Jobj for same level
    struct Jobj *next;//Point to the next Jobj for same level
    void *Hook;//Value of the Jobj, where the data while be mounted
}Jobj;

Jobj Jobj_Jsontranslater(char *json_string);
SONDS *Jobj_JsonCompiler(Jobj *jobj_base);
Jobj Jobj_newJobj();
Jobj *Jobj_initJobj();
TYPE Jobj_judge_type(char *str);
Jobj* Jobj_seekend(Jobj *obj);

Jobj *Jobj_appendOBJ(SONDS *obj_string);
Jobj *Jobj_OBJaddKV(SONDS *s);

Jobj *Jobj_appendList(char *list_string);
Jobj *Jobj_ListaddELE(Jobj *data_hook,Type_data add_type,void *data);

SONDS *renderList(List *list_content);
SONDS *renderOBJ(Jobj *Hook_content);
#endif
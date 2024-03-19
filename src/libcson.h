//
// Created by Su on 24-3-19.
//
#pragma once
#include "sonds.h"
#include "List.h"

#ifndef LIBCSON_H
#define LIBCSON_H

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

Jobj *Jobj_Json_translater(char *json_string);
SONDS *Jobj_Json_Compiler(Jobj *jobj_base);
Jobj Jobj_newJobj();
Jobj *Jobj_initJobj();
TYPE Jobj_judge_type(char *str);
Jobj* Jobj_seekend(Jobj *obj);

Jobj *Jobj_appendOBJ(SONDS *obj_string);
Jobj *Jobj_OBJaddKV(SONDS *s);

List *Jobj_appendList(char *list_string);
Jobj *Jobj_ListaddELE(Jobj *data_hook,Type_data add_type,void *data);

SONDS *renderList(List *list_content);
SONDS *renderOBJ(Jobj *Hook_content,int no_head);

Jobj *Jobj_Getby_Key(Jobj *obj,SONDS key);
Jobj *Jobj_Getby_Path(Jobj *obj,SONDS *path);

#endif //LIBCSON_H

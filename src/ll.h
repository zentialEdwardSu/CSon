//
// Created by Su on 2023/11/29.
//
# include <stdlib.h>
# include "sonds.h"

#ifndef LL_H
#define LL_H

#define CACHE_SIZE 5

typedef struct Codell {
    char data;
    float freq;
    Str *code;
    struct Codell *next_code;
} Codell;

typedef struct Cachell {
    Codell* node;
} Cache;

Codell* initializeList();
Codell* insertAtEnd(struct Codell* head, char data, float freq,Str *code_str);
int len(struct Codell* head);
void freeList(struct Codell* head);
Codell *findViaCache(Codell * llhead,Cache *cc, char key);
Cache *initCache();

#endif //LL_H
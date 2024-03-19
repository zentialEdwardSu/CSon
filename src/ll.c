//
// Created by 28405 on 2023/11/29.
//

#include "ll.h"
#include "sonds.h"

Codell* initializeList() {
    return NULL;
}

Codell* insertAtEnd(struct Codell* head, char data, float freq,Str *code_str) {
    struct Codell* newNode = (struct Codell*)malloc(sizeof(struct Codell));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newNode->data = data;
    newNode->freq = freq;
    newNode->code = code_str;
    newNode->next_code = NULL;

    if (head == NULL) {
        return newNode;
    }

    Codell* current = head;
    while (current->next_code != NULL) {
        current = current->next_code;
    }

    current->next_code = newNode;
    return head;
}

int len(struct Codell* head) {
    int length = 0;
    Codell* current = head;

    while (current != NULL) {
        length++;
        current = current->next_code;
    }

    return length;
}

void freeList(struct Codell* head) {
    struct Codell* current = head;
    struct Codell* nextNode;

    while (current != NULL) {
        nextNode = current->next_code;
        SONDS_free(current->code);
        free(current);
        current = nextNode;
    }
}

/**
 * \brief init cache for search
 * \return
 */
Cache *initCache(Codell *codebook) {
    Codell *c = codebook->next_code;
    Cache *cl = malloc(CACHE_SIZE*sizeof(Cache));
    for(int i=0; i< CACHE_SIZE;i++) {
        cl[i].node = c;
        c = c->next_code;
    }
    return cl;
}

Codell *findViaCache(Codell * llhead,Cache *cc, char key) {

    // search in cache
    for(int i=0;i < CACHE_SIZE;i++) {
        if(cc[i].node != NULL && cc[i].node->data == key) {
            return cc[i].node;
        }
    }

    // search in ll and update cache
    Codell* current = llhead;
    while (current != NULL) {
        if (current->data == key) {
            //move cache
            for (int i = CACHE_SIZE - 1; i > 0; --i) {
                cc[i] = cc[i - 1];
            }
            cc[0].node = current;
            return current;
        }
        current = current->next_code;
    }

    return NULL;
}

#ifndef __STACK_H
#define __STACK_H

#include<assert.h>
#include<stdbool.h>
#include"CSon.h"

#define OK 1
#define ERROR 0
#define MAX(a,b) a>=b?a:b;
#define MAX_node(a,b) a->data>=b->data?a:b;
#define MIN(a,b) a<=b?a:b;
#define EXTENDSTEP 3

#endif

//int���͵�״̬��
typedef int Status_code;
// typedef Jobj ElementType;
typedef char CommonType;

// ���ݽṹ����

//ջ��Ӧ���ָ��Jobj��ָ�� *Jobj
//��������ջ�ṹ
typedef struct{
    Jobj **basement;//ջ�ױ�ʶ
    Jobj **top;//ջ����ʶ Ϊջ��+�������+1��λ��
    Jobj **cursor;//�����α�
    int max_stack_size;//�������
}Jstack;


//��ʼ���������Ϊinit_size��ջ
Status_code init_Jstack(Jstack *to_init,int init_size){
    to_init->basement = to_init ->cursor = (Jobj **)malloc(sizeof(Jobj *)*(init_size+1));

    to_init->top = to_init ->basement+init_size;
    to_init->max_stack_size = init_size;
}
//����ջ�������ջ
Status_code Jstack_push_nolimit(Jstack *to_push,Jobj *push_data){
    if(to_push->cursor == to_push->top){
        Jobj **tmp = (Jobj **)malloc(sizeof(Jobj *)*(to_push->max_stack_size+EXTENDSTEP));
        memcpy(tmp,to_push->basement,(to_push->max_stack_size*sizeof(Jobj *)));
        free(to_push->basement);
        to_push->basement = tmp;
        to_push->top = to_push->basement + to_push->max_stack_size +EXTENDSTEP+1;
        to_push->cursor = to_push->basement + to_push->max_stack_size;
        to_push->max_stack_size+=EXTENDSTEP;
    }
    *to_push->cursor++ = push_data;
    return OK;
}
//��ջ��ȡ��������Ԫ��
Jobj *Jstack_Pop(Jstack *to_pop){
    Jobj *pop_data;
    if(to_pop->cursor == to_pop->basement)return ERROR;
    pop_data = *--to_pop->cursor;
    return pop_data;
}

//���ջ
Status_code Jstack_clear(Jstack *to_clear){
    to_clear->cursor = to_clear->basement;
    return OK;
}
//����ջ
Status_code Jstack_drop(Jstack *to_drop){
    if(to_drop->basement){
        free(to_drop->basement);
        return OK;
    }
}
//���ջ���ڵĳ���
int Jstack_current_cursor(Jstack *to_current){
    return (int)(to_current->cursor-to_current->basement);
}
Status_code Jstack_full(Jstack *stack){
    if(stack->cursor==(stack->top-1)){
        return OK;
    }
    return ERROR;
}
Status_code Jstack_empty(Jstack *stack){
    if(stack->cursor==stack->basement){
        return OK;
    }
    return ERROR;
}
#ifndef __CSON_H
#define __CSON_H

#include"SONDS.h"

#endif

#ifndef __BASE__
#define __BASE__
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#endif
typedef enum{
    base = 0,
    STRING,
    ARR,
    OBJ
}TYPE;

typedef struct Jobj{
    SONDS name;//Jobj�Ĺؼ���(Key)
    TYPE type;//��ע��Jobj������
    struct Jobj *pre;//ָ��ͬ��ǰһ���ؼ��ֵ�ָ��
    struct Jobj *next;//ָ��ͬ����һ���ؼ��ֵ�ָ��
    void *Hook;//Jobj��ֵ(Value),voidָ��������ݹ��ص�,���ڹ���������
}Jobj;

//Json����Ļ���
Jobj newJobj(){
    Jobj json;
    json.name = newSONDS_nomore("BASE");
    json.type = base;
    json.pre = NULL;
    json.next = NULL;
    json.Hook = NULL;

    return json;
}

//��hook����µ� {} ��ʽ�ṹ
Jobj *appendOBJ(Jobj *JobjtoaObj){
    

}

//��{}������µļ�ֵ��
Jobj *OBJaddKV(){

}

//��hook�������µ� [] �ṹ
Jobj *appendList(){

}

//��[]��β������µ�Ԫ��
Jobj *ListaddELE(){

}

//��Jobj��ʽ������ת��ΪSONDS�ṹ���ַ���
SONDS JsonCompiler(){

}

//���ַ����ṹ������ת����
Jobj JsonDecoder(){

}

//ʹ�� xpath ����·����Jobj�з��ʶ���
Jobj *JobjGet(){

}

//ʹ��SONDS��ʽ�Ĺؼ�����ȫ�ַ�Χ�ڲ����ض�ֵ
Jobj *JobjQuery(){

}
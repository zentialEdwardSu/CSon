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
    SONDS name;//Jobj的关键字(Key)
    TYPE type;//标注该Jobj的类型
    struct Jobj *pre;//指向同级前一个关键字的指针
    struct Jobj *next;//指向同级后一个关键字的指针
    void *Hook;//Jobj的值(Value),void指针类的数据挂载点,用于挂载子数据
}Jobj;

//Json对象的基底
Jobj newJobj(){
    Jobj json;
    json.name = newSONDS_nomore("BASE");
    json.type = base;
    json.pre = NULL;
    json.next = NULL;
    json.Hook = NULL;

    return json;
}

//在hook添加新的 {} 形式结构
Jobj *appendOBJ(Jobj *JobjtoaObj){
    

}

//在{}内添加新的键值对
Jobj *OBJaddKV(){

}

//在hook里增加新的 [] 结构
Jobj *appendList(){

}

//在[]的尾部添加新的元素
Jobj *ListaddELE(){

}

//将Jobj形式的数据转换为SONDS结构的字符串
SONDS JsonCompiler(){

}

//将字符串结构的数据转换成
Jobj JsonDecoder(){

}

//使用 xpath 风格的路径在Jobj中访问对象
Jobj *JobjGet(){

}

//使用SONDS形式的关键词在全局范围内查找特定值
Jobj *JobjQuery(){

}
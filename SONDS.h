
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include<stdbool.h>

#ifndef __SONDS_H
#define __SONDS_H

#define sDS standardizeSONDS

/*LastEdit 1:05 2022-5-1*/

typedef struct SONDS{
    int length;
    int free;
    char *data;
}SONDS;

typedef SONDS Str;

/*Give whole size of Str s*/
size_t sizeofSONDS(SONDS *s){
    return s->length+s->free+1+sizeof(SONDS);
}

SONDS newSONDS(char *string){
    SONDS newOne;
    newOne.length = strlen(string);
    newOne.free = newOne.length*2;
    newOne.data = (char *)malloc(newOne.free+1);
    memcpy(newOne.data,string,newOne.length);
    newOne.data[newOne.length] = '\0';
    newOne.free=newOne.length;

    return newOne;
}

// New SONDS with no extra place for just division
SONDS newSONDS_nomore(char *string){
    SONDS newOne;
    newOne.length = strlen(string);
    newOne.free = 0;
    newOne.data = (char *)malloc(newOne.length+1);
    memcpy(newOne.data,string,newOne.length);
    newOne.data[newOne.length] = '\0';

    return newOne;
}

void consoleLogSONDS(SONDS *s){
    printf("Length:%d;\r\nFree:%d;\n",s->length,s->free);
    printf("Data:%s\n",s->data);
}

int printfSONDS(SONDS *string){
    int printfSize = printf("%s\n",string->data);
    return printfSize;
}

char *standardizeSONDS(SONDS *s){
    return s->data;
}

SONDS* addCharSONDS(SONDS *base, char *toadd){
    int addLen = strlen(toadd);
    int diff = base->free - addLen;
    char *tmpdata;
    if(diff<0){
        tmpdata = (char *)malloc((base->length+addLen+1)*2);
        memcpy(tmpdata,base->data,base->length);
        char *tmpftmp = tmpdata+base->length;
        memcpy(tmpftmp,toadd,addLen);
        tmpftmp[addLen+1] = '\0';
        base->length = base->length+addLen;
        base->free = base->length;

        tmpftmp = base->data;
        free(tmpftmp);
        base->data = tmpdata;
    }else{
        char *tmpftmp = tmpdata+base->length;
        memcpy(tmpftmp,toadd,addLen);
        tmpftmp[addLen+1] = '\0';
        base->free = diff;
        base->length += addLen;
    }
    return base;
}

SONDS* addSONDS(SONDS *base, SONDS *toadd){
    // int addLen = strlen(toadd);
    int diff = base->free - toadd->length;
    char *tmpdata;
    if(diff<0){
        tmpdata = (char *)malloc((base->length+toadd->length+1)*2);
        memcpy(tmpdata,base->data,base->length);
        char *tmpftmp = tmpdata+base->length;
        memcpy(tmpftmp,toadd->data,toadd->length);
        tmpftmp[toadd->length+1] = '\0';
        base->length = base->length+toadd->length;
        base->free = base->length;

        tmpftmp = base->data;
        free(tmpftmp);
        base->data = tmpdata;
    }else{
        char *tmpftmp = tmpdata+base->length;
        memcpy(tmpftmp,toadd,toadd->length);
        tmpftmp[toadd->length+1] = '\0';
        base->free = diff;
        base->length += toadd->length;
    }
    return base;
}

//include low, High not included; index start from 0; 
//>>> ex: ABCDEFG [0,3]->ABC
SONDS divideSONDS(SONDS *todivide,int low,int high){
    if(low < 0){
        low = todivide->length+low;
    }
    if(high < 0){
        high = todivide->length+high;
    }
    if(low>high){
        printf("[SONDS WARN]Low must smaller than high: Now low:%d;High:%d",low,high);
        return newSONDS("");
    }else if(high>todivide->length){
        printf("[SONDS WARN]High interger out of range;High:%d;length:%d",high,todivide->length);
        return newSONDS("");
    }
    int size = high-low;
    char *tmp = todivide->data+low;
    char *tmpdata = (char *)malloc(size+1);
    memcpy(tmpdata,tmp,size);
    tmpdata[size] = '\0';
    return newSONDS(tmpdata);
}

SONDS* spiltSONDS(SONDS *tospilt,char signal){
    int spiltpos = 0;
    while(spiltpos<tospilt->length)
    {
        if(tospilt->data[spiltpos]==signal){
            break;
        }
        spiltpos++;
    }
    // printf("spilt:%d\n",spiltpos);
    SONDS preDivide = divideSONDS(tospilt,0,spiltpos);
    // printf("size prediff : %d\n",sizeof(preDivide));
    SONDS sufDivide = divideSONDS(tospilt,spiltpos+1,tospilt->length);
    SONDS *resDivided = (SONDS *)malloc(2*sizeof(SONDS));
    resDivided[0] = preDivide;
    resDivided[1] = sufDivide;
    return resDivided;
}

void Next(SONDS *T,int *next){
    int i=1;
    next[1]=0;
    int j=0;
    while (i< T->length) {
        if (j==0||T->data[i-1]==T->data[j-1]) {
            i++;
            j++;
            if (T->data[i-1]!=T->data[j-1]) {
               next[i]=j;
            }
            else{
                next[i]=next[j];
            }
        }else{
            j=next[j];
        }
    }
}

int kmpSONDS(SONDS *S,SONDS *T){
    int *next = (int *)malloc(T->length*sizeof(int));
    Next(T,next);//根据模式串T,初始化next数组
    int i=1;
    int j=1;
    while (i<=S->length&&j<=T->length)
    {
        //j==0:代表模式串的第一个字符就和指针i指向的字符不相等；S[i-1]==T[j-1],如果对应位置字符相等，两种情况下，指向当前测试的两个指针下标i和j都向后移
        if (j==0 || S->data[i-1]==T->data[j-1]) {
            i++;
            j++;
        }else{
            j=next[j];//两个字符不相等，i不动，j变为当前测试字符串的next值
        }
    }
    if (j>T->length) {//如果条件为真，说明匹配成功
        return i - T->length-1;
    }
    return -1;
}

#endif
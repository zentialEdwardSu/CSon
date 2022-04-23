#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>


#define sDS standardizeSONDS
typedef struct SONDS{
    int length;
    int free;
    char *data;
}SONDS;

typedef SONDS Str;

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

void consoleLog(SONDS *s){
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

SONDS* addChar(SONDS *base, char *toadd){
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

//include low, High ex: ABCDEFG [0,3] ABC
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

SONDS* spiltSONDAS(SONDS *tospilt,char signal){
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
    // SONDS *resDivided = (SONDS *)malloc(preDivide.length+sufDivide.length+2+sizeof(SONDS)*2);
    // *resDivided = preDivide;
    // resDivided+=(1+sizeof(SONDS)+preDivide.length);
    // *resDivided = sufDivide;
    return resDivided;
}
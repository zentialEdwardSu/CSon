#include "SONDS.h"

/**
 * @brief get size of a SONDS struct
 * 
 * @param s 
 * @return size_t 
 */
size_t SONDS_str_size(SONDS *s){
    return s->length+s->free+1+sizeof(SONDS);
}

/**
 * @brief use char* to create a SONDS
 * 
 * @param string 
 * @return SONDS 
 */
SONDS SONDS_new(char *string){
    SONDS newOne;
    newOne.length = strlen(string);
    newOne.free = newOne.length*2;
    newOne.data = (char *)malloc(newOne.free+1);
    memset(newOne.data,0,newOne.free);
    memcpy(newOne.data,string,newOne.length);
    newOne.data[newOne.length] = '\0';
    newOne.free=newOne.length;

    return newOne;
}

/**
 * @brief use char* to create a SONDS
 * 
 * @param string 
 * @return SONDS* 
 */
SONDS *SONDS_new_pointer(char *string){
    SONDS *newOne = (SONDS *)malloc(sizeof(SONDS));
    newOne->length = strlen(string);
    newOne->free = newOne->length*2;
    newOne->data = (char *)malloc(newOne->free+1);
    memset(newOne->data,0,newOne->free);
    memcpy(newOne->data,string,newOne->length);
    newOne->data[newOne->length] = '\0';
    newOne->free=newOne->length;

    return newOne;
}
/**
 * @brief use char* to create a SONDS do not alloc extra memory
 * 
 * @param string 
 * @return SONDS 
 */
SONDS SONDS_new_noalloc(char *string){
    SONDS newOne;
    newOne.length = strlen(string);
    newOne.free = 0;
    newOne.data = (char *)malloc(newOne.length+1);
    memset(newOne.data,0,newOne.free);
    memcpy(newOne.data,string,newOne.length);
    newOne.data[newOne.length] = '\0';

    return newOne;
}

/**
 * @brief use char* to create a SONDS do not alloc extra memory
 * 
 * @param string 
 * @return SONDS* 
 */
SONDS *SONDS_new_pointer_noalloc(char *string){
    SONDS *newOne = (SONDS *)malloc(sizeof(SONDS));
    newOne->length = strlen(string);
    newOne->free = 0;
    newOne->data = (char *)malloc(newOne->free+1);
    memset(newOne->data,0,newOne->free);
    memcpy(newOne->data,string,newOne->length);
    newOne->data[newOne->length] = '\0';
    newOne->free=newOne->length;

    return newOne;
}

/**
 * @brief Log struct for SONDS
 * 
 * @param s 
 */
void SONDS_consoleLog(SONDS *s){
    printf("Length:%d;\r\nFree:%d;\n",s->length,s->free);
    printf("Data:%s\n",s->data);
}

/**
 * @brief print sonds to stdout return printed size
 * 
 * @param string 
 * @return int 
 */
int SONDS_printf(SONDS *s){
    int printfSize = printf("%s\n",s->data);
    return printfSize;
}

/**
 * @brief Convert SONDS to char*
 * 
 * @param s 
 * @return char* 
 */
char *SONDS_to_char(SONDS *s){
    return s->data;
}

/**
 * @brief append char* to a SONDS
 * 
 * @param base 
 * @param toadd 
 * @return SONDS* 
 */
SONDS* SONDS_add_char(SONDS *base, char *toadd){
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
        char *tmpftmp = base->data+base->length;
        memcpy(tmpftmp,toadd,addLen);
        tmpftmp[addLen+1] = '\0';
        base->free = diff;
        base->length += addLen;
    }
    return base;
}

/**
 * @brief contact two SONDS return the base SONDS 
 * 
 * @param base 
 * @param toadd 
 * @return SONDS* 
 */
SONDS* SONDS_add(SONDS *base, SONDS *toadd){
    // int addLen = strlen(toadd);
    int diff = base->free - toadd->length;
    char *tmpdata = NULL;
    if(diff<0){
        int malloc_size = (base->length+toadd->length)*2+1;
        tmpdata = (char *)malloc(malloc_size);
        memset(tmpdata,0,malloc_size);
        memcpy(tmpdata,base->data,base->length);
        char *tmpftmp = tmpdata+base->length;
        memcpy(tmpftmp,toadd->data,toadd->length);
        tmpftmp[toadd->length+1] = '\0';
        base->length = base->length+toadd->length;
        base->free = base->length;

        tmpftmp = base->data;
//        free(tmpftmp)
        base->data = tmpdata;
    }else{
        char *tmpftmp = base->data+base->length;
        memcpy(tmpftmp,toadd->data,toadd->length);
        base->free = diff;
        base->length += toadd->length;
        tmpftmp[toadd->length+1] = '\0';
    }
    return base;
}

/**
 * @brief create a slice , include low, High not included; index start from 0; 
 * 
 * @param todivide 
 * @param low 
 * @param high 
 * @return SONDS 
 */
SONDS SONDS_divide(SONDS *todivide,int low,int high){
    char *tmp_data = NULL;
    if(low < 0){
        low = todivide->length+low;
    }
    if(high < 0){
        high = todivide->length+high;
    }
    if(low>high){
#ifdef DEBUG
        printf("[SONDS WARN]Low must smaller than high: Now low:%d;High:%d",low,high);
#endif
        return SONDS_new("");
    }else if(high>todivide->length){
#ifdef DEBUG
        printf("[SONDS WARN]High interger out of range;High:%d;length:%d",high,todivide->length);
#endif
        return SONDS_new("");
    }
    int size = high-low;
    char *tmp = todivide->data+low;
    tmp_data = (char *)malloc(size+1);
    memcpy(tmp_data,tmp,size+1);
    tmp_data[size] = '\0';
    return SONDS_new(tmp_data);
}

/**
 * @brief Spilt SONDS by a Ascii char return (pre,after)
 * 
 * @param tospilt 
 * @param signal 
 * @return SONDS* 
 */
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
    SONDS preDivide = SONDS_divide(tospilt,0,spiltpos);
    // printf("size prediff : %d\n",sizeof(preDivide));
    SONDS sufDivide = SONDS_divide(tospilt,spiltpos+1,tospilt->length);
    SONDS *resDivided = (SONDS *)malloc(2*sizeof(SONDS));
    resDivided[0] = preDivide;
    resDivided[1] = sufDivide;
    return resDivided;
}

/**
 * @brief keep special struct while during spilt process
 * @note example
 * @code
 *      "A:[1,2],B:3"
 *      get [A:[1,2],B:3]
 * @endcode
 * @param tospilt SONDS to be spilled
 * @param signal
 * @return SONDS * arr [before signal, after signal]
 */
SONDS* spiltSONDS_keepStruct(SONDS *tospilt,char signal){
    int spiltpos = 0;
    int struct_flag = 0;
    while(spiltpos<tospilt->length)
    {
        switch(tospilt->data[spiltpos]){
            case '[':case '{':case '(':
                struct_flag = 1;
                break;
            case ']':case '}':case ')':
                struct_flag = 0;
                break;
        }
        if(tospilt->data[spiltpos]==signal && !struct_flag){
            break;
        }
        spiltpos++;
    }
    // printf("spilt:%d\n",spiltpos);
    SONDS preDivide = SONDS_divide(tospilt,0,spiltpos);
    // printf("size prediff : %d\n",sizeof(preDivide));
    SONDS sufDivide = SONDS_divide(tospilt,spiltpos+1,tospilt->length);
    SONDS *resDivided = (SONDS *)malloc(2*sizeof(SONDS));
    resDivided[0] = preDivide;
    resDivided[1] = sufDivide;
    return resDivided;
}

/**
 * @brief compare two SONDS if the same
 * 
 * @param s1 
 * @param s2 
 * @return int 
 */
int SONDS_checkSame(SONDS *s1, SONDS *s2){
    if(!strcmp(s1->data,s2->data))
        return 1;
    return 0;
}

/**
 * @brief free a SONDS
 * 
 * @param s 
 */
void SONDS_free(SONDS *s){
    free(s->data);
    free(s);
}

/**
 * @brief SONDS is null or not
 * 
 * @param s 
 * @return int 
 */
int SONDS_is_null(SONDS *s){
    return s->length?0:1;
}

void _Next(SONDS *T,int *next){
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

/**
 * @brief serach T in s return the pos that T first appear, -1 for not in
 * 
 * @param S 
 * @param T 
 * @return int 
 */
int SONDS_serach(SONDS *S,SONDS *T){
    int *next = (int *)malloc(T->length*sizeof(int));
    _Next(T,next);//Init next Arr base on input 
    int i=1;
    int j=1;
    while (i<=S->length&&j<=T->length)
    {
        /*
        j==0 stands for the first in model is diff from the char which pointed by i&&
        S[i-1]==T[j-1],char equal in match place 
        In these two situation i,j move backward*/
        if (j==0 || S->data[i-1]==T->data[j-1]) {
            i++;
            j++;
        }else{
            //do not match i stay j turn to be the value in next
            j=next[j];
        }
    }
    if (j>T->length) {//True will match process done 
        return i - T->length-1;
    }
    return -1;
}
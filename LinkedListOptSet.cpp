#include "LinkedListOptSet.h"


#define NONVOID 0
// #define OVERFLOW 1
#define NONDEFINE 2
#define INVALID 3
#define NOTFOUND 404

#define MAXSIZE 1000


List MakeEmpty(){
    List PtrL = (List) malloc (sizeof(List));
    PtrL->Next = NULL;
    return PtrL;
}

List FindKth(int K, List PtrL){
    List p = PtrL;
    if(K < 1){
        printf("Operation Failed!\nError Code %02x\n",INVALID);
        return NULL;
    }
    int i = 1 ;
    for(; K > i && p != NULL ; p = p->Next, i++);
    if(i == K){
        return p;
    }
    else{
        return NULL;
    }
}

List Insert(char *id, char *password, QString UserName, int i,List PtrL){
    List p,s;
    if(i == 1){
        s = (List) malloc(sizeof(struct LNode));
//        s->num = X;
        strncpy(PtrL->id,id,strlen(id));
        strncpy(PtrL->password,password,strlen(password));
        PtrL->Username = UserName;
        s->Next = PtrL;
        return s;
    }
    p = FindKth(i - 1,PtrL);
    if(p == NULL){
        printf("Operation Failed!\nError Code %02x\n",INVALID);
        return NULL;
    }
    else{
        s = (List) malloc(sizeof(struct LNode));
        strncpy(PtrL->id,id,strlen(id));
        strncpy(PtrL->password,password,strlen(password));
        PtrL->Username = UserName;
        s->Next = p->Next;
        p->Next = s;
        return PtrL;
    }
}

List Delete(int i, List PtrL){
    List p,s;
    if(i < 1){
        printf("Operation Failed!\nError Code %02x\n",INVALID);
        return NULL;
    }
    if(i == 1){
        s = PtrL;
        if(PtrL != NULL)
            PtrL = PtrL->Next;
        else
            return NULL;
        free(s);
        return PtrL;
    }
    p = FindKth(i-1,PtrL);
    if(p == NULL){
        printf("Operation Failed!\nError Code 1%02x\n",INVALID);
        return NULL;
    }
    else if(p->Next == NULL){
        printf("Operation Failed!\nError Code 2%02x\n",INVALID);
        return NULL;;
    }
    else{
        s = p->Next;
        p->Next = s->Next;
        free(s);
        return PtrL;
    }
}

int Length(List PtrL){
    List p = PtrL;
    int i = 0;
    if(PtrL == NULL){
        return i;
    }
    for(; p != NULL ; i++, p = p->Next);
    return i;
}

void ShowList(List L){
    List PtrL = L;
    for(int i = 1 ; PtrL->Next != NULL ; i++){
        printf("%dL  id = %s\t pwd = %s",i,PtrL->id,PtrL->password);
        PtrL = PtrL->Next;
    }
}

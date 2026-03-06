#ifndef DEF_H
#define DEF_H
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MaxLength 1000
#define RandN 5

typedef int ElemType;
typedef int status;

typedef struct ClsNode // 将子句表示为由文字构成的链表
{
    ElemType words;
    struct ClsNode *pnext;
} ClsNode, *ClsNodes;
typedef struct ClsList
{
    ClsNode *phead;
    struct ClsList *pnext;
} ClsList, *ClsLists;


#endif

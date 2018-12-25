#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define true 1
#define false 0
#define MALLOC(x,y) ((x *)malloc(sizeof(x)*y))


// this code is copy from the thompson.c 
typedef struct nfa
{
    struct nfa ***next;
    int set[63];
    _Bool accept;
    int mark;
}nfa;
typedef struct nfaBlock{
    nfa *first,*last;
    int strP;
}nfaBlock;
extern nfaBlock *buildNfa(char *re);

// ---------------------------------------
typedef struct dfa
{
    struct dfa ***next;
    int set[62];
    _Bool accept;
    int mark;
}dfa;

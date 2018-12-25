#include "complite.h"


static _Bool isAlpha(char c);
static nfaBlock *singleRe(char re,int strP);
static nfaBlock *leftOrRightRe(char *re);
static int trueStrlen(char *s);
static int charToIndex(char c);
static nfa *newNfa(void);
nfaBlock *buildNfa(char *re);

static nfa *newNfa(void)
{
    static int number = 0;
    nfa *new = MALLOC(nfa,1);
    new->next = MALLOC(nfa **,63);
    new->accept = false;
    for (int i = 0 ; i < 63 ; i ++){
        new->set[i] = 0;
        new->next[i] = MALLOC(nfa *,20); 
    }
    new->mark = number;
    number += 1;
    return new;
}
static int trueStrlen(char *s)
{
    int len = strlen(s);
    int life = 0;
    for(int i = 0 ; i < len ; i ++)
    {
        if(s[i] == '('){
            life += 1;
        }
        else if(s[i] == ')'){
            life -= 1;
        }
        if(life < 0){
            return i;
        }
    }
    return len;
}
static int charToIndex(char c)
{
    if(c >= 'a' && c <= 'z'){
        return c - 'a';
    }
    else if (c >= 'A' && c <= 'Z'){
        return c - 'A' + 26;
    }
    else if (c >= '0' && c <= '9'){
        return c - '0' + 52;
    }
    else {
        return -1;
    }
}
static _Bool isAlpha(char c)
{
    if(c >= 'a' && c <= 'z'){
        return true;
    }
    else if (c >= 'A' && c <= 'Z'){
        return true;
    }
    else if (c >= '0' && c <= '9'){
        return true;
    }
    else {
        return false;
    }
}
static nfaBlock *singleRe(char re,int strP)
{
    nfa *a = newNfa(),*b = newNfa();
    nfaBlock *feed = MALLOC(nfaBlock,1);
    a->next[charToIndex(re)][a->set[charToIndex(re)]] = b;
    a->set[charToIndex(re)] += 1;
    a->accept = false;
    b->accept = true;
        
    feed->first = a;
    feed->last = b;
    feed->strP = strP;
    return feed;
}

static nfaBlock *leftOrRightRe(char *re)
{
    int strP = 0;
    nfaBlock *this;
    if(re[0] == '(')
    {
        this = buildNfa(re + 1);
        this->strP += 2;
        strP = this->strP + 1;
    }
    else if (isAlpha(re[0]) == true){
        this = singleRe(re[0],0);
        strP = 1;
    }
    if (strP < trueStrlen(re) && re[strP] == '*'){
        nfa *first = this->first,*last = this->last;
        nfa *newFirst = newNfa(),*newLast = newNfa();
        
        last->next[62][last->set[62]] = first;
        last->set[62] += 1;
        newFirst->next[62][newFirst->set[62]] = first;
        newFirst->set[62] += 1;
        last->next[62][last->set[62]] = newLast;
        last->set[62] += 1;
        newFirst->next[62][newFirst->set[62]] = newLast;
        newFirst->set[62] += 1;
        last->accept = false;
        newLast->accept = true;

        this = MALLOC(nfaBlock,1);

        this->first = newFirst;
        this->last = newLast;
        this->strP = strP;
    }
    else {
        return this;
    }
}
nfaBlock *buildNfa(char *re)
{
    int strP = 0;
    if(trueStrlen(re) == 1){
        return singleRe(re[0],0);
    }
    else {
        nfaBlock *left = leftOrRightRe(re);
        nfaBlock *right = NULL;
        nfaBlock *both = NULL;
        strP = left->strP + 1;
        
        if(strP < trueStrlen(re))
        {
            if(re[strP] == '|')
            {
                right = buildNfa(re + strP + 1);
                nfa *bothFirst = newNfa() , *bothLast = newNfa();
                nfaBlock *both = MALLOC(nfaBlock,1);
                bothFirst->next[62][bothFirst->set[62]] = left->first;
                bothFirst->set[62] += 1;
                bothFirst->next[62][bothFirst->set[62]] = right->first;
                bothFirst->set[62] += 1;
                left->last->next[62][left->last->set[62]] = bothLast;
                left->last->set[62] += 1;
                right->last->next[62][right->last->set[62]] = bothLast;
                right->last->set[62] += 1;
                left->last->accept = right->last->accept = false;
                both->first = bothFirst;
                both->last = bothLast;
                both->first->accept = false;
                both->last->accept = true;
                both->strP = strP + right->strP + 1;
                return both;
            }
            else
            {
                both = MALLOC(nfaBlock,1);

                right = buildNfa(re + strP);
                left->last->next[62][left->last->set[62]] = right->first;
                left->last->set[62] += 1;
                left->last->accept = false;
                right->last->accept = true;
                both->first = left->first;
                both->last = right->last;
                both->strP = strP + right->strP;
                return both;
            }
        }
        else {
            return left;
        }
    }
}

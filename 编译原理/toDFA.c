#include "complite.h"


struct dfaNode
{
    struct nfa **nfa;
    dfa *dfa;
    int len;
}**Qlist;
int QlistLen = 0;
struct dfaNode **workList;
int workListLen;
int top = 0,tail = 0;
void init(int QLen,int workLen)
{
    Qlist = MALLOC(struct dfaNode *,QLen);
    for(int i = 0 ; i < QLen ; i ++){
        Qlist[i] = MALLOC(struct dfaNode,1);
    }
    workList = MALLOC(struct dfaNode *,workLen);
    workListLen = workLen; 
}
void swap(nfa **a,nfa **b)
{
    nfa *temp = *a;
    *a = *b;
    *b = temp;
    return ;
}
void quickSort(nfa **marks,int len)
{
    if (len <= 1){
        return ;
    }
    int last = marks[len - 1]->mark;
    int i = -1,j = 0;

    while(j < len - 1)
    {
        if(last > marks[j]->mark)
        {
            i += 1;
            swap(marks + j,marks + i);
        }
        j += 1;
    }
    i += 1;
    swap(marks + len - 1 ,marks + i);
    quickSort(marks,i);
    quickSort(marks + i + 1,len - i - 1);
    return ;
}
void epsClosure(nfa *node,struct nfa **output,int *returnSize)
{
    int thisIndex = *returnSize;
    int temp = node->mark;
    output[thisIndex] = node;
    (*returnSize) += 1;
    node->mark = -1;
    for(int i = 0 ; i < node->set[62] ; i ++)
    {
        if (node->next[62][i]->mark >= 0){
            epsClosure(node->next[62][i],output,returnSize);
        }
    }
    node->mark = temp;
    return ;
}
void epsClosures(struct dfaNode *node,nfa **output,int *returnSize)
{
    for (int i = 0 ; i < node->len ; i ++)
    {
        int size = 0;
        epsClosure(node->nfa[i],output+(*returnSize),&size);
        (*returnSize) += size;
    }
    quickSort(output,*returnSize);
    return ;
}
static dfa *newDfa(void)
{
    static int number = 0;
    dfa *new = MALLOC(dfa,1);
    new->next = MALLOC(dfa **,62);
    new->accept = false;
    for (int i = 0 ; i < 62 ; i ++){
        new->set[i] = 0;
        new->next[i] = MALLOC(dfa *,20); 
    }
    new->mark = number;
    number += 1;
    return new;
}
int joinToQList(nfa **nfa,int len)
{
    static int index = 0;
    Qlist[QlistLen]->nfa = nfa;
    Qlist[QlistLen]->dfa = newDfa();
    Qlist[QlistLen]->len = len;
    
    for(int i = 0 ; i < len ; i ++)
    {
        if(nfa[i]->accept == true){
            Qlist[QlistLen]->dfa->accept = true;
            QlistLen += 1;
            return QlistLen - 1;
        }
    }
    QlistLen += 1;
    return QlistLen - 1;
}
void joinToWorkList(struct dfaNode *dfaNode)
{
    top = (top + 1)%workListLen;
    workList[top] = dfaNode;
    return ;
}
struct dfaNode *popWorkList(void)
{
    tail = (tail + 1)%workListLen;
    return workList[tail];
}
struct dfaNode *nextC(struct dfaNode *Q,int c)
{

    struct dfaNode *feed = MALLOC(struct dfaNode,100);
    feed->nfa = MALLOC(nfa *,100);
    int size = 0;
    for (int i = 0 ; i < Q->len ; i ++)
    {
        for(int j = 0 ; j < Q->nfa[i]->set[c] ; j ++)
        {
            feed->nfa[size] = Q->nfa[i]->next[c][j];
            size += 1;
        }
    }
    feed->len = size;
    return feed;
}
_Bool same(nfa **a,int Alen,nfa **b,int Blen)
{
    if (Alen != Blen){
        return false;
    }
    for (int i = 0 ; i < Alen ; i ++)
    {
        if(a[i]->mark != b[i]->mark){
            return false;
        }
    }
    return true;
}
int isInQList(nfa **Nfa,int len)
{
    for (int i = 0 ; i < QlistLen ; i ++)
    {
        if(same(Nfa,len,Qlist[i]->nfa,Qlist[i]->len)){
            return i;
        }
    }
    return -1;
}
void joinD(struct dfaNode *thisWork,int join,int c)
{
    thisWork->dfa->next[c][thisWork->dfa->set[c]] = Qlist[join]->dfa;
    thisWork->dfa->set[c] += 1;
    return ;
}
dfa *nfaToDFA(nfa *Nfa)
{
    int q0Len = 0;
    struct nfa **q0 = MALLOC(struct nfa *,100);
    epsClosure(Nfa,q0,&q0Len);
    quickSort(q0,q0Len);
    joinToWorkList(Qlist[joinToQList(q0,q0Len)]);
    while(tail < top)
    {
        struct dfaNode *thisWork = popWorkList();
        for(int c = 0 ; c < 62 ; c ++)
        {
            int *qn = MALLOC(int,100);
            int size = 0;
            int sameIndex = 0;
            nfa **t = MALLOC(nfa *,100);
            epsClosures(nextC(thisWork,c),t,&size);
            if(size > 0)
            {
                if((sameIndex = isInQList(t,size)) < 0)
                {
                    int join;
                    joinToWorkList(Qlist[join = joinToQList(t,size)]);
                    joinD(thisWork,join,c);
                }
                else {
                    joinD(thisWork,sameIndex,c);
                }
            }
        }
    }
    return Qlist[0]->dfa;
}
int main ()
{
    char *s = MALLOC(char,100);
    nfaBlock *p;
    dfa *q;
    init(200,200);
    scanf("%s",s);
    p = buildNfa(s);
    q = nfaToDFA(p->first);
    printf("done!");
}
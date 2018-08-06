#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
#define FLAGS O_WRONLY | O_CREAT | O_TRUNC  
#define MODE S_IRWXU 
#define NEW(x,y) ((x *)malloc(sizeof(x)*y))
typedef struct words
{
    char word[15];
    double efactor;
    int retime;
    long long nextPlaytime;
}Words;
int wordslen = 0;
double computingEF(int quality,double efactor)
{
    efactor = efactor + (0.1 - (5 - quality)*(0.08 + (5 - quality)*0.02));
    if(efactor < 1.3){
        efactor = 1.3;
    }
    return efactor;
}
int nextStudyDay(int replayTime,int efactor)
{
    if(replayTime == 1){
        return 1;
    }
    else if(replayTime == 2){
        return 6;
    }
    else if(replayTime > 2) 
    {
        return nextStudyDay(replayTime - 1,efactor)*efactor;
    }
}
Words *loadWordsFile(void)
{
    int wordsFile = open(".\\words.txt",O_RDWR);
    Words *words;

    if(read(wordsFile,&wordslen,sizeof(int)) == -1){
        return NULL;
    }
    words = NEW(Words,1000);
    read(wordsFile,words,sizeof(Words)*wordslen);
    return words;
}
Words *inputWords(void)
{
    Words *words = NEW(Words,1000);
    time_t thisTime;
    time(&thisTime);
    thisTime = thisTime/60/60/24;
    printf("please input many words.first input the words lenght,then input all words :)\n");
    scanf("%d",&wordslen);
    for(int i = 0 ; i < wordslen ; i ++)
    {
        scanf("%s",words[i].word);
        words[i].efactor = 2.5;
        words[i].nextPlaytime = thisTime;
        words[i].retime = 0;
    }
    return words;
}
void outWordsToFile(Words *words)
{
    int wordsFile = open(".\\words.txt",O_RDWR);
    if(wordsFile == -1){
        open(".\\words.txt", FLAGS, MODE);
        wordsFile = open(".\\words.txt",O_RDWR);
    }
    write(wordsFile,&wordslen,sizeof(int));
    write(wordsFile,words,sizeof(Words)*wordslen);
}
void push(Words *(stack[1000]),Words *word,int *top)
{
    *top = (*top + 1) % 1000;
    stack[*top] = word;
}
Words *pop(Words *(stack[1000]),int *tail)
{
    *tail = (*tail + 1) % 1000;
    return stack[*tail];
}
void studyBegin(Words *words)
{
    time_t thisTime;
    Words *(stack[1000]);
    time(&thisTime);
    thisTime = thisTime/60/60/24;

    int top = 0,tail = 0;
    for(int i = 0 ; i < wordslen ; i ++) //loading
    {
        if (words[i].nextPlaytime <= thisTime){
            push(stack,words + i,&top);
        }
    }
    printf("Now all ready,let us begin !\n");
    while(top != tail)
    {
        int quality;
        Words *this = pop(stack,&tail);
        printf("Do you memory word: %s ? please input a number represent you memory!\n%f,%d\n",this->word,this->efactor,this->nextPlaytime);
        scanf("%d",&quality);
        this->efactor = computingEF(quality,this->efactor);
        this->retime += 1;
        this->nextPlaytime = thisTime + (long long)nextStudyDay(this->retime,this->efactor);
    }
}
int main ()
{
    Words *words;
    int select;
    words = loadWordsFile();
    if(words == NULL)
    {
        printf("File no words!");
        words = inputWords();
        outWordsToFile(words);
    }
    studyBegin(words);
    outWordsToFile(words);
}
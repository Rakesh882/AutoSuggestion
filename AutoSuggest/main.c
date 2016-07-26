#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#define ALPHABET_SIZE 26
typedef struct node Node;
struct node
{
    bool isEOF;
    Node* next[ALPHABET_SIZE];
};
Node* createNode()
{
    Node* newNode=malloc(sizeof(Node));
    newNode->isEOF=false;
    int i;
    for(i=0; i<ALPHABET_SIZE; i++)
        newNode->next[i]=NULL;
    return newNode;
}
Node *root;
void insertWord(char *word)
{
    Node* temp=root;
    int i=0;
    while(word[i]!='\0')
    {
        if(temp->next[word[i]-'a']==NULL)
            temp->next[word[i]-'a']=createNode();
        temp=temp->next[word[i]-'a'];
        i++;
    }
    temp->isEOF=true;
}
bool hasWord(char *word)
{
    Node*temp=root;
    int i=0;
    while(word[i]!='\0')
    {
        if(temp->next[word[i]-'a']==NULL)
            return false;
        temp=temp->next[word[i]-'a'];
        i++;
    }
    return temp->isEOF;
}
void printWords(Node* root1,char* prefix)
{
    if(root1->isEOF)
    {
        //Sleep(500);
        printf("\n%s",prefix);
    }

    int i;
    for(i=0; i<ALPHABET_SIZE; i++)
    {
        if(!root1->next[i]) continue;
        int len=strlen(prefix);
        char* newPrefix=malloc(len+2);
        strcpy(newPrefix,prefix);
        newPrefix[len]=i+'a';
        newPrefix[len+1]='\0';
        printWords(root1->next[i],newPrefix);
    }
}
int main()
{
    char arr[200];
    root=createNode();
    FILE *fp=fopen("dictionary.txt","r");
    if(fp==NULL)
    {
        printf("FILE NOT FOUND");
        return 0;
    }
    while(!feof(fp))
    {
        fscanf(fp,"%s",arr);
        insertWord(arr);
    }
    printf("Enter a word to suggest: ");
    scanf("%s",arr);
    int i=0,j=0;
    Node* root1=root;
    while(arr[i]){
        if(!root1->next[arr[i]-'a'])
        {
            j=1;break;
        }
        root1=root1->next[arr[i]-'a'];
    }
    printWords(root1,arr);
    fclose(fp);
    return 0;
}

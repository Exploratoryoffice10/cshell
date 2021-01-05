#include "headers.h"
//#include "splitinp.h"
//#include "cominterp.h"

//char *bu[1000];

void split_inp(char* buff)
{

    int n=1;
    if(buff==NULL)
    {
        return;
    } 
    char **bu;
    bu=(char**)malloc(sizeof(char*)*1000);  
    bu[0]=strtok(buff,";\n");
    while((bu[n]=strtok(NULL,";\n"))!=NULL)
    {
        n++;
    }
    
    for (int i = 0; i < n; i++)
    {
        commandaction(bu[i]);
    }
}
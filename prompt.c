#include "headers.h"


void printname()
{
    yellow();
    printf("<%s@%s:",usn,hsn);
    int x1,b=0;
    if(strcmp(pcudr,cudr)==0)
    {
        printf("~>");
        reset();
        return;
    }
    
    if(strlen(cudr)>=strlen(pcudr))
    {   
        int z=0,p=strlen(pcudr);
        for (int i=0;i<p;++i)
        {                                     
            if(cudr[i]==pcudr[i])
            {
                z++;
            }
        }
        if(z!=p)
        {
            printf("%s>",cudr);
        }
        else
        {
            printf("~");
            for (int j=p;j<strlen(cudr);j++)
            {
               printf("%c",cudr[j]); 
            }
            printf(">");
        }
    }
    else
    {
        printf("%s>",cudr);
    }
    reset();
    
}

void prompt()
{
    int glbr;
    printname();
    buf=NULL;
    while(1)
    {
        glbr=getline(&buf,&bf,stdin); 
        if(glbr==-1)
        {
            overkill(1);
            printf("\nbye bye\n");
            break;
        }
        split_inp(buf); 
        printname();
    }
}


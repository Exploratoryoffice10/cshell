#include "headers.h"

void fpinfo(char ** pinp,int cyt){
    int idpsd=getpid();
    if(cyt>1)
    {
        idpsd=atoi(pinp[1]);;
    }

    printf("pid -- %d\n",idpsd);
    char arr1[4096];    
    char arr2[4096];
    sprintf(arr1,"/proc/%d/status",idpsd);
    int fd1=open(arr1,O_RDONLY);
    if(fd1==-1)
    {
        perror("unable to open proc/pid dir ");
        return;
    }
    char *op[10000];    
    char ix[10500]; 
    int btr; 
    btr=read(fd1,ix,10050);   
    if(btr==-1)
    {
        perror("error ");
        return; 
    }

    int ki=0;
    op[ki]=strtok(ix," \t\n");
    ki++;
    while((op[ki]=strtok(NULL," \t\n"))!=NULL)
    {
        ki++;
    }
    
    for(int i=0;i<ki;i++)
    {
        if(strcmp(op[i],"VmSize:")==0)
        {
            printf("Memory --- %s  {Virtual Memory}\n",op[i+1]);
            i++;
        }
        if(strcmp(op[i],"State:")==0){
            printf("Process Status -- %s\n",op[i+1]);
            i++; 
        }
    }

    sprintf(arr1,"/proc/%d/exe",idpsd);
    int che1=readlink(arr1,arr2,4096);
    if(che1!=-1)
    {
        int inar=strlen(arr2);
        arr2[inar]='\0';
        printf("Exectable path --- %s\n",arr2);
    }
    else
    {
        perror("error: ");
    }
}
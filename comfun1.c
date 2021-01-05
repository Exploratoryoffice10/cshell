#include "headers.h"
 
void fecho(char** pinp,int x)
{
    int y;
    for (int i=1;pinp[i]!=NULL;++i)
    {
        if(pinp[i][0]!='$'){
            printf("%s ",pinp[i]);
        }
        else    // env variable
        {
            char *pt1,*pt2;
            pt2=(char *)malloc(sizeof(char)*strlen(pinp[i]));  
            for(int j=1;j<strlen(pinp[i]);j++)
            {
                pt2[j-1] = pinp[i][j];
            }
            pt2[strlen(pinp[i])-1]='\0';
            pt1=getenv(pt2);
            free(pt2);
            if(pt1!=NULL)
            {
                printf("%s ",pt1);
            }
        }
    }
    printf("\n");
}

// function for cd
void fcd(char** pinp,int x)
{   
    if(x>2)
    {
        printf("multiple arguments for cd try giving one argument\n");
        return;
    }
    
    if(pinp[1]==NULL || strcmp(pinp[1],"~")==0)
    {
        chdir(pcudr);
        setenv("OLDPWD",cudr,1);
        getcwd(cudr,4096);
        return;
    }
    
    if(strcmp(pinp[1],"-")==0)
    {
        char *ppp= getenv("OLDPWD");
        chdir(ppp);
        setenv("OLDPWD",cudr,1);
        getcwd(cudr,4096);
        return;
    }
    if(strcmp(pinp[1],".")==0)
    {   
        setenv("OLDPWD",cudr,1);
        return;  
    }
    else if(strcmp(pinp[1],"..")==0)
    {
        int x;
        if(strcmp(cudr,"/")==0)
        {
            return;
        }

        char *predp;
        predp=(char*)malloc(((int)strlen(cudr)+2)*sizeof(char));
        
        for(int i=0;i<strlen(cudr);i++)
        {
            if(cudr[i]=='/')
            {
                x=i;
            }
        }
        if(x!=0)
        {
            for (int i = 0;i<x;i++)
            {
                predp[i]=cudr[i];    
            }
            predp[x]='\0';
        }
        else
        {
            predp[0]='/';
        }
        int chdch=chdir(predp);
        if(chdch==-1)
        {
            printf("failed to change directory\n");
            return;
        }
        setenv("OLDPWD",cudr,1);
        getcwd(cudr,4096);
        free(predp);
    } 
    else
    {
        int ddi;
        if(pinp[1][0]=='~')
        {
            int x=strlen(pcudr)+strlen(pinp[1])+2;
            char* ppp=(char*)malloc (x*sizeof(char));
            for(int i=0;i<strlen(pcudr);++i)
            {
                ppp[i]=pcudr[i];
            }
            for(int i=1;i<(int)strlen(pinp[1]);++i)
            {
                ppp[(int)strlen(pcudr)+i-1]=pinp[1][i];
            }
            int dd0=chdir(ppp);
            if(dd0==-1)
            {
                printf("No such directory\n");
            }
            else
            {
                setenv("OLDPWD",cudr,1);
                getcwd(cudr,4096);
            }
            free(ppp);
        }
        else
        {
            int dd0=chdir(pinp[1]);           
            if(dd0==-1)
            {
                printf("No such directory\n");
            }
            else
            {
                setenv("OLDPWD",cudr,1);
                getcwd(cudr,4096);
            }
        }
    }
}



void execexecp(char** pinp,int y)
{
    int x=fork();
    if(x==0)  //child
    {   
        int yyy=getpid();
        setpgid(yyy,yyy);
        signal(SIGTTIN,SIG_DFL);
        signal(SIGTTOU,SIG_DFL);
        signal(SIGSTOP,SIG_DFL);
        signal(SIGTSTP,SIG_DFL);
        signal(SIGINT,SIG_DFL);
        if(execvp(pinp[0],pinp)<0)
        {   
            perror("error here ");
            exit(1);
        }
    }
    else     // for parent
    {
        int s,wstat;    // y=0 => "&" not present at end of command
        if(y==0)        // Parent is waiting     
        {
            signal(SIGTSTP,SIG_IGN);
            signal(SIGINT,SIG_IGN);
            if(tcsetpgrp(STDERR_FILENO,x)==-1){
                perror("error si : ");
            }
            s=waitpid(x,&wstat,WUNTRACED);  // waiting for child process to finish
            if(tcsetpgrp(STDERR_FILENO,phgdt)==-1)
            {
                perror("error in changing");
                fprintf(stderr,"jfkds");
            }
            else
            {
                //fprintf(stderr,"success\n");
                //fprintf(stdout,"jifjdk");
            }
            if (WIFSTOPPED(wstat))
            {
                //printf("i am in\n");//signal(SIGINT,siginthandler1);//signal(SIGTSTP,sigstsphandler1);
                fgarr[fgind1].prid=x;
                int  uio=0;
                for(int zzo,iio=0;pinp[iio]!=NULL;iio++)
                {
                    for(zzo=0;zzo<strlen(pinp[iio]);zzo++)
                    {
                        fgarr[fgind1].com[uio]=pinp[iio][zzo];
                        uio++;
                    }
                    fgarr[fgind1].com[uio]=' ';
                    uio++;
                }
                fgarr[fgind1].com[uio]='\0';
                fgarr[fgind1].flag=1;   // for fg flag 1
                fgind1++;fgc1++;    
            }
            signal(SIGINT,siginthandler1);signal(SIGTSTP,sigstsphandler1);                     
        }
        else      // y=1 & is at last
        {

            fgarr[fgind1].prid=x; int uio=0;
            for(int zzo,iio=0;pinp[iio]!=NULL;iio++)
            {
                for(zzo=0;zzo<strlen(pinp[iio]);zzo++)
                {
                    fgarr[fgind1].com[uio]=pinp[iio][zzo];
                    uio++;
                }
                fgarr[fgind1].com[uio]=' ';
                    uio++;
            }
            fgarr[fgind1].com[uio]='\0';
            fgarr[fgind1].flag=2;   // for bg flag 2
            fgind1++;fgc1++;
        }
    }
}


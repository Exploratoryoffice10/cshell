#include "headers.h"

//char *ecbuf[1000];
//void othe(char * ecbufl,int y);

void runeachcommand(char** ecbu,int coun);



void commandaction(char * indip)    // indip is the string (the command after splitting ';' ) 
{
    int cou=0;
    if(indip==NULL)
    {
        return;
    }
    char **ecbuf;
    ecbuf=(char **)malloc(sizeof(char *) * 1000);
    cou=0;
    ecbuf[cou]=strtok(indip,delim);
    cou++;
    while((ecbuf[cou]=strtok(NULL,delim))!=NULL)    // semi-colon seperated commands each terms split into ecbuf
    {
        cou++;
    }

    int ipip=0,a11=0,a22=0,a33=0;
    
    for(int i=0;ecbuf[i]!=NULL;i++)
    {
        if(strcmp(ecbuf[i],"<")==0)
        {
            a11++;
        }
        if(strcmp(ecbuf[i],">")==0){
            a22++;
        }
        if (strcmp(ecbuf[i],">>")==0)
        {
            a33++;
        }
        if (strcmp(ecbuf[i],"|")==0)
        {
            ipip++;
        }   
    }
    
    if(ipip){
        piping(ecbuf,cou);
        return;
    }
    
    if(a11+a22+a33)
    {
        int res;
        res=redirect(ecbuf,cou);
        free(ecbuf);
        return;
    }

    runeachcommand(ecbuf,cou);
    
    free(ecbuf);
}


void runeachcommand(char** ecbu,int coun) 
{
    int y=0;
    
    if(strcmp(ecbu[coun-1],"&")==0)
    {
        y=1;
        ecbu[coun-1]=NULL;
    }
    if(strcmp(ecbu[0],"quit")==0)
    {
        quitfunc(coun);    
    }
    if(strcmp(ecbu[0],"echo")==0)
    {
        fecho(ecbu,coun);    
    }
    else if(strcmp(ecbu[0],"pwd")==0)
    {
        printf("%s\n",cudr);
    }
    else if (strcmp(ecbu[0],"cd")==0)
    {
        fcd(ecbu,coun);
    }
    else if (strcmp(ecbu[0],"pinfo")==0)
    {
        fpinfo(ecbu,coun);
    }
    else if (strcmp(ecbu[0],"ls")==0)
    {
        fls(ecbu,coun);
    }
    else if ((strcmp(ecbu[0],"setenv")==0) || (strcmp(ecbu[0],"unsetenv")==0))
    {
        setandunset(ecbu,coun);
    }
    else if (strcmp(ecbu[0],"jobs")==0)
    {
        jobsfunc(coun);  
    }
    else if (strcmp(ecbu[0],"overkill")==0)
    {
        overkill(coun);
    }
    else if (strcmp(ecbu[0],"kjob")==0)
    {
        kjob(ecbu,coun);
    }
    else if (strcmp(ecbu[0],"fg")==0)
    {
        foregroundproc(ecbu,coun);
        //printf("fg\n");
    }
    else if (strcmp(ecbu[0],"bg")==0)
    {
        //printf("bg\n");
        backgroundproc(ecbu,coun);
    }
    else
    {
        execexecp(ecbu,y);
    }
}


// setenv , unsetenv function
/*
    if(strcmp(ecbuf[0],"echo")==0)
    {
        fecho(ecbuf,cou);    
    }
    else if(strcmp(ecbuf[0],"pwd")==0)
    {
        printf("%s\n",cudr);
    }
    else if (strcmp(ecbuf[0],"cd")==0)
    {
        fcd(ecbuf,cou);
    }
    else if (strcmp(ecbuf[0],"pinfo")==0)
    {
        fpinfo(ecbuf,cou);
    }
    else if (strcmp(ecbuf[0],"ls")==0)
    {
        fls(ecbuf,cou);
    }
    else
    {
        execexecp(ecbuf,y);
    }
    */
    
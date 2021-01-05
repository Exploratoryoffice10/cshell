#include "headers.h"
//#include "comfun2.h"

// this file solely contains the function for ls
// only ls............................... 

void prifilper(struct stat ser)
{
    int x=ser.st_mode;
    S_ISDIR(x)?printf("d"):printf("-");
    (x & S_IRUSR)?printf("r"):printf("-");
    (x & S_IWUSR)?printf("w"):printf("-");
    (x & S_IXUSR)?printf("x"):printf("-");
    (x & S_IRGRP)?printf("r"):printf("-");
    (x & S_IWGRP)?printf("w"):printf("-");
    (x & S_IXGRP)?printf("x"):printf("-");
    (x & S_IROTH)?printf("r"):printf("-");
    (x & S_IWOTH)?printf("w"):printf("-");
    (x & S_IXOTH)?printf("x"):printf("-");

    struct passwd *p1,*p2;
    p1=getpwuid(ser.st_uid);
    p2=getpwuid(ser.st_gid);
    printf("  %10s %10s ",p1->pw_name,p2->pw_name);
    printf("%8ld ",ser.st_size);
    struct tm *tim;
    tim = localtime(&ser.st_mtime);  
    char pui[10];
    strftime(pui,sizeof(pui)," %b ", tim);
    printf("%4s",pui);
    printf(" %2d %2d:%2d ",(*tim).tm_mday,(*tim).tm_hour,(*tim).tm_min);
}


void gabspfd(char *opy,char* inp)
{
    if(strcmp(inp,".")==0)
    {
        int co1=strlen(cudr);
        for (int i=0;i<co1;i++)
        {
            opy[i]=cudr[i];
        }
        opy[co1]='\0';
        return;
    }

    if(inp[0]=='~')
    {
        for (int i = 0; i < (int)strlen(pcudr); i++)
        {
            opy[i]=pcudr[i];
        }
        for(int i=1;i<(int)strlen(inp);i++)
        {
            opy[(int)strlen(pcudr)+i-1]=inp[i];
        }
        opy[(int)(strlen(pcudr)+strlen(inp))-1]='\0';
        return;
    }

    if(strcmp(inp,"..")==0)
    {
        int x;
        if(strcmp(cudr,"/")==0)
        {
            opy[0]='/';opy[1]='\0';
            return;
        }
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
                opy[i]=cudr[i];    //printf("%c",cudr[i]);
            }
            opy[x]='\0';
        }
        else
        {
            opy[0]='/';opy[1]='\0';
        }
        return;
    }

    for (int i = 0; i <(int)strlen(inp); i++)
    {
        opy[i]=inp[i];
    }
    opy[(int)strlen(inp)]='\0';
}

void fls(char ** pinp,int x)
{   
    DIR* dir;struct dirent *sdr1; char* cpft;struct stat sts;
    int ca=0,cl=0,cc=0;
    for(int i=1;i<x;i++)
    {
        if(strcmp(pinp[i],"-l")==0){
            cl=1;
        }
        else if(strcmp(pinp[i],"-a")==0){
            ca=1;
        }
        else if(strcmp(pinp[i],"-la")==0 || strcmp(pinp[i],"-al")==0)
        {
            ca=1;cl=1;
        }
        else       
        {
            cc++;
        }
    }
    if(cc==0)
    {
        dir=opendir(cudr);
        if(cl==0)
        {
            while ((sdr1=readdir(dir))!=NULL)
            { 
                if(ca==1 || (sdr1->d_name)[0]!='.')
                {
                    printf("%s\n",sdr1->d_name);
                } 
            }    
        }
        else 
        {
            sdr1=readdir(dir);
            cpft=(char*)malloc((int)(5+sizeof(cudr)+256)*sizeof(char));
            while(sdr1!=NULL)
            {
                if(sdr1->d_name[0]!='.' || ca==1)
                {    
                    for (int i = 0; i < (int)strlen(cudr);i++)
                    {
                        cpft[i]=cudr[i];
                    }
                    cpft[(int)strlen(cudr)]='/';
                    for (int i = 0; i<(int)strlen(sdr1->d_name); i++)
                    {
                        cpft[1+i+(int)strlen(cudr)]=sdr1->d_name[i];
                    }
                    cpft[1+(int)strlen(sdr1->d_name)+strlen(cudr)]='\0';
                    if(stat(cpft,&sts)==0)
                    {
                        prifilper(sts);  //int x=sts.st_mode;    
                        printf(" %s\n",sdr1->d_name);
                    }
                    else
                    {
                        printf("%s is the path for %s for you got ",cpft,sdr1->d_name);
                        free(cpft);
                        perror("stat error");
                        return;               
                    }
                }
                sdr1=readdir(dir);
            }
            free(cpft);
        }
        closedir(dir);
        return; /// till here when no arguments are passed to print local directory.
    }
    
    char* zio;
    zio=(char*)malloc((2500)*sizeof(char));
    cpft=(char*) malloc(2200*sizeof(char));
    for(int e3i=1;e3i<x;e3i++)
    {    
        if(pinp[e3i][0]!='-')
        {   
            gabspfd(cpft,pinp[e3i]);
            if(cc>1)
            {
                printf("%s :\n",cpft);
            }

            dir = opendir(cpft);
            if(dir==NULL)
            {
                printf("%s no such file or directory\n",pinp[e3i]); 
                continue;
            }
            else
            {
                if(cl==0)
                {
                    while ((sdr1=readdir(dir))!=NULL)
                    { 
                        if(ca==1 || (sdr1->d_name)[0]!='.')
                        {
                            printf("%s\n",sdr1->d_name);
                        } 
                    }    
                }    
                else
                {
                    sdr1=readdir(dir);
                    while(sdr1!=NULL)
                    {
                        if(sdr1->d_name[0]!='.' || ca==1)
                        {    
                            for (int i=0;i<(int)strlen(cpft);i++)
                            {
                                zio[i]=cpft[i];
                            }
                            zio[(int)strlen(cpft)]='/';
                            for (int i = 0; i<(int)strlen(sdr1->d_name); i++)
                            {
                                zio[1+i+(int)strlen(cpft)]=sdr1->d_name[i];
                            }
                            zio[1+(int)strlen(sdr1->d_name)+strlen(cpft)]='\0';
                            if(stat(zio,&sts)==0)
                            {
                                prifilper(sts);  //int x=sts.st_mode;    
                                printf(" %s\n",sdr1->d_name);
                            }
                            else
                            {
                                printf("%s is the path for %s for you got",zio,sdr1->d_name);
                                free(cpft);
                                perror("stat error");
                                return;               
                            }

                        }   
                        sdr1=readdir(dir);
                    }
                }   
            }
            closedir(dir);
            if (cc>1)
            {
                printf("\n");            
            }
        } 
    }
    free(zio);free(cpft);
}


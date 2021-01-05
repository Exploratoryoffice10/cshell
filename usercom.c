#include "headers.h"

int prijob(struct foreground fga,int p1);

void kill1job(struct foreground fga);

void setandunset(char **argsi,int co)
{
	if(co==3)
	{
		if(strcmp(argsi[0],"setenv")==0)
		{
			if(setenv(argsi[1],argsi[2],1)!=0)
			{
				perror("error: ");
			}
		}
		else
		{
			printf("error in number of arguments passed wrong command\n");
		}
	}
	else if(co==2)
	{
		if(strcmp(argsi[0],"unsetenv")==0)
		{
			if(unsetenv(argsi[1])!=0)
			{
				perror("error: ");
			}
		}
		else
		{
			printf("error in number of arguments passed wrong command\n");
		}
	}
	else
	{
		printf("error in number of arguments passed wrong command\n");
	}
}


void jobsfunc(int cou)
{
	int ppt=0;
	if(cou==1)
	{
		for(int i=0;i<fgind1;i++)
		{
			ppt+=prijob(fgarr[i],i+1);	
		}
		if(ppt==0)
		{
			fgc1=0;fgind1=0;
		}
	}
	else
	{
		printf("jobs has no arguments\n");
	}
}

int prijob(struct foreground fga,int p1)
{
	char arr1[4096];    
    sprintf(arr1,"/proc/%d/status",fga.prid);
    int fd1=open(arr1,O_RDONLY);
    
	if(fd1==-1)
    {
        // process is killed
        return 0;
    }

    char *op[10000];    
    char ix[10500]; 
    int btr; 
    btr=read(fd1,ix,10050);   
    if(btr==-1)
    {
        perror("error ");
        return 0; 
    }

    int ki=0;
    op[ki]=strtok(ix,delim);
    ki++;
    while((op[ki]=strtok(NULL,delim))!=NULL)
    {
        ki++;
    }	
	// ki is the total no of parts in the file
    for(int i=0;i<ki;i++)
    {
        if(strcmp(op[i],"State:")==0)
		{
			if(0==strcmp(op[i+1],"T"))
			{
				printf("[%d] Stopped     %s  [%d]\n",p1,fga.com,fga.prid);
				return 1;
			}
			else if(0==strcmp(op[i+1],"R"))
			{
				printf("[%d] Running     %s  [%d]\n",p1,fga.com,fga.prid);
				return 1;
			}
			else if(0==strcmp(op[i+1],"S"))
			{
				printf("[%d] Sleeping    %s  [%d]\n",p1,fga.com,fga.prid);
				return 1;
			}
			return 0;
        }
    }
}


void kjob(char ** argsi,int cou)
{
	if(cou==3)
	{
		int sinum=atoi(argsi[2]);
		int indec=atoi(argsi[1])-1;
		if(indec<fgind1)
		{
			int pno=fgarr[indec].prid;
			if(kill(pno,sinum)!=0)
			{
				perror("error: ");
				printf("couldnt kill the required process\n");	
			}
		}
		else
		{
			printf("check the index\n");	
		}
	}
	else 
		printf("check the number of arguments\n");
}

void overkill(int cou)
{
	if(cou==1)
	{
		for (int i = 0; i<fgind1; i++)
		{
			kill(fgarr[i].prid,SIGKILL);
		}
		fgind1=0;fgc1=0;
	}
	else
	{
		printf("no arguments should be passed\n");
	}
}

void quitfunc(int cou)
{
	if(cou==1)
	{
		overkill(1);
		printf("bye bye\n");
		exit(0);
	}
	else
	{
		printf("NO ARGUMENTS MUST BE PASSED\n");
	}
}


void foregroundproc(char ** argsi,int cou)
{
	signal(SIGINT,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);
	if(cou==2)
	{
		int ind=atoi(argsi[1])-1;
		if(ind<fgind1)
		{	
			int procid = fgarr[ind].prid;
			fgarr[ind].flag=1;
			tcsetpgrp(STDERR_FILENO,procid);
			if(kill(fgarr[ind].prid,SIGCONT)==0)
			{
				int wstatus;
				printf("continued     %s   [%d]\n",fgarr[ind].com,fgarr[ind].prid);
				waitpid(fgarr[ind].prid,&wstatus,WUNTRACED);
				tcsetpgrp(STDERR_FILENO,phgdt);
			}
			else
			{
				perror("error: ");	
			}
		}
		else
		{
			printf("wrong index\n"); 
		}
	}
	else
	{
		printf("pass correct number of arguments\n ");
	}
	signal(SIGINT,siginthandler1);
	signal(SIGTSTP,sigstsphandler1);
}




void backgroundproc(char ** argsi,int cou)
{
	if(cou==2)
	{
		int ind = atoi(argsi[1])-1;
		fgarr[ind].flag==2;
		if(ind<fgind1)
		{
			kill(fgarr[ind].prid,SIGCONT);
		}
		else
		{
			printf("no job exists with that index\n");
		}
	}
	else
	{
		printf("check the no.of arguments passed\n ");
	}
}


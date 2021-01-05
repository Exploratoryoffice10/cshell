#include "headers.h"

int redirect(char ** argsi,int co)
{
    int oristdin=dup(0);
    int oristdout=dup(1);
    int rv=0;
    int a11=0,a22=0,a33=0;
    int a1x=-1,a1y=-1,a1z=-1;
    for(int i=0;argsi[i]!=NULL;i++)
    {   
        if(strcmp(argsi[i],"<")==0){
            a11++;a1x=i;
        }
        if(strcmp(argsi[i],">")==0){
            a22++;a1y=i;
        }
        if (strcmp(argsi[i],">>")==0)
        {
            a33++;a1z=i;
        } 
    }
    char inp[4000],outp[4000];
    int x=1010111;
    if(a11==1)
    {
        strcpy(inp,argsi[a1x+1]);
        if(x>a1x)
        {
            x=a1x;
        }
    }
    if(a22==1)
    {
        strcpy(outp,argsi[a1y+1]);
        if(x>a1y)
        {
            x=a1y;
        }
    }
    if (a33==1)
    {
        strcpy(outp,argsi[a1z+1]);  
        if(x>a1z)
        {
            x=a1z;
        }
    }
    char *z;int chk=1;
    int fid=-2,fout=-2;
    if(a11)
    {

        fid=open(inp,O_RDONLY);
        if(fid==-1)
        {
            rv=1;
            perror("stopped.. input file problem: ");
            return rv;    // error no input file stop command execution
        }
        else
        {
            //printf("hello lets print the file name the input name is %s\n",inp);
            dup2(fid,0);
            close(fid);
        }
    }
    if(chk==1)
    {
        if(a22)
        {   
            rv=1;
            fout=open(outp,O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if(fout==-1)
            {
                perror("output file problem: ");
                return rv; // stop execution
            }
            else
            {
                dup2(fout,1);
                close(fout);
            }
            
        }
        if(a33)
        {
            fout=open(outp,O_CREAT | O_WRONLY | O_APPEND, 0644);
            if(fout==-1)
            {
                rv=1;
                perror("output file problem: ");
                return rv; // stop execution
            }
            else
            {
                dup2(fout,1);
                close(fout); // out assigned to 1 no problem
            }   
        }
    }

    //printf("x is %d .",x);
    //argsi[x]=NULL;    all set everything is fine
    for (int i=x;i<co;i++)
    {
        argsi[i]=NULL;
    }

    int fx=fork();
    if(fx==-1)
    {
        perror("fork error ");
        return 1;
    }
    if(fx==0){
        if(execvp(argsi[0],argsi)==-1)
        {
            perror("execvp error: ");
            exit(1);
        }
    }
    else
    {
        waitpid(0,NULL,0);
        //fprintf(stderr,"this is a serious problem\n");
        dup2(oristdin,0);    // before next command 1 ,0 should point to stdin and stdout file
        dup2(oristdout,1);   //
        close(oristdin);close(oristdout);
        return rv;
    }
}
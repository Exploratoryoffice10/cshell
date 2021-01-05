#include "headers.h"

void yellow(){
    printf("\033[01;33m");
}

void reset(){
    printf("\033[0m");
}


void sigchildhandler(int sig)
{
    int wstatus,p=0;
    int i=0,x=waitpid(-1,&wstatus,WNOHANG);     // x is return pid
    for(i=0;i<fgind1;i++)
    {
        if(x==fgarr[i].prid)
        {
            p=1;
            break;
        }
    }
    if(p==1)
    {
        if(fgarr[i].flag==2)
        {    
            if (WIFEXITED(wstatus)) 
            {
                printf("\nthe bg process %s with pid %d exited normally\n", fgarr[i].com,fgarr[i].prid);
            }
            else
            {   
                printf("\nthe bg process %s with pid %d exited abnormally\n",fgarr[i].com,fgarr[i].prid);
            }
        }
        fgc1--;
        if(fgc1==0) 
            fgind1=0;
            printname();
        fflush(stdout);
    }
}


void siginthandler1(int sig)
{
    printf("\nctrl+C is pressed\n");
    printname();
    fflush(stdout); // stdout is newline buffered
}

void sigstsphandler1(int sig)   // sigstsp
{
    printf("\nctrl+Z is pressed\n");
    printname();
    fflush(stdout); // stdout is newline buffered
}   


int main()
{
    setpgid(getpid(),0);
    phgdt=getpgid(getpid());
    for(int i=0;i<1000;i++){
        fgarr[i].flag=0;
    }
    signal(SIGTTIN,SIG_IGN);
    signal(SIGTTOU,SIG_IGN);
    signal(SIGTSTP,sigstsphandler1);
    signal(SIGINT,siginthandler1);
    fgind1=0;fgc1=0;
    int sa=getlogin_r(usn,100),ha=gethostname(hsn,100);
    signal(SIGCHLD,sigchildhandler);
    getcwd(pcudr,4096);getcwd(cudr,4096);setenv("OLDPWD",cudr,1);
    prompt();
    return 0;
}


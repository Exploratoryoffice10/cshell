#include "headers.h"

void piping(char ** argsi,int co)
{
    int npipes=0,i,j;
    for (i = 0;argsi[i]!=NULL; i++)
    {
        if(strcmp(argsi[i],"|")==0){
            npipes++;
        }
    }
    //fprintf(stderr,"%d is no.of pipes",npipes);
    int fsin=dup(0),fsout=dup(1);
    int check=0,k,infd,outfd;
    char inf[4000],outf[4000];
    char *parcom[200];int fdp[npipes][2];
    i=0;j=0;    // used to parse the whole string
    while(check==0)
    {
        //fprintf(stderr,"now i is %d\n",i);
        k=0;
        while (strcmp(argsi[j],"|")!=0)   // when loop breaks j is pipe
        {
            parcom[k]=argsi[j];
            j++;k++;
            if(argsi[j]==NULL){
                check=1;
                break;
            }
        }
        
        parcom[k]=NULL; 
        j++;    // skipping pipe
        /*
        for (int asi = 0; parcom[asi]!=NULL; asi++)
        {
            fprintf(stderr,"%s dd i is %d dd ",parcom[asi],i);
        }
        */
        

        if(i==0)    // first one
        {
            //fprintf(stderr,"currently in %d th component\n",i);
            if(pipe(fdp[i])==-1)
            {
                perror("error in piping");
                dup2(fsin,0);dup2(fsout,1);
                return;
            } 
            //fprintf(stderr,"gg1\n");
            int pid=fork();
            if(pid==0)
            {                                   // no use of read end in pipe here only we are writing 
                //fprintf(stderr,"cugg2\n");
                close(fdp[i][0]);
                if(k>2)
                {
                    if(strcmp(parcom[k-2],"<")==0)
                    {
                        strcpy(inf,parcom[k-1]);
                        infd=open(inf,O_RDONLY);
                        if(infd==-1)
                        {
                            dup2(fsin,0);dup2(fsout,1);
                            perror("input file error:");
                            close(fdp[i][1]);   //closing open fd            
                            exit(1);
                        }
                        else
                        {
                            dup2(infd,0);     
                            parcom[k-2]=NULL;
                            parcom[k-1]=NULL;
                            close(infd);
                        }
                    }
                }

                dup2(fdp[i][1],1);
                close(fdp[i][1]);           // read and write closed in child process
                //dup2(fsout,1);
                //fprintf(stderr,"gg3\n");
                if(execvp(parcom[0],parcom)==-1)
                {
                    fprintf(stderr,"this is unacceptable titkdls");
                    dup2(fsin,0);dup2(fsout,1);
                    perror("error :");
                    exit(1);
                }
            }
            else
            {
                waitpid(pid,NULL,0);
                //fprintf(stderr,"gg 4\n");    
                close(fdp[i][1]);    // write end
            }
            /// close(fdp[i][0]);    
        }
        else if(i==npipes) // last one 
        {
            /*fprintf(stderr,"currently in %d th component\n",i);for (int kji = 0; parcom[kji]!=NULL; kji++)
            {fprintf(stderr,"%s ",parcom[kji]);}fprintf(stderr,"are the last %d commands\n",k);
            */
            int pid=fork();
            if(pid==0)
            {
                dup2(fsout,1);
                if(k>2)
                {

                    if(strcmp(parcom[k-2],">")==0)
                    {
                        /*for (int kji = 0; parcom[kji]!=NULL; kji++)
                        {
                            fprintf(stderr,"%s ",parcom[kji]);
                        }
                        fprintf(stderr,"are the last %d commands in the fork\n",k);
                        fprintf(stderr,"the name of file before copying to ouf is %s \n",parcom[k-1]);
                        */
                        strcpy(outf,parcom[k-1]);
                        //fprintf(stderr,"the name of the output file is %s\n",outf);
                        outfd=open(outf,O_CREAT | O_WRONLY | O_TRUNC,0644);
                        if(outfd==-1)
                        {
                            exit(1);
                        }   
                        //fprintf(stderr," id is %d business %s mn\n",outfd,parcom[k-1]);
                        parcom[k-1]=NULL;
                        parcom[k-2]=NULL;
                        dup2(outfd,1);
                        close(outfd); // closing out fd
                    }
                    else if(strcmp(parcom[k-2],">>")==0)
                    {
                        strcpy(outf,parcom[k-1]);
                        outfd=open(outf,O_CREAT | O_WRONLY | O_APPEND, 0644);
                        if(outfd==-1)
                        {
                            perror("output file :");
                            exit(1);
                        }
                        //set stdout
                        parcom[k-1]=NULL;
                        parcom[k-2]=NULL;
                        dup2(outfd,1);
                        close(outfd);    // closing outfd
                    }
                }
                dup2(fdp[i-1][0],0);
                close(fdp[i-1][0]);
                if(execvp(parcom[0],parcom)==-1)
                {
                    fprintf(stderr,"this is unacceptable titkdls");
                    dup2(fsin,0);dup2(fsout,1);
                    close(fsin);close(fsout);
                    perror("error :");
                    exit(1);
                }
            }
            else
            {
                waitpid(pid,NULL,0);
                close(fdp[i-1][0]);
            }
        }
        else                // middle one
        {
            //fprintf(stderr,"currently in %d th component",i);
            if(pipe(fdp[i])==-1)
            {
                perror("error in piping");
                return;
            }
            int pid=fork();
            if(pid==0)  // the fds open are previous pipes read and present pipe r and w
            {    
                
                dup2(fdp[i-1][0],0);
                dup2(fdp[i][1],1);
                close(fdp[i][0]);
                close(fdp[i][1]);
                close(fdp[i-1][0]);
                if(execvp(parcom[0],parcom)==-1)
                {
                    perror("error :");
                    dup2(fsin,0);dup2(fsout,1);  //reload original stdout stdin
                    return;
                }  
                // everything must be closed at last
            }
            else
            {
                waitpid(pid,NULL,0);
                close(fdp[i-1][0]);     // read input from the previous pipe job done in child
                close(fdp[i][1]);       // this pipe write end is now useless we need the read end so next fork can read it
            }                       
        }      
        i++;
        //fprintf(stderr,"going to next one %d \n",i);
        //break;
    }
    //finally bring the original stdin and stdout
    dup2(fsin,0);dup2(fsout,1);
    close(fsin);close(fsout);
    //printf("  done execution.coming out\n");
}
#ifndef HEADER_H
#define HEADER_H


#include <stdio.h>    
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stddef.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pwd.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>

#define delim " \t\n"
 
void yellow();

void reset();

size_t bf;

struct foreground{
    int prid;
    char com[1000];
    int flag;
};

int phgdt,fgc1,fgind1;  // keeping track of active process and index of latest process (created time)

struct foreground fgarr[4000];

char usn[100],hsn[100],pcudr[4096],cudr[4096],*buf;

void prompt();

void printname();

void fpinfo(char ** pinp,int cyt); // pinfo

void fecho(char** pinp,int x);

void fcd(char** pinp,int x);

void execexecp(char** pinp,int y);

void prifilper(struct stat ser);

void fls(char ** pinp,int x);

void gabspfd(char *opy,char* inp); //get abs path for dir

int redirect(char ** args,int co);

void piping(char ** argsi,int co);

void commandaction(char * indip);

void split_inp(char* buf);


//user defined commands

void setandunset(char **argsi,int cou);

void jobsfunc(int cou);

void foregroundproc(char ** argsi,int cou);

void backgroundproc(char ** argsi,int cou);

void kjob(char ** argsi,int cou);

void overkill(int cou);    // kills all background process at once (running)

void quitfunc(int cou);

//signal handlers

void sigchildhandler(int sig);

void siginthandler1(int sig);

void siginthandler2(int sig);

void sigstsphandler1(int sig);

#endif
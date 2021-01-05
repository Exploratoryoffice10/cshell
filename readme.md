The header files contains declarations of all functions,signal handlers ,
global variables. The files pipes.c contains the functions for implementation
of pipes. The files redirect.c contains the functions for implementation of  
input output redirection. The file usercom.c contains functions for user defined 
commands. all the signal handlers are defined in main.c

For implementation of input , output redirection c
ontaining one input and output file. we open the corresponding file and set 
the fd 0 points to the opening file and 1 points to the output file if they 
exist. by running the command using execvp. in a pipe we write at one end and 
we read at the other end. when there are n pipes in a command we need n pipes 
to process the command we split the command using '|'  and execute the each 
part using a fork. we need to set the input and output (fd 0 and 1).for the 
parts in between commands we read from a pipe in which the previous command 
writes and we write so that the next command reads from the pipe. only the 
first component can have a input file to read and last component can have a 
output file to write . 

for implementing usercommands setenv and unsetenv we use the system calls 
setenv and unsetenv to do so.generally environmental variables are inherited 
from the parent process.



NOTE: do not change the environmental variable 'OLDPWD'. I used this variable 
to keep track of the previous directory meddling with this can cause 
trouble.i used a string to store the current directory. in cd command before 
i update the current directory string for printing it in the prompt.before 
updating the string i push the value in it in OLDPWD	 .



For jobs i am using a array which store the process id and command executed.
a process is stopped when ctrl+z is pressed which sends the sigtstp signal to 
the process.when interrupt is send from keyboard it is also send to all its
child process. if we didn't write specific signal handlers this stops the 
shell process. So we write signal handlers to make sure we use the signals 
correctly to process some errors etc.

when a foreground process is stopped by a signal we store it in a array and 
we add the background process to the array when there are no running and 
stopped process in the process in the array we set the number of process is 
zero. for a background there shouldnt be any control to terminal. so we keep 
the background process in a new group (using setgpid -> used to shift process 
between groups). so it doesnt have any have control to terminal. for foreground 
process we shift the control to terminal between our shell and 
foregruond process. when fg process is stopped or exited we again give terminal
control to our shell process which can be obtained by tcserpgrp.
for overkill we send sigkill to all process which terminate.for overkill by 
taking the signal number process index we send the desired signal.before 
quitting the terminal all the background process are killed. even when EOF 
Charecter is recognised we kill all the process. while executing fg command 
if the given details are valid we send a sigcont signal we give the terminal
control to fg wait till it ends to snatch back the control.in bg we just send 
the sigcont signal. for bg we can send signal using kjob. 

----------------- info --------------------


        /\ Understand concepts /\
           -------------------
|-- Environment variables : are dynamic named values that affect how running processes behave on a computer. They are part of the environment in which a process runs and typically consist of a name=value pair. The most critical for program execution is PATH, which lists directories containing executable programs.

|-- Pipe : a system call,pipe is like a one-way tunnel that connects two process together. When one process needs to send information to another process, it uses this tunnel. Just like water flows through a real pipe from one end to the other, data flows through this virtual pipe from the first process to the second process 

|-- Fork : a system call, fork is like making a copy of a running program. When a program uses fork, it creates a child process (copy) that is almost exactly like its parent process (original). 

|--


****************\\ MANDATORY //**************

1- first think we check in start of program of some requirements:
--> check if  arguments is 5 (infile cmd1 cmd2 outfile).
    |--> if arguments is not 5 we write error in stderror ("Usage: ./pipex file1 cmd1 cmd2 file2") and exit with 1 that mean program exit with error. 
--> check if env is not empty.
    |--> if *Environment variables* is empty we write error in stderror ("Error empty Environment") and exit with 1.
2- call a function call pipex we passe in parameter (char **argments, char **environments) :
--> create a *pipe* and pass in pipe array of integers must be at least have 2 integers (pip[2]) 
    |--> if faild to pipe write error in stderror ("faild to pipe") exit with 1 .
--> create a child using *fork* and save return of fork in variable(fork return process id of child to parent process but not for child process, in child fork return 0).
    |--> if faild to fork write error in stderror ("faild to fork") exit with 1 .
--> if the value of variable is 0 the mean is the child :
    --> call function call first_child passe in parameter (char **argments, char **environments) :
        --> open file (infile) we call function that responsible to open our files we pass in parameter (name of file(argv[1]) and flag that represent if is for stdin or stdout (0 or 1)).
            --> check if file is exist
                |--> if not exit write a message with name of function  

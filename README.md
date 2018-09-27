# Shell 
 
The shell has the following capabilities

+ Inbuilt cd,echo,ls,pwd,fg,bg,jobs,setenv,unsetenv
+ Can run process at foreground and background
+ Can give information about process info
+ When bg process is done, message is displayed
+ you can check the dynamic time as well using clock command
+ It gives info on all running background process
+ Commands can be piped and redirected
+ Shell exits only on quit 
+ Process is terminated on ctrl-c
+ Process is suspended on ctrl-z
+ Stopped background process run on bg
+ Overkill kills all background process


## Setup

To run the shell, you need to do the following-

+ Run `make`
+ Run `./shell`

## File Map 
 
### `src/`
- `shell.c` has the startup code
- `mainloop.c` has all main functions such as input commands, bg checker working
- `run.c` has ctrl-z handler, execute function which is for `quit` and the process handler
- `pipeShell.c` has pipe and redirection handling
- `exitHandler.c` has ctrl-c handler
- `prompt.c` has the function for generating prompt
- `commands.c` has the function for splitting of commands
- `newPointer.c` initializes a new char pointer
- `bgKiller.c` function for terminating background process
- `cd.c` has cd implemented
- `clock.c` has clock implemented
- `echo.c` has echo implemented
- `fgShell.c` has fg and bg implemented
- `killJobShell.c` has jobs and kjob implemented
- `ls.c` has ls implemented
- `overkill.c` has overkill implemented
- `pinfo.c` has pinfo implemented
- `setenvShell.c` has setenv,getenv and unsetenv implemented

### `include/`

- `shellFunctions.c` has all the functions and global constants declared

### `obj/`
Has all the binaries of all `src` files.

## Road Map

When you run `./shell`, it starts up from `shell.c` and initializes all global variables like killy,bgy etc. Then it goes into `mainloop.c` where in background process life is checked and command input is handled. This is further sent to `pipeShell.c` where in the input and ouptut file descriptors are set for each command in pipe. Recursively they are executed by the functions in `run.c` namely by `launch` function. This function basically creates the processes and does the signal handling as well.   
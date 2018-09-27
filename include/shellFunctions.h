#ifndef SHELL_H
#define SHELL_H

#define buffer_size 1024
//This is for strtok
#define TOK_BUFF_SIZE 64
#define TOK_DELIM " \t\n\a\r"
#define COM_DELIM ";"
#define MAX 32767
typedef int (*commands)(char**);

char *bg_processes[32768];
int bg_order[32768];
int lastProcess;
int killy;
int bgy;

int shellPID;

char* home;

char *new();

char *finalPath();

char *read_line();

char **split_line(char *line);

char **split_command(char *line);

int getJobNum(int jobPid);

int jobsShell(char **args);

int overkillShell(char **args);

void fgShell(char **args);

int kjobsShell(char **args);

int setenvShell(char **args);

int unsetenvShell(char **args);

int getenvShell (char **args);

int bgShell(char **args);

int delete(char **a,int p,int i);

int isAppend(char **args);

char *input_file(char **args);

char *output_file(char **args);

int countToken(char **args);

char **modify_token(char **tokens,int pos);

void execute_with_pipes (char *input, int input_pipe);

void exitHandler(int sig_num);

void tostring(char *str, int num);

int cdShell(char **args);

int pwdShell(char **args);

int clockShell(char **args);

int echoShell(char **args);

int launch(char **args,int input_fd,int output_fd);

int exitShell(char **args);

int lsShell(char **args);

int execute(char **args,int input_fd,int output_fd);

int pinfoShell(char **args);

int prompt();

void bgChecker(int sig_num);

void shell_loop();

#endif
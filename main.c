#include "builtins.h"
#include "parse.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

//input: catches signals, only does anything if ctrl+c is pressed
//output: if ctrl+c is pressed, it instead causes the terminal to move one line downwards
static void sighandler(int signo) {
  if (signo==SIGINT) {
    char curDir[512];

    cwd(curDir);
    printf("\n");
    printTerminal(curDir);
    fflush(stdout);
  }
}

// input: a pointer to an array of strings
// runs the command in the array of strings, handles operators and recurses on ; or |
// output: none
void run(char** tokarr) {
    // if contains semicolon, run the first part, then run the second part
    int semicolon = contains(tokarr, ";");
    if (semicolon) {
        char* first[semicolon];
        subarr(tokarr, 0, semicolon, first);
        run(first);
        int len = 0;
        while (tokarr[len] != NULL) {
            len++;
        }
        char* second[len - semicolon];
        subarr(tokarr, semicolon + 1, len, second);
        run(second);
        return;
    }
    int inbkp = 0;
    int outbkp = 1;
    // handle | here, send output to tempfile (no time for popen)
    int pipe = contains(tokarr, "|");
    if (pipe) {
        // recurse
        char* first[pipe];
        subarr(tokarr, 0, pipe, first);
        int fd = open("tempfile", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        outbkp = dup(1);
        dup2(fd, 1);
        run(first);
        dup2(outbkp, 1);
        close(fd);
        int len = 0;
        while (tokarr[len] != NULL) {
            len++;
        }
        char* second[len - pipe];
        subarr(tokarr, pipe + 1, len, second);
        fd = open("tempfile", O_RDONLY);
        inbkp = dup(0);
        dup2(fd, 0);
        run(second);
        dup2(inbkp, 0);
        close(fd);
        return;
    }

    int insertion = contains(tokarr, "<");
    if (insertion) {
        inbkp = dup(0);
        int fd = open(tokarr[insertion + 1], O_RDONLY);
        dup2(fd, 0);
        tokarr[insertion] = NULL;
    }

    int redirect = contains(tokarr, ">");
    if (redirect) {
        outbkp = dup(1);
        int fd = open(tokarr[redirect + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        dup2(fd, 1);
        tokarr[redirect] = NULL;
    }

    // builtins
    if (!strcmp(tokarr[0], "cd")) {
        cd(tokarr[1]);
    } else if (!strcmp(tokarr[0], "exit")) {
        exit(0);
    } else {
        int pid = fork();
        if (pid) {
            // parent
            int status;
            wait(&status);
            dup2(outbkp, 1);
            dup2(inbkp, 0);
            return;
        }
        // child
        if(execvp(tokarr[0], tokarr) == -1){
           //handles execvp failiures, mentions tag if exist else blames commands, bad files are handled by execvp
           
        
            if(tokarr[1] != NULL && strchr(tokarr[1], '-')){
                printf("Command %s or tags starting with %s not found, and cannot be installed\n", tokarr[0], tokarr[1]);
                exit(0);
                
            }
        
            printf("Command %s not found, and cannot be installed", tokarr[0]);
                
            
            fflush(stdout);
            
        }
        exit(0);
    }
}

int main() {
  setvbuf(stdout, NULL, _IONBF, 0);
  char curDir[512];

  cwd(curDir);
  char line[256];
  signal(SIGINT, &sighandler);
  printTerminal(curDir);
  int prev = 0;
  int tim = time(NULL);
  while (prev || fgets(line, 256, stdin)) {
    char * tmpLine = line;

    valid_arg(line);//parses line correctly
    if (prev || (strcmp(line, "up") && strcmp(line, "down") && strcmp(line, "enter"))) {
      if (prev) {
        char *new = getOldCommandIndex(getComLoc());
        prev = 0;
        strcpy(line, new);
        printf("%s\n", new);
        pushTracker(0);
      }
      updateTracker(tmpLine);//Keeps track of previous commands
      char *tokarr[256];
      char *tok;
      int i = 0;
      char *linecpy = line;
      while ((tok = strsep(&linecpy, " ")) != NULL) {
          tokarr[i] = tok;
          i++;
      }
      tokarr[i] = NULL;
      tokarr[i - 1][strlen(tokarr[i - 1])] = '\0';
     
      run(tokarr);
      cwd(curDir);
    }
    //handles command memory
    else {
      if (!strcmp(line, "up")) {
        pushTracker(1);
        printTerminal(curDir);
        printf("Current command to print: '%s' type 'enter' to confirm\n",getOldCommandIndex(getComLoc()));
      }
      else if (!strcmp(line, "enter")) {
        prev = 1;
      }
      else {
        pushTracker(-1);
        printTerminal(curDir);
        printf("Current command to print: '%s' type 'enter' to confirm\n",getOldCommandIndex(getComLoc()));
      }
    }
    if (time(NULL)-tim>.0000001) {
      printTerminal(curDir);
    }

    fflush(stdout);
  }
  exit(0);
}

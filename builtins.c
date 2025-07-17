#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
// Contains functions used for shell builtins and the prompt

int comLoc = 0;
int comSize = 0;
char oldCommands[512][512];

// input: the path to the directory you want to change to
// output: changes the directory to the path specified, returns 0 if successful, returns errno if not
int cd(char* path) {
    int res = chdir(path);
    if (res == -1) {
        return err();
    } else {
        return 0;
    }
}


//input: string that can hold at least 256 chars
//output: 0 if there are no issues, returns errno if issues, sets the string to null terminated cwd
int cwd(char* out){
   if(!getcwd(out, 255)){
    strcat(out, "\0");
    return 0;
   }
   else{
    return errno;
   }
}

// input: The directory path that the user is currently in
// output: Prints the bar with a special bit of color
void printTerminal(char* curDir) {
  char* green = "\033[0;32m";
  char* yellow = "\033[0;33m";
  char* black = "\033[0;30m";
  char* white = "\033[0;37m";
  printf("%sDIG:%s %s%s$ %s", green, yellow, curDir, green, white);
}


//input: previous command inutted into the terminal to be used again
//increases the size of oldCommands and adds a previous command that was used
void updateTracker(char line[]) {
  for (int i=comSize; i>0; i--) {
    strcpy(oldCommands[i], oldCommands[i-1]);
  }
  strcpy(oldCommands[0], line);
  comSize++;
}

//input: moving determines how much the comLoc changes, comLoc determines which command
//oldCommands is going to print
//no output, only updates comLoc
void pushTracker(int moving) {
  comLoc+=moving;
  if (moving == 0) {
    comLoc = 0;
  }
  if (comLoc>=comSize) {
    comLoc=comSize-1;
  }
  if (comLoc<0) {
    comLoc=0;
  }
  //Method needs to work automatically once '^[[A' is detected, and then print out
  //the command at comLoc, should reset upon enter being pressed
}

//input: none
//output: returns the value of comLoc
int getComLoc() {
  return comLoc;
}

//input: index of oldCommands that stores an old command
//output: returns command of index 'index'
char* getOldCommandIndex(int index) {
  return oldCommands[index];
}

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
// Contains functions that are used to parse the input from the terminal/manipulate strings

// input: a string; the index you want to remove from the string
// output: removes the char at index 'index'
void removeIndex(char arg_ary[], int index) {
  int size = strlen(arg_ary);
  for (int i=index; i<size; i++) {
    arg_ary[i] = arg_ary[i+1];
  }
}

// input: a character array to be edited, a character to be added, an index where it should be added
// output: arg is updated to include 'adding' at index 'index'
void addIndex(char arg[], char adding, int index) {
  int size = strlen(arg);
  for (int i=size+1; i>index; i--) {
    arg[i] = arg[i-1];
  }
  arg[index] = adding;
}

// input: a character array needing spaces between semicolons
// output: modifies the character array to be a valid argument
void spaceAdder(char arg[]) {
  int size = strlen(arg);
  for (int i=0; i<size; i++) {
    if (arg[i]==';') {
      addIndex(arg, ' ', i+1);
      addIndex(arg, ' ', i);
      i++;
    }
  }
}

// input: a string that you want to remove extra spaces from
// output: arg_ary is now free of spaces after a space or a semicolen
void valid_arg(char arg_ary[]) {
  int size = strlen(arg_ary);
  for (int i=0; i<size; i++) {
    if (*(arg_ary+i)==' ') {
      if (*(arg_ary+i+1)==' ' || i==0 || *(arg_ary+i+1)==';') {
        removeIndex(arg_ary, i);
        i--;
        size--;
      }
    }
    else if (*(arg_ary+i)==';') {
      if (*(arg_ary+i+1)==' ' || *(arg_ary+i+1)==';') {
        removeIndex(arg_ary, i+1);
        i--;
        size--;
      }
    }
    else if (*(arg_ary+i)=='\n') {
      removeIndex(arg_ary, i);
      i--;
      size--;
    }
  }
  spaceAdder(arg_ary);
}

// input: string with input lines; empty string array to hold the seperate command arguments
// output: arg_ary now functions for execvp
void parse_args( char*  line, char**  arg_ary ) {
    int size = 0;
    while (*(arg_ary+size) = strsep(&line, " ")) size++;
}

// input: a string you want to remove the \n and \r from
// output: the string is then modified to no longer include those characters
void clear(char* s) {
    int i=0;
    while(*(s+i)) {
        if (*(s+i)=='\n' || *(s+i)=='\r') {
            s[i] = 0;
        }
        i++;
    }
    i = strlen(s);
    if (s[i]==' ') {
      s[i] = 0;
    }
}

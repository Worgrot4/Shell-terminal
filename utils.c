#include <errno.h>
#include <string.h>
#include <stdio.h>
// Contains general utility functions

// input: none
// output: prints the error message associated with errno and returns theerrno
int err(){
  printf("errno %d\n",errno);
  printf("%s\n",strerror(errno));
  return errno;
}

// input: a pointer to an array of strings, a start index, an end index (not inclusive), and a pointer to an array of strings (for output)
// output: output string array will contain the subarray
void subarr(char** arr, int start, int end, char** out) {
    for (int i = start; i < end; i++) {
        out[i - start] = arr[i];
    }
    out[end - start] = NULL;
}

// input: a pointer to an array of strings and a string to find
// output: the index of the string if found, 0 otherwise
int contains(char** arr, char* str) {
    for (int i = 0; arr[i] != NULL; i++) {
        if (strcmp(arr[i], str) == 0) {
            return i;
        }
    }
    return 0; // THIS IS A BAD IDEA BUT IT WORKS
}
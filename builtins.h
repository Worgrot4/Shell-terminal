#ifndef BUILTINSH
#define BUILTINSH
int cd(char* path);
int cwd(char* out);
void printTerminal(char* curDir);
void updateTracker(char line[]);
void pushTracker(int moving);
int getComLoc();
char* getOldCommandIndex(int index);
#endif

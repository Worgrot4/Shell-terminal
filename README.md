[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/77as2zNO)
# Systems Project2 - MyShell
A description of what features your shell implements:
- Our shell implements pwd, cd, exit and the standard operators (`>`, `<`, `|`, `;`). The `run` function handles these by doing recursion when necessary, so multiple pipe operators can be used in a row (so, `echo hi | cat | cat | cat` works).
- The prompt (which contains the current directory) uses ascii escape sequences to add colors.
- Ctrl+C doesn't exit the shell and instead quits the current line and moves on to a new one (like bash).
- Typing 'enter' attempts the last used command, typing 'up' cycles through your previous commands, typing 'down' cycles backwards, similar to the arrow keys (up and down)

A description of what features you attempted to implement but were unsuccessful:
- We attempted to have an auto-complete tab feature which we currently have not finished, as all versions that are guaranteed to work on linux distros seem to break ctrl+c.

Any bugs or things you want me to know about your program:
- When using the insertion operator to send commands to the shell, it may display the shell prompts (with the current directory, etc) between the output of each command. (`./shell.out < test.txt`)

A copy of every function header:
```
int cd(char* path);
int cwd(char* out);
void printTerminal(char* curDir);
void updateTracker(char line[]);
void pushTracker(int moving);
int getComLoc();
char* getOldCommandIndex(int index);
void removeIndex(char arg_ary[], int index);
void addIndex(char arg[], char adding, int index);
void spaceAdder(char arg[]);
void valid_arg(char arg_ary[]);
void parse_args(char* line, char** arg_ary);
void clear(char* s);
int err();
void subarr(char** arr, int start, int end, char** out);
int contains(char** arr, char* str);
static void sighandler(int signo);
void run(char** tokarr);
```

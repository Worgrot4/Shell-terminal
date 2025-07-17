.PHONY: clean run compile clone commit
run: shell.out
	@./shell.out $(ARGS)
compile shell.out: main.o parse.o builtins.o utils.o
	@gcc -o shell.out main.o parse.o builtins.o utils.o
main.o: main.c
	@gcc -c main.c
parse.o: parse.c
	@gcc -c parse.c
builtins.o: builtins.c
	@gcc -c builtins.c
utils.o: utils.c
	@gcc -c utils.c
clean:
	@rm -f *.o shell.out
clone:
	@bash clone.sh
commit:
	make clean
	git add -A

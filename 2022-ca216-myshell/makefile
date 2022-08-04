# Patricija Shalkauskaite, 20467952 - Operating Systems Project 1
# ca216/myshell

CC=gcc  # The compiler will be placed in a variable

bin/myshell: src/myshell.c src/utility.c src/myshell.h
	$(CC) -Wall src/myshell.c src/utility.c -o bin/myshell

clean:
	rm -f bin/myshell

.PHONY: clean  # So shell doesn't interpret clean as something other than the command specified in make.

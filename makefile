CFLAGS = -g -Wall -Wextra 

all:
	echo "Build the program"
build:
	clang $(CFLAGS) strstr.c -o str
clean:
	rm convertc

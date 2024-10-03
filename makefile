all: asst6


asst6 : asst6.c some_heap.c
	gcc asst6.c some_heap.c -o asst6


%.o: %.c some_heap.h
	gcc -Wall -Wextra -g -c $< -o $@


clean:
	rm -f asst6.c some_heap.c asst6


.PHONY: all clean

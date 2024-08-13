CC = gcc
DEBUG_CFLAGS = -g
RELEASE_CFLAGS = -O2 -DNDEBUG
CFLAGS = -Wall -c -std=c23 #-pedantic-errors 

# por defecto uso 
ifndef BUILD_TYPE
    BUILD_TYPE = release
endif

# modifico CFLAGS en base a BUILD_TYPE
ifeq ($(BUILD_TYPE),debug)
    CFLAGS += $(DEBUG_CFLAGS)
else ifeq ($(BUILD_TYPE),release)
    CFLAGS += $(RELEASE_CFLAGS)
endif

#indica qué objetivos deben realizarse sí o sí, sin importar las dependencias
.PHONY: clean run

exec: main.o utils.o
	$(CC) main.o utils.o -o exec

main.o: main.c utils.h
	$(CC) $(CFLAGS) -o main.o main.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -o utils.o utils.c

clean:
	rm -f main.o utils.o exec

run: exec
	./exec
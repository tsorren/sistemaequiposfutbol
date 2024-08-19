CC = gcc
DEBUG_CFLAGS = -g
RELEASE_CFLAGS = -O2 -DNDEBUG
CFLAGS = -c -std=c23 #-pedantic-errors 

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

exec: main.o utils.o render.o files.o jugador.o
	$(CC) main.o utils.o render.o files.o jugador.o -o exec

main.o: main.c utils.h render.h files.h jugador.h
	$(CC) $(CFLAGS) -o main.o main.c 

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -o utils.o utils.c

render.o: render.c render.h jugador.h utils.h
	$(CC) $(CFLAGS) -o render.o render.c

files.o: files.c files.h jugador.h render.h utils.h
	$(CC) $(CFLAGS) -o files.o files.c

jugador.o: jugador.c jugador.h
	$(CC) $(CFLAGS) -o jugador.o jugador.c

clean:
	rm -f *.o exec.exe

run: exec
	./exec
CC         = g++
CFLAGS     = --std=c++11 -g -Wall
CFLAGSROOT = `root-config --cflags`
LIBSROOT   = `root-config --glibs`

all: prova2

poligono.o: poligono.cpp
	$(CC) $(CFLAGS) -c poligono.cpp      $(CFLAGSROOT)
prova2: prova2.cpp poligono.o
	$(CC) $(CFLAGS) -o prova2 prova2.cpp poligono.o $(CFLAGSROOT) $(LIBSROOT)

clean:
	rm *.o prova2

CC     = g++
CFLAGS = -g -Wall
LDFLAGS = -ldl
OBJS = main.o

all: game 

game: $(OBJS)
	$(CC) $(OBJS) -o game $(LDFLAGS)

main.o: main.cpp Game.h GameMove.h GameTree.h GameTeam.h GameUser.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f game *.o

# This is GNU makefile extension to notify that roughly means: 'clean' does
# not depend on any files in order to call it.
.PHONY: clean

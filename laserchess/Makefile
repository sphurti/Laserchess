CC     = g++
CFLAGS = -g -Wall -fPIC -I../
LDFLAGS = -shared
OBJS = Board.o LaserChess.o Move.o Piece.o User.o

all: laserchess.so

laserchess.so: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@ 

Board.o: Board.cpp Board.h
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

LaserChess.o: LaserChess.cpp LaserChess.h
	$(CC) $(CFLAGS) -c -o $@ $<

Move.o: Move.cpp Move.h
	$(CC) $(CFLAGS) -c -o $@ $<

Piece.o: Piece.cpp Piece.h
	$(CC) $(CFLAGS) -c -o $@ $<

User.o: User.cpp User.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f laserchess.so *.o

# This is GNU makefile extension to notify that roughly means: 'clean' does
# not depend on any files in order to call it.
.PHONY: clean

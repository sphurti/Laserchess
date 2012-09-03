CC     = g++
ABSERIAL_CFLAGS = -g -Wall -fPIC -I../
ABSERIAL_LDFLAGS = -shared
ABSERIAL_OBJS = AlphaBetaSerial.o

all: abserial.so abparallel.so

abserial.so: $(ABSERIAL_OBJS)
	$(CC) $(ABSERIAL_OBJS) $(ABSERIAL_LDFLAGS) -o $@ 

AlphaBetaSerial.o: AlphaBetaSerial.cpp AlphaBetaSerial.h
	$(CC) $(ABSERIAL_CFLAGS) -fPIC -c -o $@ $<

ABPARALLEL_CFLAGS = -g -Wall -fPIC -fopenmp -I../
ABPARALLEL_LDFLAGS = -shared
ABPARALLEL_OBJS = AlphaBetaParallel.o

abparallel.so: $(ABPARALLEL_OBJS)
	$(CC) -fopenmp $(ABPARALLEL_OBJS) $(ABPARALLEL_LDFLAGS) -o $@ 

AlphaBetaParallel.o: AlphaBetaParallel.cpp AlphaBetaParallel.h
	$(CC) $(ABPARALLEL_CFLAGS) -fPIC -c -o $@ $<

clean:
	rm -f abserial.so *.o

# This is GNU makefile extension to notify that roughly means: 'clean' does
# not depend on any files in order to call it.
.PHONY: clean

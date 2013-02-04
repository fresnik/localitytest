CC=gcc
LIBS=-lrt

all: localitytest

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

localitytest: localitytest.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

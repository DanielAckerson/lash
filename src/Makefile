CFLAGS= -std=c11 -Wall -O2 -O0 -g
LDFLAGS= -llua

all: lash

lash: lash.o env.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $^ $(CFLAGS)

.PHONY: clean
clean:
	@-rm -rf *.o lash

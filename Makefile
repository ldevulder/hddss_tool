all: read_hddss

CFLAGS = -Og

read_hddss.o: hddss.h

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

read_hddss: read_hddss.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	-rm -f read_hddss *.o

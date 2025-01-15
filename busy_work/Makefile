CFLAGS += -g

BINARIES := busy_work

all: $(BINARIES)
	
%: %.c
	$(CC) -o $@ $< -O0 $(CFLAGS)


clean:
	rm -fr  $(BINARIES)

CFLAGS += -g

BINARIES := access_forbidden

all: $(BINARIES)
	
%: %.c
	$(CC) -o $@ $< -O0 $(CFLAGS)


clean:
	rm -fr  $(BINARIES)

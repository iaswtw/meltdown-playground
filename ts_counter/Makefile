CFLAGS += -g

BINARIES := ts_counter

all: $(BINARIES)
	
%: %.c
	$(CC) -o $@ $< -O0 $(CFLAGS)


clean:
	rm -fr  $(BINARIES)

CFLAGS += -g

BINARIES := check_tsx

all: $(BINARIES)
	
%: %.c
	$(CC) -o $@ $< -O0 $(CFLAGS)


clean:
	rm -fr  $(BINARIES)

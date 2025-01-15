CFLAGS += -g

BINARIES := meltdown1 detect_flush_reload_threshold

all: $(BINARIES)
	
%: %.c
	$(CC) -o $@ $< -O0 $(CFLAGS)


clean:
	rm -fr  $(BINARIES)

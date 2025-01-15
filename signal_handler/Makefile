CFLAGS += -g
#CFLAGS += -O2
#CFLAGS += -g -pg -fprofile-arcs -ftest-coverage
#LDFLAGS += -pg -fprofile-arcs -ftest-coverage
#EXTRA_CLEAN += meltdown_test.gcda meltdown_test.gcno $(PROJECT_ROOT)gmon.out
#EXTRA_CMDS = rm -rf meltdown_test.gcda


BINARIES := suppress_sig_using_handler

all: $(BINARIES)
	
%: %.c
	$(CC) -o $@ $< -O0 


clean:
	rm -fr  $(BINARIES)

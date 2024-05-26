SRC := $(wildcard *.c)
BIN := $(SRC:.c=)
DEBUG := n
ifeq ($(DEBUG),y)
CFLAGS += -g
endif

all: $(BIN)

%: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -rf $(BIN)

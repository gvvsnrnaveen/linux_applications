SRC := $(wildcard *.c)
BIN := $(SRC:.c=)

all: $(BIN)

%: %.c
	$(CC) -o $@ $<

clean:
	rm -rf $(BIN)

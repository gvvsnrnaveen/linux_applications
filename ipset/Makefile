SRC := $(wildcard *.c)
BIN := $(SRC:.c=)
LIBS += -lipset

all:$(BIN)

%: %.c
	$(CC) -o $@ $< $(LIBS)

clean:
	rm -rf $(BIN)

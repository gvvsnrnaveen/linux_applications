all:
	$(CC) pub.c -o pub -lmosquitto -lssl -ljson-c
	$(CC) sub.c -o sub -lmosquitto -lssl -ljson-c
	
clean:
	rm -rf pub sub

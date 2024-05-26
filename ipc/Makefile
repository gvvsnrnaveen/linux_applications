SRC :=  $(wildcard *.cc)
BIN := $(SRC:.cc=.o)
CCFLAGS += -std=c++17 -fPIC
LIBS += -lpthread -lrt -fPIC
all: $(BIN) msgq shm

msgq: 
	$(CXX) -o msgq_receiver msgq_receiver.o msgq_manager.o $(LIBS)
	$(CXX) -o msgq_sender msgq_sender.o msgq_manager.o $(LIBS)

shm:
	$(CXX) -o shm_write shm_writer.o shm_manager.o $(LIBS)
	$(CXX) -o shm_reader shm_reader.o shm_manager.o $(LIBS)

%: %.cc
	$(CXX) -o $@ $< $(CCFLAGS)

clean:
	rm -rf $(BIN) msgq_receiver msgq_sender shm_write shm_reader

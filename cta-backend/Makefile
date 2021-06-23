
CC=g++-8
CFLAGS=-I. -Iinclude -Iinclude/external --std=c++17 

ODIR=obj
LIBS=-lpthread

HDR:=$(shell find . -name '*.h')
SRC:=$(shell find . -name '*.cpp')
DEPS:=$(HDR) $(SRC)


_OBJ:=$(patsubst %.cpp,%.o,$(notdir $(SRC)))
OBJ:=$(patsubst %,$(ODIR)/%,$(_OBJ))


all: ctaserver

$(ODIR): 
	mkdir -p $@

$(ODIR)/%.o: src/%.cpp $(DEPS) $(ODIR)
	$(CC) $(CFLAGS) -g -c -o $@ $< 

ctaserver: $(OBJ)
	$(CC) -g -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm -f ctaserver
	rm -rf $(ODIR) 
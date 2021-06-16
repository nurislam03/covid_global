
CC=g++
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
	$(CC) $(CFLAGS) -c -o $@ $< 

ctaserver: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm ctaserver
	rm -rf $(ODIR) 

CC=g++-8
CFLAGS=-I. -Iinclude -Iinclude/external \
	-I/usr/local/include/mongocxx/v_noabi \
	-I/usr/local/include/libmongoc-1.0 \
	-I/usr/local/include/bsoncxx/v_noabi \
	-I/usr/local/include/libbson-1.0 \
	--std=c++17 -D CPPHTTPLIB_OPENSSL_SUPPORT


ODIR=obj
LIBS=-lpthread -L/usr/local/lib -lmongocxx -lbsoncxx -lssl -lcrypto

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

run:
	LD_LIBRARY_PATH=/usr/local/lib ./ctaserver

.PHONY: clean

clean:
	rm -f ctaserver
	rm -rf $(ODIR) 
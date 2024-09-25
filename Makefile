CC=gcc
CFLAGS=-Wall -Wextra -pedantic -I./include/
LDFLAGS=-L./build/ -lloguva

BUILDDIR=build
INSTALLDIR=/usr/lib
LIBHEADER=loguva.h
LIBNAME=libloguva.so

SRC=$(wildcard src/*.c)
LIB=$(BUILDDIR)/$(LIBNAME)

SRC_SAMPLE=$(wildcard samples/*.c)
BIN_SAMPLE=$(BUILDDIR)/sample

.PHONY: all install uninstall clean samples

all: always $(LIB) $(BIN_SAMPLE)

$(LIB): $(SRC)
	$(CC) $(CFLAGS) -shared -fPIC $^ -o $@

$(BIN_SAMPLE): $(SRC_SAMPLE)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

samples:
	LD_LIBRARY_PATH=$(BUILDDIR) $(BIN_SAMPLE)

always:
	mkdir -p $(BUILDDIR)

install: $(LIB)
	cp $(LIB) $(INSTALLDIR)
	cp include/$(LIBHEADER) /usr/include/

uninstall:
	rm $(INSTALLDIR)/$(LIBNAME)
	rm /usr/include/$(LIBHEADER)

clean:
	rm -rf $(BUILDDIR)

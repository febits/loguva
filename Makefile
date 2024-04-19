CC=gcc
CFLAGS=-Wall -Wextra -pedantic
LDFLAGS=-L./build/ -lloguva
CINCLUDE=-I./include/
CFLAGS+=$(CINCLUDE)

BUILDDIR=build
INSTALLDIR=/usr/lib

SRC=$(wildcard src/*.c)
LIB=$(BUILDDIR)/libloguva.so

SAMPLE=samples/sample
SRCSAMPLE=samples/sample.c

default: $(LIB)
all: $(LIB) $(SAMPLE)

$(LIB): $(SRC)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -shared -fPIC $^ -o $@

$(SAMPLE): $(SRCSAMPLE)
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

run_samples:
	LD_LIBRARY_PATH=$(BUILDDIR) $(SAMPLE)

clean:
	rm -rf $(BUILDDIR) $(SAMPLE)

SRC := ./src/
OBJ := .obj/
SOURCES := $(shell find ./src -name "*.c")
LINKERS :=  $(subst $(SRC), $(OBJ), $(SOURCES:.c=.o))

all: $(LINKERS) build

$(LINKERS): $(SOURCES)
	mkdir -p $(dir $@)
	gcc -c $(subst .obj,./src, $(@:.o=.c)) -o $@

build:
	gcc $(LINKERS) -o lzw

unit-test: 
	gcc ./tests/unit-tests.c ./tests/libtap/tap.c -o unit-tests && ./unit-tests 

clean:
	rm -rf .obj

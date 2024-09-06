SRC := ./src/
OBJ := .obj/

SOURCES := $(shell find ./src -name "*.c")
LINKERS :=  $(subst $(SRC), $(OBJ), $(SOURCES:.c=.o))

TEST_OBJ := .test-obj/
TEST_SOURCES := $(shell find ./ -name "*.c" -not -path "./src/main.c")
TEST_LINKERS :=  $(subst ./, $(TEST_OBJ), $(TEST_SOURCES:.c=.o))


all: $(LINKERS) build

unit-test: $(TEST_LINKERS) build-unit-tests 

$(LINKERS): $(SOURCES)
	mkdir -p $(dir $@)
	gcc -c $(subst .obj,./src, $(@:.o=.c)) -o $@

$(TEST_LINKERS): $(TEST_SOURCES)
	mkdir -p $(dir $@)
	gcc -c $(subst .test-obj,., $(@:.o=.c)) -o $@

build-unit-tests:
	gcc $(TEST_LINKERS) -o unit-tests && ./unit-tests 

build:
	gcc $(LINKERS) -o lzw

clean:
	rm -rf .obj

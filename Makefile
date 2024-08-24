SRC := ./
OBJ := .obj/
SOURCES := $(shell find -name "*.c")
LINKERS :=  $(subst $(SRC), $(OBJ), $(SOURCES:.c=.o))

all: $(LINKERS) build

$(LINKERS): $(SOURCES)
	mkdir -p $(dir $@)
	gcc -c $(subst .obj,., $(@:.o=.c)) -o $@

build:
	gcc $(LINKERS)

clean:
	rm -rf .obj

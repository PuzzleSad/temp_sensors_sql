CC=ccache gcc
CFLAGS=-Wall -Wextra -O2 --std=c11

BIN=a.elf

HEADERDIR=.
SOURCEDIR=.
BUILDDIR=build


SOURCES= $(wildcard *.c)\
	$(wildcard src/*.c)\
	$(wildcard src/sql/src/*.c)\
	$(wildcard src/log/src/*.c)\
	$(wildcard src/sensors/src/*.c)\
	$(wildcard src/reading/src/*.c)

OBJECTS= $(patsubst %.c, $(BUILDDIR)/%.o, $(notdir $(SOURCES)) )


all: bin run

# all: 
# 	@echo $(SOURCES)
# 	@echo $(OBJECTS)

nrun: bin

bin: $(BIN)

run: $(BIN)
	./$(BIN)

$(BIN): $(OBJECTS)
	@echo "linking..."
	@$(CC) $(CFLAGS) -I$(HEADERDIR) -o $@ $^ -lm -lsqlite3 -lpthread

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c
	@$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@

$(BUILDDIR)/%.o: src/%.c
	@$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@

$(BUILDDIR)/%.o: src/sql/src/%.c
	@$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@

$(BUILDDIR)/%.o: src/log/src/%.c
	@$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@

$(BUILDDIR)/%.o: src/sensors/src/%.c
	@$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@

$(BUILDDIR)/%.o: src/reading/src/%.c
	@$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@


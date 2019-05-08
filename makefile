# Directories (Include, Object, Library, Source)
IDIR=include
TDIR=test
ODIR=src/obj
SDIR=src

# Compiler Options
CC=gcc
CFLAGS=-I$(IDIR) $(LIBS) -g

#All
#LIBS +=-lm -pthread -ldl

# Dependencies and Objects lists
_DEPS = queue.h #bst.h hash.h heap.h stack.h
DEPS  = $(patsubst %,$(IDIR)/%,$(_DEPS))
_OBJ = queue.o #bst.o hash.o heap.o stack.o
OBJ  = $(patsubst %,$(ODIR)/%,$(_OBJ))
_TEST_OBJ = test_all.o test_hash.o test_queue.o
TEST_OBJ  = $(patsubst %,$(TDIR)/%,$(_TEST_OBJ))

# Compile all C objects
$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Compile all C tests
$(TDIR)/%.o: $(TDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Compile executable
kglib_test: $(OBJ) $(TEST_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Clean
.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

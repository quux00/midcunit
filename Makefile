ex1_NAME := midcunit_example1
ex2_NAME := midcunit_example2

ex1_C_SRCS := $(ex1_NAME).c
ex2_C_SRCS := $(ex2_NAME).c minmax.c

ex1_OBJS := ${ex1_C_SRCS:.c=.o}
ex2_OBJS := ${ex2_C_SRCS:.c=.o}

program_INCLUDE_DIRS := .
program_LIBRARY_DIRS :=
program_LIBRARIES :=

# these are the standard flags I compile with (for gcc)
# add -g if you want to compile with symbols for debugging
CFLAGS+=-Wall -W -pedantic -std=c99 -D_GNU_SOURCE
CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))

.PHONY: all test clean distclean

all: $(ex1_NAME) $(ex2_NAME)

$(ex1_NAME): $(ex1_OBJS)
	$(LINK.c) $(ex1_OBJS) -o $(ex1_NAME)

$(ex2_NAME): $(ex2_OBJS)
	$(LINK.c) $(ex2_OBJS) -o $(ex2_NAME)

test: $(ex1_NAME) $(ex2_NAME)
	@ echo "Example Test 1 should pass.  Example Test 2 should fail."
	./$(ex1_NAME)
	@ echo "-------------------------------"
	./$(ex2_NAME)

help:
	@ echo "== Targets =="
	@ egrep "^[^:. ]+:" [Mm]akefile | cut "-d:" -f1 

clean:
	@- $(RM) *.o

distclean:
	@- file * | grep ELF | cut "-d:" -f1 | xargs $(RM) 2>/dev/null; ls >/dev/null;

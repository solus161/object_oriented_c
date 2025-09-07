CC	= gcc
CFLAGS	= -fPIC -Wall -Wno-unused -Wextra -O2 -g  # C flags
LDFLAGS	= -shared   # linking flags

SOURCELIB	= calculator.c
TARGETLIB	= libcalculator.so

SOURCEAPP	= test_calculator.c
TARGETAPP	= test_calculator.o

# Build lib
$(TARGETLIB):	$(subst .c,.o,$(SOURCELIB))
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^ -lm

$(TARGETAPP):	$(SOURCEAPP)
	$(CC) $(SOURCEAPP) -L. -lcalculator -o $(TARGETAPP)
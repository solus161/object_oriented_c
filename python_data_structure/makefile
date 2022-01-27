CC	= gcc
CFLAGS	= -fPIC -Wall -Wextra -O2 -g  # C flags
LDFLAGS	= -shared   # linking flags

SOURCELIB	= new.c pystruct.c
TARGETLIB	= libpystruct.so

SOURCEAPP	= test_pystruct.c
TARGETAPP	= test_pystruct.o

# Build lib
$(TARGETLIB):	$(subst .c,.o,$(SOURCELIB))
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^

# $(TARGETAPP):	$(SOURCEAPP)
# 	$(CC) $(SOURCEAPP) -L -lpystructls -I -o $(TARGETAPP)
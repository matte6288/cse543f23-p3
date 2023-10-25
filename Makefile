# File          : Makefile
# Description   : Build file CSE543 Project-2

# Environment Setup and Variables
LIBDIRS=-L. 
CC=gcc 
CFLAGS=-c $(INCLUDES) -g -Wall
LINK=gcc -g
LDFLAGS=$(LIBDIRS)
AR=ar rc
RANLIB=ranlib

# Suffix rules
.c.o :
	${CC} ${CFLAGS} $< -o $@

# Setup builds
TARGETS=cse543-p3
LIBS=-lgcrypt 

# Project Protections
p2 : $(TARGETS)

cse543-p2 : monitor.o lattice.o linked-list.o utils.o
	$(LINK) $(LDFLAGS) monitor.o linked-list.o lattice.o utils.o $(LIBS) -o $@

clean:
	rm -f *.o *~ $(TARGETS)
#########################################################################
#standard targets in makefile
#all
#clean

#standard symbols
#$@-> name of the target
#$?-> name of all the prerequisites which are newer than the target
#$<-> name of the first prerequisite
#$^-> name of all the prerequisites
########################################################################

#directories
SDIR=app/src
ODIR=obj
EDIR=bin
LDIR=lib

#symbols
CC=arm-none-linux-gnueabi-gcc
CFLAGS=-c
LDFLAGS=
LIBS=
Q=@


SOURCES=hello_world.c
OBJECTS=$(patsubst %, $(ODIR)/%, $(SOURCES:.c=.o))
INCLUDE=-Iinc -Iapp/inc -Ihal/inc

#app name
EXECUTABLE=$(EDIR)/hello

all: $(EXECUTABLE)

#generate an executable
$(EXECUTABLE): $(OBJECTS)
		$(Q) $(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

#compile all source files under $(SRC)    
$(ODIR)/%.o: $(SDIR)/%.c
		$(Q) $(CC) $(INCLUDE) $(CFLAGS) $< -o $@

clean: $(OBJECTS) $(EXECUTABLE)
		$(Q) rm -f $^ $(EXECUTABLE)

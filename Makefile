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
SDIR=.
EDIR=bin
LDIR=lib

#symbols
CC=arm-none-linux-gnueabi-gcc
CFLAGS=-c
LDFLAGS=
LIBS=
#By default verbose is off
V=0
V_0=@
V_1=
Q=$(V_$(V))


SOURCES=app/src/runner.c hal/src/lego.c hal/src/lego_ev3_motor.c
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))
INCLUDE=-Iinc -Iapp/inc -Ihal/inc

#app name
EXECUTABLE=$(EDIR)/runner

all: $(EXECUTABLE)

#generate an executable
$(EXECUTABLE): $(OBJECTS)
		$(Q) $(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

#compile all source files under $(SRC)    
%.o: $(SDIR)/%.c
		$(Q) $(CC) $(INCLUDE) $(CFLAGS) $< -o $@

clean: 
		$(Q) rm -f $(OBJECTS) $(EXECUTABLE)

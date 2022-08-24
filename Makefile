CC = gcc

SRCDIR = ./api
INCDIR = ./api
OBJDIR = ./output/linux/obj
LIBDIR = ./output/linux/

OPTIONAL_CFLAGS += -DDEBUG_INFO
CFLAGS = -pipe $(OPTIONAL_CFLAGS) -g -std=gnu99 -Wall -fPIC
INCFLAGS = -I. -I./api -I./timer -I./inc

OBJS = $(OBJDIR)/audioapi.o \
	   $(OBJDIR)/g711.o \
	   $(OBJDIR)/g722_encode.o \
	   $(OBJDIR)/g722_decode.o \
	   $(OBJDIR)/timer.o
			
LIBS = $(LIBDIR)/libaudio.a
$(LIBS): $(OBJS)
	ar rvs $@ $?

audiolib: $(LIBS)

all: 
	$(shell [ ! -d $(OBJDIR) ] && mkdir $(OBJDIR))
	cp ./lib/linux/* ./output/linux/
	make audiolib;
	make actest;

clean:
	rm -f $(OBJS) 
	rm -f $(LIBDIR)/libaudio.a
	make -C audioproject clean;
	
actest:
	make -C audioproject clean;
	make -C audioproject all;
  
$(OBJDIR)/audioapi.o:./api/audioapi.c
	$(CC) -c $(CFLAGS) $(INCFLAGS) ./api/audioapi.c -o $(OBJDIR)/audioapi.o
$(OBJDIR)/g711.o:./audio/g711.c
	$(CC) -c $(CFLAGS) $(INCFLAGS) ./audio/g711.c -o $(OBJDIR)/g711.o
$(OBJDIR)/g722_encode.o:./audio/g722_encode.c
	$(CC) -c $(CFLAGS) $(INCFLAGS) ./audio/g722_encode.c -o $(OBJDIR)/g722_encode.o
$(OBJDIR)/g722_decode.o:./audio/g722_decode.c
	$(CC) -c $(CFLAGS) $(INCFLAGS) ./audio/g722_decode.c -o $(OBJDIR)/g722_decode.o
$(OBJDIR)/timer.o:./timer/timer.cpp
	$(CC) -c $(CFLAGS) $(INCFLAGS) ./timer/timer.cpp -o $(OBJDIR)/timer.o 


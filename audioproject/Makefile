OPTIONAL_CFLAGS += -DWEBRTC_POSIX
CFLAGS = -pipe $(OPTIONAL_CFLAGS) -g -fPIC
INCFLAGS = -I. -I../ 
LIBDIR = ../output/linux/
BINDIR = ../output/linux/
OBJDIR = ../output/linux/obj
LIBFLAGS = -L$(LIBDIR) -laudio -lbcg729 -lopus -lstdc++ -lpthread 
LIBFLAGS += -lm -lz -ldl -lrt 

CC = g++

$(BINDIR)/audioproject.exe:$(OBJDIR)/acdemo.o
	$(CC) -o $(BINDIR)/audioproject.exe  $(OBJDIR)/acdemo.o -L$(LIBDIR) $(LIBFLAGS)

$(OBJDIR)/acdemo.o:./acdemo.c
	$(CC) -c $(CFLAGS) $(INCFLAGS) ./acdemo.c -o $(OBJDIR)/acdemo.o      

all: $(BINDIR)/audioproject.exe

clean:
	rm -f $(OBJDIR)/acdemo.o 
	rm -f $(BINDIR)/audioproject.exe


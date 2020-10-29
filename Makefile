CC = gcc
CFLAGS = -g -Wall -lm
LDFLAGS = -lm
DEPS = clogs.h cdist.h cdata.h cstat.h
OBJFILES = dscstat.o clogs.o cdist.o cdata.o cstat.o
TARGET = dscstat

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) #$(DEPS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~



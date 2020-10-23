CC = gcc
CFLAGS = -g -Wall -lm
LDFLAGS = -lm
DEPS = cdist.h
OBJFILES = dscstat.o cdist.o
TARGET = dscstat

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) #$(DEPS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~



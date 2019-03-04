# the compiler to use
CC=gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS=-g -Wall
  
#files to link:
LFLAGS= 
  
# the name to use for both the target source file, and the output file:
TARGET=bin_editor
  
all:$(TARGET)
	
$(TARGET):$(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LFLAGS)

clean:
	rm -f $(TARGET)

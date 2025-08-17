# Compiler and Flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

# Source Files
SRCDIR = src
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/train.c $(SRCDIR)/vagon.c $(SRCDIR)/materials.c $(SRCDIR)/file_ops.c $(SRCDIR)/utils.c

# Object Files
OBJS = main.o train.o vagon.o materials.o file_ops.o utils.o

# Output Executable
TARGET = program

# Default Target
all: $(TARGET)

# Linking Step
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

# Compilation Step for Each .c File
%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Build
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: all
	./$(TARGET)
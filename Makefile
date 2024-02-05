CC=gcc  #compiler
# TARGET=a.exe #target file name
TARGET=a.out #target file name

all:
	$(CC) test/*.c \
	*.c -o $(TARGET)
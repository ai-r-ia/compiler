# Group Number: 28
# 1. Anishka Singh 2020B3A70816P
# 2. Gautam Jajoo 2020B3A71638P
# 3. Suraj Phalod 2020B3A71959P
# 4. Ria Shekhawat 2020B4A71986P
# 5. Karan Agrawal 2020B4A70830P

CC=gcc  #compiler
# TARGET=a.exe #target file name
TARGET=stage1exe #target file name

all:
	$(CC) test/*.c \
	*.c -o3 $(TARGET) -lm
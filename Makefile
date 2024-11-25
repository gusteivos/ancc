
NAME=ancc

CC=gcc -std=c99 -pedantic -pedantic-errors -g
CCFLAGS=-Wall -Wextra

ifeq ($(OS),Windows_NT)
    OBJ=.obj
    EXE=.exe
	RM=cmd /C .\rm.bat -f -v
else
    OBJ=.o
    EXE=.out
	RM=rm -f -v
endif

SRCFOLDER=./src/

SRCS=$(wildcard $(SRCFOLDER)*.c)
OBJS=$(SRCS:.c=$(OBJ))
LIBS=-lm

$(NAME): $(OBJS)
	$(CC) $(CCFLAGS) $(LIBS) $(OBJS) -o ./$(NAME)$(EXE)

%$(OBJ): %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) ./$(NAME)$(EXE)

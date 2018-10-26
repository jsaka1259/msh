TARGET := msh

SCMN   := common
SCMD   := $(SCMN)/cmd

OBJS   := main.o
OBJS   += $(SCMN)/cmd.o $(SCMN)/getch.o $(SCMN)/parse.o \
          $(SCMN)/shell.o $(SCMN)/utils.o
OBJS   += $(SCMD)/echo.o $(SCMD)/exit.o $(SCMD)/help.o

CC     := gcc
CFLAGS := -Wall
INC    := -I $(SCMN)
RM     := rm

.SUFFIXES: .c .o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INC) -o $@ $(notdir $^)

.c.o:
	$(CC) $(CFLAGS) $(INC) -c $<

.PHONY: clean
clean:
	$(RM) -f $(notdir $(OBJS)) $(TARGET)

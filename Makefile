BIN    := msh

SCMN   := common/
SCMD   := $(SCMN)cmd/

OBJS   := main.o
OBJS   += $(SCMN)cmd.o $(SCMN)getch.o $(SCMN)line.o \
          $(SCMN)parse.o $(SCMN)shell.o $(SCMN)utils.o
OBJS   += $(SCMD)echo.o $(SCMD)exit.o $(SCMD)help.o

CC     := gcc
CFLAGS := -Wall
INC    := -I $(SCMN)
RM     := rm

.SUFFIXES: .c .o

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(INC) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

.PHONY: clean
clean:
	$(RM) -f $(OBJS) $(BIN)

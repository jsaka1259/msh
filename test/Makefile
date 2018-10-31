BIN    := msh_test

SCMN   := ../common/
SCMD   := $(SCMN)cmd/
TCMN   := common_test/
TCMD   := $(TCMN)cmd_test/

OBJS   := test.o
OBJS   += $(TCMN)common_test.o
OBJS   += $(TCMD)echo_test.o
OBJS   += $(SCMN)cmd.o $(SCMN)getch.o $(SCMN)line.o \
          $(SCMN)parse.o $(SCMN)shell.o $(SCMN)utils.o
OBJS   += $(SCMD)echo.o $(SCMD)exit.o $(SCMD)help.o

CC     := gcc
CFLAGS := -Wall
INC    := -I $(SCMN)
INC    += -I $(TCMN)
RM     := rm

.SUFFIXES: .c .o

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(INC) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

.PHONY: clean
clean:
	$(RM) -f $(OBJS) $(BIN)

TARGET := msh

SCMN   := common
SCMD   := $(SCMN)/cmd

OBJS   := main.o
OBJS   += $(SCMN)/cmd.o $(SCMN)/parse.o $(SCMN)/shell.o $(SCMN)/utils.o
OBJS   += $(SCMD)/echo.o $(SCMD)/help.o $(SCMD)/exit.o

CC     := gcc
CFLAGS := -Wall
INC    := -I $(PWD)/$(SCMN)
RM     := rm

.SUFFIXES: .c .o
DEFAULT: all

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INC) -o $@ $(notdir $^)

.c.o:
	$(CC) $(CFLAGS) $(INC) -c $<

.PHONY: clean
clean:
	$(RM) -f $(notdir $(OBJS)) $(TARGET)

SRCDIR  := src
CMNDIR  := $(SRCDIR)/common
CMDDIR  := $(SRCDIR)/cmd

OUTDIR  := build
SRCS    := $(wildcard $(SRCDIR)/*.c)
SRCS    += $(wildcard $(CMNDIR)/*.c)
SRCS    += $(wildcard $(CMDDIR)/*.c)
OBJS    := $(addprefix $(OUTDIR)/,$(patsubst %.c,%.o,$(SRCS)))
BIN     := $(OUTDIR)/msh

CC      := gcc
CFLAGS  := -Wall
RM      := rm

.PHONY: clean rebuild

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OUTDIR)/%.o:%.c
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -rf $(OUTDIR)

rebuild: clean all

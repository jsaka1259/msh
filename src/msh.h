#ifndef _MSH_H_
#define _MSH_H_

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>

#include "cmd/cmd.h"
#include "common/getch.h"
#include "common/utils.h"
#include "line.h"
#include "parse.h"

#define MSH     "msh"
#define VERSION "prototype"
#define PROMPT  "(" MSH "-" VERSION ")$ "
#define USAGE "Usage: %s [-c \'command arg ...\']\n" \
              "Option:\n" \
              "  -c command arg ...: execute COMMAND with ARGs\n" \
              "  -h                : display help\n"

#endif

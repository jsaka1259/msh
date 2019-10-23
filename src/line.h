#ifndef _LINE_H_
#define _LINE_H_

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cmd/cmd.h"
#include "common/getch.h"
#include "common/utils.h"

#define LINE_SIZE 80UL

extern void init_history(void);
extern void delete_history(void);
extern void get_cmdline(char *line);

#endif

#ifndef _PARSE_H_
#define _PARSE_H_

#include <stdint.h>
#include <stdlib.h>

#include "cmd/cmd.h"
#include "common/utils.h"

extern cmd_t *parse_cmd(char *line);
extern int8_t exec_cmd(cmd_t *cmd);
extern void   free_cmd(cmd_t *cmd);

#endif

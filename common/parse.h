#ifndef _PARSE_
#define _PARSE_

extern cmd_t *parse_cmd(char *line);
extern int8_t exec_cmd(cmd_t *cmd);
extern void   free_cmd(cmd_t *cmd);

#endif

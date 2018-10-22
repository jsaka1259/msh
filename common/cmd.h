#ifndef _CMD_
#define _CMD_

#define NCMD    3
#define CMDLEN  256
#define DESCLEN 65536

typedef struct {
	uint32_t argc;
	char   **argv;
} cmd_t;

extern int8_t echo(uint32_t argc, char **argv);
extern int8_t help(uint32_t argc, char **argv);
extern int8_t quit(uint32_t argc, char **argv);

extern const char cmds[NCMD][CMDLEN];
extern const char cmd_desc[NCMD][DESCLEN];
extern const int8_t (*cmd_handler[NCMD])(uint32_t argc, char **argv);

#endif

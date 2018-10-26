#ifndef _CMD_
#define _CMD_

#define NCMD     3
#define CMDLEN   256
#define USAGELEN 256
#define DESCLEN  65536
#define NOT_FOUND "%s: not found\n"

#define RET_NORMAL        0x00
#define RET_NOT_FOUND     0x01
#define RET_NORMAL_EXIT   0xFF
#define RET_ABNORMAL_EXIT 0xFE

#define RET_EXIT_MASK  0xFE
#define CHECK_RET_EXIT(ret) ((ret & RET_EXIT_MASK) == RET_EXIT_MASK)

typedef struct {
	uint32_t argc;
	char   **argv;
} cmd_t;

extern int8_t msh_echo(uint32_t argc, char **argv);
extern int8_t msh_exit(uint32_t argc, char **argv);
extern int8_t msh_help(uint32_t argc, char **argv);

extern cmd_t *cmd;
extern const char cmds[NCMD][CMDLEN];
extern const char cmd_usage[NCMD][USAGELEN];
extern const char cmd_desc[NCMD][DESCLEN];
extern const int8_t (*cmd_handler[NCMD])(uint32_t argc, char **argv);

#endif

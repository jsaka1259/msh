#include <common.h>

const char cmds[NCMD][CMDLEN] = {
	"echo",
	"help",
	"quit",
};

const char cmd_desc[NCMD][DESCLEN] = {
	"echo: echo arg...\n"
	"      display arg",
	"help: help\n"
	"      display command list and description",
	"quit: quit\n"
	"      exit shell",
};

const int8_t (*cmd_handler[NCMD])(uint32_t argc, char **argv) = {
	echo,
	help,
	quit,
};

#include <common.h>

const int8_t (*cmd_handler[NCMD])(uint32_t argc, char **argv) = {
	msh_echo,
	msh_exit,
	msh_help,
};

const char cmds[NCMD][CMDLEN] = {
	"echo",
	"exit",
	"help",
};

const char cmd_usage[NCMD][USAGELEN] = {
	"echo [arg ...]",
	"exit [n]",
	"help [pattern ...]",
};

const char cmd_desc[NCMD][DESCLEN] = {
	"    Write arguments to the standard output.\n"
	 "\n"
	"    Display the ARGs, separated by a single space character and followed by a\n"
	"    newline, on the standard output."
	,
	"    Exit the shell.\n"
	"\n"
	"    Exits the shell with a status of N.  If N is omitted, the exit status\n"
	"    is that of the last command executed."
	,
	"    Display information about builtin commands.\n"
	"\n"
	"    Displays brief summaries of builtin commands.  If PATTERN is\n"
	"    specified, gives detailed help on all commands matching PATTERN,\n"
	"    otherwise the list of help topics is printed.\n"
	"\n"
	"    Arguments:\n"
	"      PATTERN	Pattern specifiying a help topic"
	,
};

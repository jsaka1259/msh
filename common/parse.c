#include <common.h>

void
get_cmd(char *line, const size_t size)
{
	size_t i;
	char c;
	if (2 > size) {
		fprintf(stderr, "\rSystem Error: line buffer size is invalid [%ld]\n",
		        size);
		exit(1);
	}
	i = 0;
	while ((c = getch()) != 0x0a) {
		if (i == 0 && c == 0x04) {
			fputc('\n', stdout);
			fflush(stdout);
			if (cmd != NULL) {
				free_cmd(cmd);
			}
			exit(0);
		}
		else if (i > 0 && c == 0x7F) {
			i--;
			fputs("\b \b", stdout);
			fflush(stdout);
		}
		else if (0x20 <= c && 0x7e >= c) {
			fputc(c, stdout);
			fflush(stdout);
			if (size-1 > i) {
				line[i] = c;
				i++;
			}
		}
		else ;
	}
	line[i] = 0x00;
	fputc('\n', stdout);
	fflush(stdout);
}

cmd_t*
parse_cmd(char *line)
{
	char    *p    = line;
	uint32_t capa = 8;
	cmd_t   *cmd;

	cmd       = xmalloc(sizeof(cmd_t));
	cmd->argc = 0;
	cmd->argv = xmalloc(sizeof(char*) * capa);

	while (*p) {
		while (*p && 0x20 == *p) {
			*p++ = 0x00;
		}
		if (*p) {
			if (capa <= cmd->argc + 1) {
				capa *= 2;
				cmd->argv  = xrealloc(cmd->argv, capa);
			}
			cmd->argv[cmd->argc] = p;
			cmd->argc++;
		}
		while (*p && 0x20 != *p) {
			p++;
		}
	}
	cmd->argv[cmd->argc] = 0x00;
	return cmd;
}

int8_t
exec_cmd(cmd_t *cmd)
{
	uint32_t i;

	for (i = 0; i < NCMD; i++) {
		if (strcmp(cmd->argv[0], cmds[i]) == 0) {
			return cmd_handler[i](cmd->argc, cmd->argv);
		}
	}
	return RET_NOT_FOUND;
}

void
free_cmd(cmd_t *cmd)
{
	free(cmd->argv);
	free(cmd);
}

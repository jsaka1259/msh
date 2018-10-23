#include <common.h>

void
get_cmd(char *line, size_t size)
{
	if ((fgets(line, size, stdin)) == NULL) {
		fprintf(stdout, "\n");
		exit(0);
	}
	if (line[strlen(line) - 1] == 0x0A)
		line[strlen(line) - 1] = 0x00;
	else
		while (fgetc(stdin) != 0x0A) ;
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
			cmd_handler[i](cmd->argc, cmd->argv);
			return 0;
		}
	}
	return 1;
}

void
free_cmd(cmd_t *cmd)
{
	free(cmd->argv);
	free(cmd);
}

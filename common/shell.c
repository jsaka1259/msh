#include <common.h>

#define USAGE "Usage: %s [-c \'command arg ...\']\n" \
              "Option:\n" \
              "  -c command arg ...: execute COMMAND with ARGs\n" \
              "  -h                : display help\n"

int8_t
shell(int argc, char **argv)
{
	int     opt;
	uint8_t copt = 0;
	int8_t  ret;
	char   *line;

	while ((opt = getopt(argc, argv, "c:h")) != -1) {
		switch (opt) {
			case 'c':
				copt = 1;
				line = xmalloc(sizeof(char*) * LINE_SIZE);
				strncpy(line, optarg, LINE_SIZE);
				break;
			case 'h':
			case '?':
			default:
				fprintf(stderr, USAGE, argv[0]);
				exit(1);
		}
	}

	if (copt) {
		cmd = parse_cmd(line);
		if (cmd->argc > 0) {
			ret = exec_cmd(cmd);
			if (strcmp(EXIT_CMD, cmd->argv[0]) == 0) {
				free(line);
				free_cmd(cmd);
				exit(ret);
			}
			else if (ret == RET_NOT_FOUND) {
				fprintf(stdout, NOT_FOUND, cmd->argv[0]);
				fflush(stdout);
			}
		}
		free(line);
		free_cmd(cmd);
	}
	else {
		init_history();
		while (1) {
			fprintf(stdout, "%s", PROMPT);
			fflush(stdout);
			cmd = parse_cmd(get_cmd());
			if (cmd->argc > 0) {
				ret = exec_cmd(cmd);
				if (strcmp(EXIT_CMD, cmd->argv[0]) == 0) {
					free_cmd(cmd);
					delete_history();
					return ret;
				}
				else if (ret == RET_NOT_FOUND) {
					fprintf(stdout, NOT_FOUND, cmd->argv[0]);
					fflush(stdout);
				}
			}
			free_cmd(cmd);
		}
	}

	return 0;
}

#include <common.h>

#define LINE_SIZE 80
#define MSH       "msh"
#define VERSION   "0.0.2"
#define PROMPT    "(" MSH "-" VERSION ")$ "
#define USAGE     "Usage: %s [-c \'command arg ...\']\n" \
                  "Option:\n" \
									"  -c command arg ...: execute COMMAND with ARGs\n" \
									"  -h                : display help\n"

int8_t
shell(int argc, char **argv)
{
	int     opt;
	uint8_t copt = 0;
	char    line[LINE_SIZE];
	cmd_t  *cmd;

	while ((opt = getopt(argc, argv, "c:h")) != -1) {
		switch (opt) {
			case 'c':
				copt = 1;
				strncpy(line, optarg, sizeof(line));
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
			if (exec_cmd(cmd)) {
				fprintf(stdout, NOT_FOUND, cmd->argv[0]);
				fflush(stdout);
			}
		}
		free(cmd);
	}
	else {
		while (1) {
			fprintf(stdout, "%s", PROMPT);
			fflush(stdout);
			get_cmd(line, sizeof(line));
			cmd = parse_cmd(line);
			if (cmd->argc > 0) {
				if (exec_cmd(cmd)) {
					fprintf(stdout, NOT_FOUND, cmd->argv[0]);
					fflush(stdout);
				}
			}
			free_cmd(cmd);
		}
	}

	return 0;
}

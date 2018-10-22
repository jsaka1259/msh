#include <common.h>

int8_t
msh_help(uint32_t argc, char **argv)
{
	uint32_t i, j;

	if (argc <= 1) {
		for (i = 0; i < NCMD; i++ ) {
			fprintf(stdout, "%s\n", cmd_usage[i]);
		}
	}
	else {
		int8_t found = 0;
		for (i = 1; i < argc; i++) {
			for (j = 0; j < NCMD; j++) {
				if (strcmp(argv[i], cmds[j]) == 0) {
					fprintf(stdout, "%s: %s\n", cmds[j], cmd_usage[j]);
					fprintf(stdout, "%s\n", cmd_desc[j]);
					found = 1;
				}
			}
			if (!found)
				fprintf(stdout, NOT_FOUND, argv[i]);
		}
	}

	fflush(stdout);
	return 0;
}

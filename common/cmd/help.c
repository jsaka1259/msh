#include <common.h>

int8_t help(uint32_t argc, char **argv)
{
	uint32_t i;
	fprintf(stdout, "[CMD] [Description]\n");
	for (i = 0; i < NCMD; i++ )
		fprintf(stdout, "%s\n", cmd_desc[i]);
	fflush(stdout);
	return 0;
}

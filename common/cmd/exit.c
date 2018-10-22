#include <common.h>

int8_t
msh_exit(uint32_t argc, char **argv)
{
	if (argc == 0)
		exit(0);
	else
		exit(atoi(argv[0]));
}

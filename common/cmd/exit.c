#include <common.h>

int8_t
msh_exit(uint32_t argc, char **argv)
{
	if (1 >= argc)
		return RET_NORMAL_EXIT;
	else {
		switch (atoi(argv[1])) {
			case 0:
				return RET_NORMAL_EXIT;
			default:
				return RET_ABNORMAL_EXIT;
		}
	}
}

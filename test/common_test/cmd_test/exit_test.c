#include <common_test.h>

#define TCASE 5
#define CAPA  8

static uint32_t in_argc[TCASE] = {
	0,
	1,
	2,
	2,
	2,
};

static char in_argv[TCASE][CAPA][LINE_SIZE] = {
	{"exit"},
	{"exit"},
	{"exit", "0"},
	{"exit", "1"},
	{"exit", "-1"},
};

static int8_t ex[TCASE] = {
	0,
	0,
	0,
	1,
	-1,
};

int8_t
msh_exit_test(int8_t d)
{
	uint32_t i, j;
	char *p[TCASE][CAPA];
	int8_t ret;
	uint8_t result;
	uint8_t all_result = 0;

	if (d)
		fprintf(stderr, "===> %s <===\n", __FUNCTION__);

	for (i = 0; i < TCASE; i++) {
		for (j = 0; j < CAPA; j++)
			p[i][j] = in_argv[i][j];
		ret = msh_exit(in_argc[i], (char**)p[i]);
		fflush(stdout);
		
		result = 0;
		if (ex[i] != ret) {
			result = 1;
			if (0 == all_result)
				all_result = 1;
		}

		if (d) {
			fprintf(stderr, "<%s case: %d> ", __FUNCTION__, i);
			if (0 == result)
				fprintf(stderr, "SUCCESS\n");
			else
				fprintf(stderr, "FAILURE\n");
			fprintf(stderr, "in : argc     = %d\n", in_argc[i]);
			for (j = 0; j < in_argc[i]; j++)
				fprintf(stderr, "     argv[%2d] = \"%s\"\n", j, in_argv[i][j]);
			fprintf(stderr, "ex : ret      = %d\n", ex[i]);
			fprintf(stderr, "out: ret      = %d\n", ret);
		}
	}

	if (d) {
		if (0 == all_result)
			fprintf(stderr, ">>>> SUCCESS <<<<\n\n");
		else
			fprintf(stderr, ">>>> FAILURE <<<<\n\n");
	}

	return all_result;
}

#include <common_test.h>

#define TCASE 4
#define CAPA  8

uint32_t in_argc[TCASE] = {
	0,
	1,
	2,
	3,
};

char in_argv[TCASE][CAPA][LINE_SIZE] = {
	{"echo"},
	{"echo"},
	{"echo", "abc"},
	{"echo", "abc", "def"},
};

typedef struct {
	int8_t  ret;
	char   *out;
} ret_t;

ret_t ex[TCASE] = {
	{0, "\n"},
	{0, "\n"},
	{0, "abc\n"},
	{0, "abc def\n"},
};

int8_t
msh_echo_test(int8_t d)
{
	uint32_t i, j;
	char *p[TCASE][CAPA];
	int8_t ret;
	uint8_t result;
	uint8_t all_result = 0;

	set_stdout2buf();

	if (d)
		fprintf(stderr, "===> %s <===\n", __FUNCTION__);

	for (i = 0; i < TCASE; i++) {
		for (j = 0; j < CAPA; j++)
			p[i][j] = in_argv[i][j];
		ret = msh_echo(in_argc[i], (char**)p[i]);
		fflush(stdout);
		
		result = 0;
		if (ex[i].ret != ret) {
			result = 1;
			if (0 == all_result)
				all_result = 1;
		}
		else {
			for (j = 1; j < in_argc[i]; j++) {
				if (0 != strcmp(ex[i].out, out_buf)) {
					result = 1;
					if (0 == all_result)
						all_result = 1;
					break;
				}
			}
		}

		if (d) {
			fprintf(stderr, "<test case: %d> ", i);
			if (0 == result)
				fprintf(stderr, "SUCCESS\n");
			else
				fprintf(stderr, "FAILURE\n");

			fprintf(stderr, "in : argc     = %d\n", in_argc[i]);
			for (j = 0; j < in_argc[i]; j++)
				fprintf(stderr, "     argv[%2d] = \"%s\"\n", j, in_argv[i][j]);
			fprintf(stderr, "ex : ret      = %d\n", ex[i].ret);
			fprintf(stderr, "     out      = \"%s\"\n", ex[i].out);
			fprintf(stderr, "out: ret      = %d\n", ret);
			fprintf(stderr, "     out      = \"%s\"\n", out_buf);
		}
	}

	if (d) {
		if (0 == all_result)
			fprintf(stderr, ">>>> SUCCESS <<<<\n\n");
		else
			fprintf(stderr, ">>>> FAILURE <<<<\n\n");
	}

	unset_stdout2buf();

	return all_result;
}

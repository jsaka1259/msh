#include <common_test.h>

#define TCASE   6
#define CAPA    8
#define OUT_LEN (NCMD * CMDLEN) + (NCMD * USAGELEN) + (NCMD * DESCLEN) + 4

static uint32_t in_argc[TCASE] = {
	0,
	1,
	2,
	2,
	2,
	4,
};

static char in_argv[TCASE][CAPA][LINE_SIZE] = {
	{"help"},
	{"help"},
	{"help", "echo"},
	{"help", "exit"},
	{"help", "help"},
	{"help", "echo", "exit", "help"},
};

typedef struct {
	int8_t  ret;
	char    out[OUT_LEN];
} ret_t;

static ret_t ex[TCASE] = {
	{0, ""},
	{0, ""},
	{0, ""},
	{0, ""},
	{0, ""},
	{0, ""},
};

int8_t
msh_help_test(int8_t d)
{
	uint32_t i, j;
	char *p[TCASE][CAPA];
	int8_t ret;
	uint8_t result;
	uint8_t all_result = 0;

	strncpy(ex[0].out, cmd_usage[0], OUT_LEN);
	strncat(ex[0].out, "\n", OUT_LEN);
	strncat(ex[0].out, cmd_usage[1], OUT_LEN);
	strncat(ex[0].out, "\n", OUT_LEN);
	strncat(ex[0].out, cmd_usage[2], OUT_LEN);
	strncat(ex[0].out, "\n", OUT_LEN);

	strncpy(ex[1].out, ex[0].out, OUT_LEN);

	strncpy(ex[2].out, cmds[0], OUT_LEN);
	strncat(ex[2].out, ": ", OUT_LEN);
	strncat(ex[2].out, cmd_usage[0], OUT_LEN);
	strncat(ex[2].out, "\n", OUT_LEN);
	strncat(ex[2].out, cmd_desc[0], OUT_LEN);
	strncat(ex[2].out, "\n", OUT_LEN);

	strncpy(ex[3].out, cmds[1], OUT_LEN);
	strncat(ex[3].out, ": ", OUT_LEN);
	strncat(ex[3].out, cmd_usage[1], OUT_LEN);
	strncat(ex[3].out, "\n", OUT_LEN);
	strncat(ex[3].out, cmd_desc[1], OUT_LEN);
	strncat(ex[3].out, "\n", OUT_LEN);

	strncpy(ex[4].out, cmds[2], OUT_LEN);
	strncat(ex[4].out, ": ", OUT_LEN);
	strncat(ex[4].out, cmd_usage[2], OUT_LEN);
	strncat(ex[4].out, "\n", OUT_LEN);
	strncat(ex[4].out, cmd_desc[2], OUT_LEN);
	strncat(ex[4].out, "\n", OUT_LEN);

	strncpy(ex[5].out, ex[2].out, OUT_LEN);
	strncat(ex[5].out, ex[3].out, OUT_LEN);
	strncat(ex[5].out, ex[4].out, OUT_LEN);

	if (d)
		fprintf(stderr, "===> %s <===\n", __FUNCTION__);

	set_stdout2buf();

	for (i = 0; i < TCASE; i++) {
		clear_out_buf();

		for (j = 0; j < CAPA; j++)
			p[i][j] = in_argv[i][j];
		
		ret = msh_help(in_argc[i], (char**)p[i]);
		fflush(stdout);

		result = 0;
		if (ex[i].ret != ret) {
			result = 1;
			if (0 == all_result)
				all_result = 1;
		}
		else {
			if (0 != strcmp(ex[i].out, out_buf)) {
				result = 1;
				if (0 == all_result)
					all_result = 1;
			}
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
			fprintf(stderr, "ex : ret      = %d\n", ex[i].ret);
			fprintf(stderr, "     out      = \n\"%s\"\n", ex[i].out);
			fprintf(stderr, "out: ret      = %d\n", ret);
			fprintf(stderr, "     out      = \n\"%s\"\n", out_buf);
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

#include <common_test.h>

#define TCASE   7
#define CAPA    8
#define OUT_LEN (NCMD * CMDLEN) + (NCMD * USAGELEN) + (NCMD * DESCLEN) + 4

static uint32_t in_argc[TCASE] = {
	0,
	1,
	2,
	2,
	2,
	4,
	2,
};

static char in_argv[TCASE][CAPA][LINE_SIZE] = {
	{"help"},
	{"help"},
	{"help", "echo"},
	{"help", "exit"},
	{"help", "help"},
	{"help", "echo", "exit", "help"},
	{"help", "xyz"},
};

typedef struct {
	int8_t  ret;
	char   *out;
} ret_t;

static ret_t ex[TCASE] = {
	{0, },
	{0, },
	{0, },
	{0, },
	{0, },
	{0, },
	{0, },
};

static void
init_ex(void)
{
	ex[0].out = xmalloc(sizeof(char*) * OUT_LEN + 1);
	strncpy(ex[0].out, cmd_usage[0], OUT_LEN);
	strncat(ex[0].out, "\n", OUT_LEN);
	strncat(ex[0].out, cmd_usage[1], OUT_LEN);
	strncat(ex[0].out, "\n", OUT_LEN);
	strncat(ex[0].out, cmd_usage[2], OUT_LEN);
	strncat(ex[0].out, "\n", OUT_LEN);

	ex[1].out = ex[0].out;

	ex[2].out = xmalloc(sizeof(char*) * OUT_LEN + 1);
	strncpy(ex[2].out, cmds[0], OUT_LEN);
	strncat(ex[2].out, ": ", OUT_LEN);
	strncat(ex[2].out, cmd_usage[0], OUT_LEN);
	strncat(ex[2].out, "\n", OUT_LEN);
	strncat(ex[2].out, cmd_desc[0], OUT_LEN);
	strncat(ex[2].out, "\n", OUT_LEN);

	ex[3].out = xmalloc(sizeof(char*) * OUT_LEN + 1);
	strncpy(ex[3].out, cmds[1], OUT_LEN);
	strncat(ex[3].out, ": ", OUT_LEN);
	strncat(ex[3].out, cmd_usage[1], OUT_LEN);
	strncat(ex[3].out, "\n", OUT_LEN);
	strncat(ex[3].out, cmd_desc[1], OUT_LEN);
	strncat(ex[3].out, "\n", OUT_LEN);

	ex[4].out = xmalloc(sizeof(char*) * OUT_LEN + 1);
	strncpy(ex[4].out, cmds[2], OUT_LEN);
	strncat(ex[4].out, ": ", OUT_LEN);
	strncat(ex[4].out, cmd_usage[2], OUT_LEN);
	strncat(ex[4].out, "\n", OUT_LEN);
	strncat(ex[4].out, cmd_desc[2], OUT_LEN);
	strncat(ex[4].out, "\n", OUT_LEN);

	ex[5].out = xmalloc(sizeof(char*) * OUT_LEN + 1);
	strncpy(ex[5].out, ex[2].out, OUT_LEN);
	strncat(ex[5].out, ex[3].out, OUT_LEN);
	strncat(ex[5].out, ex[4].out, OUT_LEN);

	ex[6].out = xmalloc(sizeof(char*) * OUT_LEN + 1);
	strncpy(ex[6].out, in_argv[6][1], OUT_LEN);
	strncat(ex[6].out, ": not found\n", OUT_LEN);
}

static void
free_ex(void)
{
	free(ex[0].out);
	free(ex[2].out);
	free(ex[3].out);
	free(ex[4].out);
	free(ex[5].out);
	free(ex[6].out);
}

uint64_t
msh_help_test(int8_t d)
{
	uint32_t i, j;
	char *p[TCASE][CAPA];
	int8_t ret;
	uint8_t result;
	uint64_t nfail = 0;

	init_ex();
	set_stdout2buf();

	if (d)
		fprintf(stderr, "===> %s <===\n", __FUNCTION__);

	for (i = 0; i < TCASE; i++) {
		clear_out_buf();

		for (j = 0; j < CAPA; j++)
			p[i][j] = in_argv[i][j];

		ret = msh_help(in_argc[i], (char**)p[i]);
		fflush(stdout);

		result = 0;
		if (ex[i].ret != ret) {
			result = 1;
			nfail++;
		}
		if (0 != strcmp(ex[i].out, out_buf)) {
			result = 1;
			nfail++;
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
		if (0 == nfail)
			fprintf(stderr, ">>>> SUCCESS <<<<\n\n");
		else
			fprintf(stderr, ">>>> FAILURE [%lu] <<<<\n\n", nfail);
	}

	unset_stdout2buf();
	free_ex();

	return nfail;
}

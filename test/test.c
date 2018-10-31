#include <common_test.h>

int
main(int argc, char **argv)
{
	int opt;
	int8_t dopt = 0;
	uint64_t ret = 0;
	while (-1 != (opt = getopt(argc, argv, "dh"))) {
		switch (opt) {
			case 'd':
				dopt = 1;
				break;
			case 'h':
			case '?':
			default:
				fprintf(stderr, "Usage: %s [-dh]\n", argv[0]);
				exit(0);
		}
	}

	ret += msh_echo_test(dopt);

	if (ret == 0)
		fprintf(stdout, "ALL SUCCESS\n");
	else
		fprintf(stdout, "FAILURE\n");
	return 0;
}

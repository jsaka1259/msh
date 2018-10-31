#include <common_test.h>

#define OUT_BUF_SIZE 8192

int fd1;
int fd2;
char *out_buf;

void
set_stdout2buf(void)
{
	out_buf = malloc(sizeof(char*) * OUT_BUF_SIZE);
	setvbuf(stdout, out_buf, _IOFBF, sizeof(char*) * OUT_BUF_SIZE);
	fd1 = dup(stdout->_fileno);
	fd2 = open("/dev/null", O_WRONLY);
	dup2(fd2, stdout->_fileno);
}

void
unset_stdout2buf(void)
{
	setvbuf(stdout, NULL, _IOFBF, BUFSIZ);
	dup2(fd1, stdout->_fileno);
	close(fd2);
	free(out_buf);
}

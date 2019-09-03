#include <common_test.h>

#define OUT_BUF_SIZE 8192

int fd1;
int fd2;
char *out_buf = NULL;

void clear_out_buf(void)
{
  if (NULL == out_buf)
    return;
  memset(out_buf, 0x00, OUT_BUF_SIZE);
}

void set_stdout2buf(void)
{
  out_buf = malloc(sizeof(char*) * OUT_BUF_SIZE);
  if (NULL == out_buf) {
    perror("set_stdout2buf");
    exit(1);
  }
  fd1 = dup(stdout->_fileno);
  fd2 = open("/dev/null", O_WRONLY);
  dup2(fd2, stdout->_fileno);
  setvbuf(stdout, out_buf, _IOFBF, sizeof(char*) * OUT_BUF_SIZE);
  fprintf(stdout, "\n");
  fflush(stdout);
}

void unset_stdout2buf(void)
{
  fflush(stdout);
  setvbuf(stdout, NULL, _IOFBF, BUFSIZ);
  dup2(fd1, stdout->_fileno);
  close(fd2);
  clear_out_buf();
  free(out_buf);
  out_buf = NULL;
}

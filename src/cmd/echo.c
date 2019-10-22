#include "cmd.h"

int8_t msh_echo(uint32_t argc, char **argv) {
  uint32_t i;

  for (i = 1; i < argc; i++)
    fprintf(stdout,
        "%s%.*s",
        argv[i],
        (argc != 1 && i != argc - 1),
        " ");

  fprintf(stdout, "\n");
  fflush(stdout);

  return RET_NORMAL;
}

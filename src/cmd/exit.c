#include "cmd.h"

int8_t msh_exit(uint32_t argc, char **argv) {
  if (1 >= argc)
    return 0;
  else
    return atoi(argv[1]);
}

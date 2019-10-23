#include "cmd.h"

int8_t msh_help(uint32_t argc, char **argv) {
  uint32_t i, j;
  int8_t found;

  if (1 >= argc) {
    for (i = 0; i < NCMD; i++ ) {
      fprintf(stdout, "\e[33m");
      fprintf(stdout, "%s\n", cmd_usage[i]);
      fprintf(stdout, "\e[m");
    }
  } else {
    for (i = 1; i < argc; i++) {
      found = 0;

      for (j = 0; j < NCMD; j++) {
        if (strcmp(argv[i], cmds[j]) == 0) {
          fprintf(stdout, "\e[33m");
          fprintf(stdout, "%s: %s\n", cmds[j], cmd_usage[j]);
          fprintf(stdout, "%s\n", cmd_desc[j]);
          fprintf(stdout, "\e[m");

          found = 1;
        }
      }
      if (found == 0)
        fprintf(stdout, NOT_FOUND, argv[i]);
    }
  }

  fflush(stdout);

  return RET_NORMAL;
}

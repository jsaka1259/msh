#ifndef _COMMON_TEST_H_
#define _COMMON_TEST_H_

#include <common.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "cmd_test.h"

extern char *out_buf;
extern void clear_out_buf(void);
extern void set_stdout2buf(void);
extern void unset_stdout2buf(void);

#endif

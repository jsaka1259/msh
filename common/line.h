#ifndef _LINE_H_
#define _LINE_H_

#define LINE_SIZE 80UL

extern void init_history(void);
extern void delete_history(void);
extern char *get_cmd(void);

#endif

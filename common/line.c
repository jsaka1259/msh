#include <common.h>

char *line;

char*
get_line(void)
{
	size_t i;
	char   c;
	line = xmalloc(sizeof(char*) * LINE_SIZE);
	if (2 > LINE_SIZE) {
		fprintf(stderr, "\rSystem Error: line buffer size is invalid [%lu]\n",
		        LINE_SIZE);
		if (cmd != NULL) {
			free_cmd(cmd);
		}
		free(line);
		exit(1);
	}
	i = 0;
	while ((c = getch()) != 0x0a) {
		if (i == 0 && c == 0x04) {
			fputc('\n', stdout);
			fflush(stdout);
			if (cmd != NULL) {
				free_cmd(cmd);
			}
			free(line);
			exit(0);
		}
		else if (i > 0 && c == 0x7F) {
			i--;
			fputs("\b \b", stdout);
			fflush(stdout);
		}
		else if (0x20 <= c && 0x7e >= c) {
			fputc(c, stdout);
			fflush(stdout);
			if (LINE_SIZE - 2 > i) {
				line[i] = c;
				i++;
			}
		}
		else ;
	}
	line[i] = 0x00;
	fputc('\n', stdout);
	fflush(stdout);
	return line;
}

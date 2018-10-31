#include <common.h>

#define LIST_SIZE 8

typedef struct _node_t {
	char *data;
	struct _node_t *prev;
	struct _node_t *next;
} node_t;
static node_t *head;
static node_t *tail;
static char *line;

void
init_history(void)
{
	head = NULL;
	tail = NULL;
}

static node_t*
create_node(char *data, node_t *prev, node_t *next)
{
	node_t *p;
	p = xmalloc(sizeof(node_t));
	p->data = xmalloc(sizeof(char*) * LINE_SIZE);
	strncpy(p->data, data, LINE_SIZE);
	p->prev = prev;
	p->next = next;
	return p;
}

static int8_t
delete_head_node(void)
{
	node_t *p;
	if (NULL == head)
		return 1;
	p = head->next;
	free(head->data);
	free(head);
	if (NULL != p)
		p->prev = NULL;
	head = p;
	return 0;
}

void
delete_history(void)
{
	node_t *p;
	p = head;
	while (NULL != head) {
		p = head->next;
		free(head->data);
		free(head);
		head = p;
	}
}

static void
append_history(char *data)
{
	static uint8_t size = 0;
	node_t *p;
	if (NULL == data || 0x00 == data[0])
		return;
	if (size == LIST_SIZE)
		delete_head_node();
	p = create_node(data, NULL, NULL);
	if (NULL == tail)
		head = p;
	else {
		p->prev = tail;
		tail->next = p;
	}
	tail = p;
	size += ((uint8_t)(size - LIST_SIZE) >> 7);
}


static char*
get_line(void)
{
	node_t *p;
	char c;
	size_t len;
	if (2 > LINE_SIZE) {
		len = strlen(PROMPT);
		while (0 < len) {
			len--;
			fputs("\b \b", stdout);
		}
		fflush(stdout);
		fprintf(stderr, "System Error: line buffer size is invalid [%lu]\n",
		        LINE_SIZE);
		fflush(stdout);
		delete_history();
		free_cmd(cmd);
		exit(1);
	}
	p = NULL;
	len = 0;
	line = xmalloc(sizeof(char*) * LINE_SIZE);
	while (0x0a != (c = getch())) {
		if (0 == len && 0x04 == c) {
			free(line);
			delete_history();
			free_cmd(cmd);
			fputc('\n', stdout);
			fflush(stdout);
			exit(0);
		}
		if (0x1b == c && 0x5b == getch()) {
			if (0x41 == (c = getch())) {
				if (NULL == tail)
					continue;
				if (NULL == p)
					p = tail;
				else {
					if (NULL == p->prev)
						continue;
					p = p->prev;
				}
			}
			else if (0x42 == c) {
				if (NULL == p)
					continue;
				if (NULL == p->next) {
					p = NULL;
					line[0] = 0x00;
					while (0 < len) {
						len--;
						fputs("\b \b", stdout);
					}
					fflush(stdout);
					continue;
				}
				p = p->next;
			}
			else
				continue;
			while (0 < len) {
				len--;
				fputs("\b \b", stdout);
			}
			fflush(stdout);
			strncpy(line, p->data, LINE_SIZE);
			len = strnlen(line, LINE_SIZE);
			fputs(line, stdout);
			fflush(stdout);
		}
		else if (0 < len && 0x7f == c) {
			len--;
			line[len] = 0x00;
			fputs("\b \b", stdout);
			fflush(stdout);
		}
		else if (0x20 <= c && 0x7e >= c) {
			fputc(c, stdout);
			fflush(stdout);
			if (LINE_SIZE - 2 > len) {
				line[len] = c;
				line[len+1] = 0x00;
				len++;
			}
		}
		else ;
	}
	fputc('\n', stdout);
	fflush(stdout);
	return line;
}

char*
get_cmd(void)
{
	char *p;
	p = get_line();
	append_history(p);
	return p;
}

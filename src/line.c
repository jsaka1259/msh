#include "line.h"

#define LIST_SIZE 8

typedef struct _node_t {
  char *data;
  struct _node_t *prev;
  struct _node_t *next;
} node_t;
static node_t *head;
static node_t *tail;

void init_history(void) {
  head = NULL;
  tail = NULL;
}

static node_t *create_node(char *data, node_t *prev, node_t *next) {
  node_t *p;

  p       = xmalloc(sizeof(node_t));
  p->data = xmalloc(sizeof(char*) * LINE_SIZE);

  strncpy(p->data, data, LINE_SIZE);

  p->prev = prev;
  p->next = next;

  return p;
}

static int8_t delete_head_node(void) {
  node_t *p;

  if (head == NULL)
    return 1;

  p = head->next;

  free(head->data);
  free(head);

  if (p != NULL)
    p->prev = NULL;

  head = p;

  return 0;
}

void delete_history(void) {
  node_t *p;

  p = head;

  while (head != NULL) {
    p = head->next;

    free(head->data);
    free(head);

    head = p;
  }
}

static void append_history(char *data) {
  static uint8_t size = 0;
  node_t        *p;

  if (data == NULL || data[0] == 0)
    return;

  if (size == LIST_SIZE)
    delete_head_node();

  p = create_node(data, NULL, NULL);

  if (tail == NULL)
    head = p;
  else {
    p->prev    = tail;
    tail->next = p;
  }

  tail = p;
  size += ((uint8_t)(size - LIST_SIZE) >> 7);
}

static void get_line(char *line) {
  char    c;
  node_t *p  = NULL;
  size_t  len = 0;

  if (line == NULL) {
    fprintf(stderr, "\e[31;1mline buffer is NULL\e[m\n");
    exit(1);
  }

  while (0x0a != (c = getch())) {
    if (len == 0 && c == 0x04) {
      strcpy(line, EXIT_CMD);
      break;
    }

    if (c == 0x1b && getch() == 0x5b) {
      if ((c = getch()) == 0x41) {
        if (tail == NULL)
          continue;
        if (p == NULL)
          p = tail;
        else {
          if (p->prev == NULL)
            continue;
          p = p->prev;
        }
      } else if (c == 0x42) {
        if (p == NULL)
          continue;
        if (p->next == NULL) {
          p       = NULL;
          line[0] = 0;
          while (len > 0) {
            len--;
            fputs("\b \b", stdout);
          }
          fflush(stdout);
          continue;
        }
        p = p->next;
      } else
        continue;
      while (len > 0) {
        len--;
        fputs("\b \b", stdout);
      }
      fflush(stdout);

      strncpy(line, p->data, LINE_SIZE);
      len = strlen(line);

      fputs(line, stdout);
      fflush(stdout);
    } else if (len > 0 && c == 0x7f) {
      len--;
      line[len] = 0;

      fputs("\b \b", stdout);
      fflush(stdout);
    } else if (c >= 0x20 && c <= 0x7e) {
      fputc(c, stdout);
      fflush(stdout);

      if (len < LINE_SIZE - 2) {
        line[len]     = c;
        line[len + 1] = 0;
        len++;
      }
    }
  }

  fputc('\n', stdout);
  fflush(stdout);
}

void get_cmdline(char *line) {
  if (line == NULL) {
    fprintf(stderr, "\e[31;1mline buffer is NULL\e[m\n");
    exit(1);
  }

  get_line(line);
  append_history(line);
}

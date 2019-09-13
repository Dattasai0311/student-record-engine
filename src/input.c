#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"


int read_line(char *buf, size_t size) {
if (!fgets(buf, size, stdin)) return -1;
/* Trim trailing newline for easier string handling. */
buf[strcspn(buf, "\n")] = '\0';
return 0;
}


int read_uint(const char *prompt, uint32_t *out) {
char buf[32];
printf("%s", prompt);
if (read_line(buf, sizeof(buf)) != 0) return -1;


char *end;
long val = strtol(buf, &end, 10);
if (*end != '\0' || val < 0) return -1;


/* Cast only after validation. */
*out = (uint32_t)val;
return 0;
}

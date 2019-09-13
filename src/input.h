#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>
#include <stdint.h>

/* Read a line into buf; strips trailing newline. */
int read_line(char *buf, size_t size);
/* Prompt and parse an unsigned integer. */
int read_uint(const char *prompt, uint32_t *out);

#endif

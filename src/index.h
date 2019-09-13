#ifndef INDEX_H
#define INDEX_H

#include <stdint.h>
#include "student.h"

/* Initialize / teardown. */
void index_init(Index *idx);
void index_free(Index *idx);
/* Look up, insert, or remove IDs. */
int  index_find(Index *idx, uint32_t id);
int  index_add(Index *idx, uint32_t id, long offset);
void index_remove(Index *idx, uint32_t id);

#endif

#include <stdlib.h>
#include "student.h"
#include "index.h"

void index_init(Index *idx) {
idx->entries = NULL;
idx->count = 0;
idx->capacity = 0;
}

void index_free(Index *idx) {
/* Caller owns the Index itself; just free the backing array. */
free(idx->entries);
}

static int index_grow(Index *idx) {
size_t new_cap = idx->capacity == 0 ? 8 : idx->capacity * 2;
IndexEntry *tmp = realloc(idx->entries, new_cap * sizeof(IndexEntry));
if (!tmp) return -1;
idx->entries = tmp;
idx->capacity = new_cap;
return 0;
}

int index_find(Index *idx, uint32_t id) {
for (size_t i = 0; i < idx->count; i++)
if (idx->entries[i].student_id == id)
return (int)i;
return -1;
}

int index_add(Index *idx, uint32_t id, long offset) {
/* Keep IDs unique inside the index. */
if (index_find(idx, id) != -1)
return -1;

if (idx->count == idx->capacity && index_grow(idx) != 0)
return -1;

idx->entries[idx->count++] = (IndexEntry){id, offset};
return 0;
}

void index_remove(Index *idx, uint32_t id) {
int pos = index_find(idx, id);
if (pos == -1) return;

for (size_t i = pos; i + 1 < idx->count; i++)
idx->entries[i] = idx->entries[i + 1];

idx->count--;
}

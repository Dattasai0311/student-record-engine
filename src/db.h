#ifndef DB_H
#define DB_H

#include <stdio.h>
#include "student.h"

/* Open the database file (create if missing). */
FILE *open_db(void);
/* Scan the file and rebuild the in-memory index. */
void rebuild_index(FILE *fp, Index *idx);

#endif

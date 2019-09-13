#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "db.h"
#include "index.h" 

FILE *open_db(void) {
FILE *fp = fopen(DB_FILE, "rb+");
if (!fp)
fp = fopen(DB_FILE, "wb+");
return fp;
}

void rebuild_index(FILE *fp, Index *idx) {
rewind(fp);

/* Walk the file and rebuild the in-memory index. */
while (1) {
long offset = ftell(fp);
RecordHeader hdr;

if (fread(&hdr, sizeof(hdr), 1, fp) != 1)
break;

if (hdr.magic != MAGIC || hdr.record_size != sizeof(Student)) {
fprintf(stderr, "Warning: corrupted record skipped.\n");
fseek(fp, hdr.record_size, SEEK_CUR);
continue;
}

Student s;
if (fread(&s, sizeof(s), 1, fp) != 1)
break;

if (!hdr.is_deleted)
index_add(idx, s.student_id, offset);
}
}

#include <stdio.h>
#include <string.h>


#include "student.h"
#include "db.h"
#include "index.h"
#include "input.h"

static void add_student(FILE *fp, Index *idx) {
Student s;

/* Read and validate basic fields before writing. */
if (read_uint("Student ID: ", &s.student_id) != 0) return;
if (index_find(idx, s.student_id) != -1) {
printf("Student exists.\n"); return;
}

printf("Name: "); read_line(s.name, sizeof(s.name));

uint32_t age;
if (read_uint("Age: ", &age) != 0 || age > 120) return;
s.age = (uint8_t)age;

printf("Major: "); read_line(s.major, sizeof(s.major));

RecordHeader hdr = {MAGIC, 1, 0, sizeof(Student)};

/* Append to end of file, then update in-memory index. */
fseek(fp, 0, SEEK_END);
long offset = ftell(fp);

fwrite(&hdr, sizeof(hdr), 1, fp);
fwrite(&s, sizeof(s), 1, fp);
fflush(fp);

index_add(idx, s.student_id, offset);
}

static void list_students(FILE *fp, Index *idx) {
for (size_t i = 0; i < idx->count; i++) {
/* Seek to payload (skip header) for each indexed record. */
fseek(fp, idx->entries[i].offset + sizeof(RecordHeader), SEEK_SET);
Student s;
fread(&s, sizeof(s), 1, fp);
printf("%u | %s | %u | %s\n", s.student_id, s.name, s.age, s.major);
}
}

int main(void) {
FILE *fp = open_db();
Index idx;
index_init(&idx);
rebuild_index(fp, &idx);

char cmd[32];
while (1) {
printf("\nadd | list | exit > ");
read_line(cmd, sizeof(cmd));

/* Simple command loop. */
if (strcmp(cmd, "add") == 0) add_student(fp, &idx);
else if (strcmp(cmd, "list") == 0) list_students(fp, &idx);
else if (strcmp(cmd, "exit") == 0) break;
}

index_free(&idx);
fclose(fp);
}

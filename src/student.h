#ifndef STUDENT_H
#define STUDENT_H


#include <stdint.h>
#include <stdio.h>


#define DB_FILE "student.db"
#define MAGIC 0x53545544 /* 'STUD' */


/* ===== Record Layout ===== */
typedef struct {
    uint32_t magic;
    uint32_t version;
    uint8_t is_deleted;
    uint32_t record_size;
} RecordHeader;


typedef struct {
    uint32_t student_id;
    char name[64];
    uint8_t age;
    char major[64];
} Student;


/* ===== Index ===== */
typedef struct {
    uint32_t student_id;
    long offset;
} IndexEntry;


typedef struct {
    IndexEntry *entries;
    size_t count;
    size_t capacity;
} Index;


#endif

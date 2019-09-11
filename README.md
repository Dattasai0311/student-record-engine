# Student Record Engine

Small, file-backed student record system written in C. Records are appended
to a binary file and an in-memory index is rebuilt on startup.

## Features
- Add student records (ID, name, age, major).
- List all non-deleted records.
- Simple on-disk layout with record headers.
- In-memory index for fast ID lookup.

## Project Layout
- `src/main.c`: CLI loop and commands.
- `src/db.c` / `src/db.h`: database open and index rebuild.
- `src/index.c` / `src/index.h`: in-memory index.
- `src/input.c` / `src/input.h`: input helpers.
- `src/student.h`: record and header definitions.
- `Makefile`: build targets.

## Build
```sh
make
```

Binary is written to `build/student_db`.

## Run
```sh
./build/student_db
```

### Commands
- `add`: add a new student record.
- `list`: list all records.
- `exit`: quit the program.

Example session:
```
add | list | exit > add
Student ID: 1001
Name: Ada Lovelace
Age: 20
Major: CS

add | list | exit > list
1001 | Ada Lovelace | 20 | CS
```

## Data File
The database file is `student.db` in the project root. Each record is stored as:
- `RecordHeader` (magic, version, is_deleted, record_size)
- `Student` payload (fixed-size fields)

On startup, the program scans the file and rebuilds an in-memory index of
active (non-deleted) records.

## Limitations
- No delete or update commands yet.
- No record validation beyond basic numeric parsing.
- No concurrency or file locking.
- Binary layout is compiler/architecture dependent.

## Notes
- If you delete `student.db`, the program will create a new one.
- The `build/` directory contains build artifacts.

## Roadmap Ideas
- Add update and delete support.
- Add search by name/major.
- Add record validation and stricter input handling.
- Add tests and a CI target.

## Cleaning
```sh
make clean
```

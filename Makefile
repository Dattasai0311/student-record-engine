CC=gcc
CFLAGS=-Wall -Wextra -g
SRC=src/main.c src/db.c src/index.c src/input.c
OUT=build/student_db

# Build the CLI binary.
all:
	mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

# Remove build output and database file.
clean:
	rm -rf build student.db

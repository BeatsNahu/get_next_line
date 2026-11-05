# get_next_line

> Reading a line from a file descriptor, one line at a time.  
> Project for **42 Barcelona** (Milestone 1).

---

## 📌 Overview

The **get_next_line** (GNL) project consists of writing a function in C that returns a line read from a file descriptor (`fd`). Each successive call to `get_next_line` returns the next line until the end of the file (EOF) is reached or an error occurs.

### Function Prototype

```c
char *get_next_line(int fd);
```

- **Return value**: The line read from the file descriptor (including the terminating `\n` character if present), or `NULL` if there is nothing else to read or an error occurred.

---

## ⚙️ Architecture & Logic

The project is structured around three modular phases:

```
[ get_next_line(fd) called ]
              │
              ▼
   1. Read & Accumulate ──────► Reads BUFFER_SIZE bytes in a loop using read()
              │                and concatenates with ft_strjoin until a '\n' is found
              │                or EOF is reached.
              ▼
   2. Confirm & Extract ──────► Allocates and extracts the line from index 0
              │                up to the '\n' (inclusive) or EOF.
              ▼
   3. Recover (Leftovers) ────► Allocates and keeps the remaining bytes (after '\n')
                               into the static variable for the next function call.
```

1. **`read_and_accumulate`**: Dynamically allocates a buffer of `BUFFER_SIZE + 1`, reads from `fd`, null-terminates the read chunk, and joins it into the static stash.
2. **`conffirm`**: Computes the exact length of the line (handling both lines with `\n` and lines ending at EOF without `\n`) and duplicates it into the return string.
3. **`recover`**: Slices whatever text remains after the newline, updates the static variable, and frees the old accumulation string.

---

## 🧠 Key Concepts & Technical Decisions

### Static Variables
A static variable inside a function preserves its value across multiple function invocations:
- Unlike regular automatic variables allocated on the stack that are destroyed when the function returns, a static variable has **static storage duration** (stored in the data/BSS segment).
- This persistence is essential for `get_next_line` because subsequent calls must remember any leftover characters read from a previous chunk.

### Dynamic Allocation vs. Stack Overflow
Local arrays allocated on the stack (e.g. `char tmp[BUFFER_SIZE + 1]`) can trigger a **Stack Overflow** (SIGSEGV) if `BUFFER_SIZE` is very large (e.g., `10,000,000`), as the default stack size on Linux is limited (~8 MB).  
In this implementation, temporary read buffers are allocated on the **Heap** via `malloc()` and promptly freed, making the function resilient to arbitrarily large buffer sizes.

### Out-Parameter Design
The helper function `checker` receives `size_t *position` as an out-parameter by reference. This allows the function to verify whether a newline exists while simultaneously reporting its index, eliminating redundant string traversals.

---

## 🌟 Bonus Part: Multiple File Descriptors

The bonus requirement extends `get_next_line` to support reading from multiple file descriptors concurrently without losing the reading thread of each descriptor:

```c
char *get_next_line(int fd)
{
    static char *content[OPEN_MAX];
    ...
}
```

- An array of pointers `static char *content[OPEN_MAX]` holds the stash for each active `fd`.
- It safely guards against out-of-bounds indices (`fd < 0 || fd >= OPEN_MAX`).
- In compliance with 42 project rules, this still counts as a single static variable.

---

## 🚀 Compilation & Usage

You can compile your program with `get_next_line` specifying any `BUFFER_SIZE` at compile time:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
./gnl
```

### Example `main.c`

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int   fd;
    char  *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Makefile Targets

```bash
make          # Compiles mandatory library GNL.a
make bonus    # Compiles bonus library with multiple FDs
make clean    # Removes object files
make fclean   # Removes object files and archive
make re       # Recompiles from scratch
```

---

## 📚 References & Resources

- [POSIX read() system call specification](https://pubs.opengroup.org/onlinepubs/009604599/functions/read.html)
- [Static variables in C (Wikipedia)](https://es.wikipedia.org/wiki/Variable_est%C3%A1tica)
- [How to change a macro value during compilation (Quora)](https://www.quora.com/How-can-I-change-a-macro-value-in-a-single-file-and-keep-its-original-value-on-the-other-files-during-compilation)
- [Checking macro definitions at compile-time (StackOverflow)](https://stackoverflow.com/questions/10545645/how-to-know-if-a-macro-has-been-defined-during-compilation)

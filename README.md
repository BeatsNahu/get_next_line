# get_next_line

> Reading a line from a file descriptor, one line at a time.  
> Project for **42 Barcelona** (Milestone 1).  
> **Branch**: `gnl_linked_list` (High-Performance $O(N)$ Queue Architecture).

---

## 📌 Overview

The **get_next_line** (GNL) project consists of writing a function in C that returns a line read from a file descriptor (`fd`). Each successive call to `get_next_line` returns the next line until the end of the file (EOF) is reached or an error occurs.

### Function Prototype

```c
char	*get_next_line(int fd);
```

- **Return value**: The line read from the file descriptor (including the terminating `\n` character if present), or `NULL` if there is nothing else to read or an error occurred.

---

## ⚙️ Architecture & Logic: High-Performance Queue ($O(1)$ Append)

Unlike the traditional string-accumulation approach (which repeatedly calls `strjoin`, leading to quadratic $O(N^2)$ execution times), this branch implements an **optimized Linked List Queue**:

```
[ get_next_line(fd) called ]
              │
              ▼
   1. Read & Accumulate ──────► Reads BUFFER_SIZE bytes into fresh nodes.
              │                Appends directly to tail in O(1) without
              │                re-traversing the list.
              ▼
   2. Confirm & Extract ──────► Computes exact line length in one pass O(N)
              │                and allocates/copies the line in a single pass O(N).
              ▼
   3. Recover (Leftovers) ────► Extracts characters remaining in the tail node
                               after '\n', stores them in a clean new node,
                               frees all old nodes, and resets stash.
```

1. **`read_and_accumulate`**: Dynamically allocates read buffers and appends them to the end of the list using a `tail` pointer in $O(1)$. It checks the newly read node for `\n` without walking preceding nodes.
2. **`conffirm`**: Computes the exact length of the line across nodes and duplicates it into the return string in a single contiguous allocation.
3. **`recover`**: Slices whatever text remains after the newline in the `tail` node, frees the old list, and establishes the remaining node as the new head of the `stash`.

---

## 📊 Benchmark: Strings ($O(N^2)$) vs. Linked List Queue ($O(N)$)

Tested on a single 50,000-character line (`giant_50k.txt`):

| BUFFER_SIZE | Strings (`ft_strjoin`) | Linked List (`tail` Queue) | Speedup Factor |
| :---: | :---: | :---: | :---: |
| **`1`** | **361.79 ms** | **28.01 ms** | **~13x faster** |
| **`10`** | **35.98 ms** | **2.85 ms** | **~12.6x faster** |
| **`42`** | **8.57 ms** | **0.76 ms** | **~11.3x faster** |
| **`1000`** | **0.47 ms** | **0.12 ms** | **~4x faster** |

> *To run the benchmark yourself:*
> ```bash
> ./.benchmark/run_benchmark.sh
> ```

---

## 🧠 Key Concepts & Technical Decisions

### Single vs. Double Pointers (`t_list *` vs `t_list **`)
- **Single pointer (`t_list *stash`)**: Passed by value to read-only functions (like `conffirm` and `get_len_line`). Advancing `stash = stash->next` navigates a local copy, leaving the caller's head pointer completely unaffected.
- **Double pointer (`t_list **stash`)**: Passed when a function must mutate the caller's pointer directly (such as reassigning the head `*stash = new_node`, clearing the list `*stash = NULL`, or advancing `&tail`).

### Dynamic Allocation vs. Stack Overflow
Temporary read buffers are allocated on the **Heap** via `malloc()` and promptly freed or transferred into nodes, avoiding stack exhaustion (`ulimit -s`) when `BUFFER_SIZE` is extremely large (e.g. `10,000,000`).

---

## 🌟 Bonus Part: Multiple File Descriptors

The bonus requirement extends `get_next_line` to support reading from multiple file descriptors concurrently:

```c
char	*get_next_line(int fd)
{
	static t_list	*stash[OPEN_MAX];

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	...
}
```

- An array of pointers `static t_list *stash[OPEN_MAX]` maintains an independent linked list for each active `fd`.
- In compliance with 42 project rules, this counts as a single static variable.

---

## 🚀 Compilation & Usage

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
./gnl
```

### Example `main.c`

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

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

---

## 📚 References & Resources

- [POSIX read() system call specification](https://pubs.opengroup.org/onlinepubs/009604599/functions/read.html)
- [Queue Abstract Data Type (Wikipedia)](https://en.wikipedia.org/wiki/Queue_(abstract_data_type))
- [Static variables in C (Wikipedia)](https://es.wikipedia.org/wiki/Variable_est%C3%A1tica)

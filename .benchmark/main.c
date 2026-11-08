#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
		return (1);
	}
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	clock_t start = clock();
	char *line;
	size_t total_lines = 0;
	size_t total_bytes = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		size_t i = 0;
		while (line[i])
			i++;
		total_bytes += i;
		total_lines++;
		free(line);
	}
	clock_t end = clock();
	close(fd);
	double elapsed_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
	printf("%8.2f ms  (%zu bytes, %zu lines)\n", elapsed_ms, total_bytes, total_lines);
	return (0);
}

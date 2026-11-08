#!/bin/bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$DIR"

echo "================================================================="
echo "        42 GNL BENCHMARK: STRINGS vs LINKED LISTS (QUEUE)        "
echo "================================================================="

# Generate test files
echo "Generando archivos de prueba..."
python3 -c "print('A' * 50000)" > giant_50k.txt
python3 -c "for i in range(1000): print(f'Line {i}: ' + 'X' * 80)" > multi_1000.txt

BUFFERS=(1 10 42 1000)

for B in "${BUFFERS[@]}"; do
    echo ""
    echo "-----------------------------------------------------------------"
    echo ">>> BUFFER_SIZE = $B"
    echo "-----------------------------------------------------------------"
    
    # Compile strings
    gcc -O2 -Wall -Wextra -Werror -D BUFFER_SIZE=$B main.c gnl_string/get_next_line.c gnl_string/get_next_line_utils.c -I gnl_string -o bench_string 2>/dev/null
    # Compile linked lists
    gcc -O2 -Wall -Wextra -Werror -D BUFFER_SIZE=$B main.c gnl_linked/get_next_line.c gnl_linked/get_next_line_utils.c -I gnl_linked -o bench_linked 2>/dev/null

    echo -n "  [Strings]     giant_50k.txt: "
    ./bench_string giant_50k.txt

    echo -n "  [Linked List] giant_50k.txt: "
    ./bench_linked giant_50k.txt
done

rm -f bench_string bench_linked giant_50k.txt multi_1000.txt
echo ""
echo "================================================================="
echo "                     BENCHMARK COMPLETADO                        "
echo "================================================================="

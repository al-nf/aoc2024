CC = gcc
CFLAGS = -Wall -g

PART1 = part1
PART2 = part2

all: $(PART1) $(PART2)

$(PART1): part1.c
	$(CC) $(CFLAGS) part1.c -o $(PART1)

$(PART2): part2.c
	$(CC) $(CFLAGS) part2.c -o $(PART2)
clean:
	rm -f $(PART1) $(PART2)


package day14

import (
	"bytes"
	"fmt"
	"log"
	"os"
	"slices"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day14/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day fourteen part one: %d\n", part1(string(file)))
	// fmt.Printf("day fourteen part two: %d\n", part2(string(file)))
}

func parseInput(input string) [][]byte {
	lines := strings.Split(input, "\n")
	grid := make([][]byte, len(lines))

	for i, line := range lines {
		grid[i] = []byte(line)
	}
	return grid
}

func part1(input string) (sum int) {
	grid := parseInput(input)

	changed := true
	for changed {
		changed = false

		for r := len(grid) - 1; r > 0; r-- {
			if !slices.Contains(grid[r], 'O') {
				continue
			}
			for c, chr := range grid[r] {
				if chr == 'O' && grid[r-1][c] == '.' {
					grid[r][c] = '.'
					grid[r-1][c] = 'O'
					changed = true
				}
			}
		}
	}
	for r, row := range grid {
		sum += bytes.Count(row, []byte{'O'}) * (len(grid) - r)
	}
	return sum
}

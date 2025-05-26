package day13

import (
	"fmt"
	"log"
	"os"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day13/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day twelve part one: %d\n", part1(string(file)))
	// fmt.Printf("day twelve part two: %d\n", part2(string(file)))
}

type grid struct {
	rows []string
	cols []string
}

func parseInput(input string) (grids []grid) {
	for _, gridStr := range strings.Split(input, "\n\n") {
		rows := strings.Split(gridStr, "\n")
		cols := make([]string, len(rows[0]))

		for c := range cols {
			col := make([]byte, len(rows))
			for r := range rows {
				col[r] = rows[r][c]
			}
			cols[c] = string(col)
		}
		grids = append(grids, grid{
			rows: rows,
			cols: cols,
		})
	}
	return grids
}

func findReflection(lines []string) int {
	len := len(lines)
outer:
	for i := range len - 1 {
		for offset := 0; ; offset++ {
			l := i - offset
			r := i + 1 + offset

			if l < 0 || r >= len {
				return i + 1
			}
			if lines[l] != lines[r] {
				continue outer
			}
		}
	}
	return 0
}

func part1(input string) (sum int) {
	for _, grid := range parseInput(input) {
		sum += (100 * findReflection(grid.rows)) + findReflection(grid.cols)
	}
	return sum
}

func part2(input string) (sum int) {
	for _, grid := range parseInput(input) {
	}
	return sum
}

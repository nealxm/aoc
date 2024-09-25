package day11

import (
	"fmt"
	"log"
	"math"
	"os"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day11/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day eleven part one: %d\n", part1(string(file)))
}

type vec2 struct {
	r, c int
}

func processInput(input string) []vec2 {
	lines := strings.Split(input, "\n")
	rows := make([]bool, len(lines))
	cols := make([]bool, len(lines[0]))

	for r, line := range lines {
		for c, chr := range line {
			if !(rows[r] && cols[c]) && chr == '#' {
				rows[r], cols[c] = true, true
			}
		}
	}
	grid := [][]string{}

	for r, line := range lines {
		gridRow := []string{}

		for c, chr := range line {
			if !cols[c] {
				gridRow = append(gridRow, string(chr))
				gridRow = append(gridRow, string(chr))
			} else {
				gridRow = append(gridRow, string(chr))
			}
		}
		if !rows[r] {
			grid = append(grid, gridRow)
			grid = append(grid, gridRow)
		} else {
			grid = append(grid, gridRow)
		}
	}
	galaxies := []vec2{}

	for r, row := range grid {
		for c, chr := range row {
			if chr == "#" {
				galaxies = append(galaxies, vec2{r, c})
			}
		}
	}
	return galaxies
}

func encode(a, b int) int {
	return ((a + b) * (a + b + 1) / 2) + b
}

func part1(input string) (sum int) {
	galaxies := processInput(input)
	seen := make(map[int]bool)

	for i, galaxya := range galaxies {
		for j, galaxyb := range galaxies {
			if i == j || seen[encode(i, j)] || seen[encode(j, i)] {
				continue
			}
			seen[encode(i, j)] = true
			sum += int(math.Abs(float64(galaxyb.r-galaxya.r))) + int(math.Abs(float64(galaxyb.c-galaxya.c)))
		}
	}
	return sum
}

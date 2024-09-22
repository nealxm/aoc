package day10

import (
	"fmt"
	"log"
	"os"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day10/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day nine part one: %d\n", part1(string(file)))
}

type vec2 struct {
	r, c int
}

func processInput(input string) (grid [][]string, start vec2) {
	for r, line := range strings.Split(input, "\n") {
		row := []string{}

		for c, char := range line {
			row = append(row, string(char))

			if char == 'S' {
				start = vec2{r, c}
			}
		}
		grid = append(grid, row)
	}
	return grid, start
}

var checks = [4]vec2{
	{-1, 0},
	{0, 1},
	{1, 0},
	{0, -1},
}

func clamp(val, min, max int) int {
	if val < min {
		return min
	} else if val > max {
		return max
	}
	return val
}

var valids = [4]string{
	"|LJS",
	"-LFS",
	"|7FS",
	"-J7S",
}

var dirs = map[string]func(idx int) bool{
	"|": func(idx int) bool { return idx == 0 || idx == 2 },
	"-": func(idx int) bool { return idx == 1 || idx == 3 },
	"L": func(idx int) bool { return idx == 2 || idx == 3 },
	"J": func(idx int) bool { return idx == 2 || idx == 1 },
	"7": func(idx int) bool { return idx == 0 || idx == 1 },
	"F": func(idx int) bool { return idx == 0 || idx == 3 },
}

func part1(input string) (steps int) {
	grid, curr := processInput(input)
	prev := curr

outer:
	for {
	main:
		for i, check := range checks {
			r := clamp(curr.r+check.r, 0, len(grid)-1)
			c := clamp(curr.c+check.c, 0, len(grid[r])-1)
			if r == prev.r && c == prev.c {
				continue
			}
			currChr := grid[curr.r][curr.c]

			switch grid[r][c] {
			case "|", "-", "L", "J", "7", "F":
				if dirs[grid[r][c]](i) && strings.ContainsAny(currChr, valids[i]) {
					prev = curr
					curr = vec2{r, c}
					steps++
					break main
				}
			case "S":
				if strings.ContainsAny(currChr, valids[i]) {
					steps++
					break outer
				}
			}
		}
	}
	return steps / 2
}

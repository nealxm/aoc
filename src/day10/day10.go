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

	fmt.Printf("day ten part one: %d\n", part1(string(file)))
	fmt.Printf("day ten part two: %d\n", part2(string(file)))
}

type vec2 struct {
	r, c int
}

func processInput1(input string) (grid [][]string, start vec2) {
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

var valids = [4]string{
	"|LJ",
	"-LF",
	"|7F",
	"-J7",
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
	grid, curr := processInput1(input)
	prev := curr

outer:
	for {
	main:
		for i, check := range checks {
			r := min(max(curr.r+check.r, 0), len(grid)-1)
			c := min(max(curr.c+check.c, 0), len(grid[r])-1)
			if r == prev.r && c == prev.c {
				continue
			}
			currChr := grid[curr.r][curr.c]
			if currChr == "S" {
				currChr = "|-LJ7F"
			}

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

func encode(a, b int) int {
	return ((a + b) * (a + b + 1) / 2) + b
}

func processInput2(input string) ([][]string, map[int]bool) {
	grid := [][]string{}
	curr := vec2{}

	for r, line := range strings.Split(input, "\n") {
		row := []string{}

		for c, char := range line {
			row = append(row, string(char))

			if char == 'S' {
				curr = vec2{r, c}
			}
		}
		grid = append(grid, row)
	}
	prev := curr
	loop := make(map[int]bool)

outer:
	for {
	main:
		for i, check := range checks {
			r := min(max(curr.r+check.r, 0), len(grid)-1)
			c := min(max(curr.c+check.c, 0), len(grid[r])-1)
			if r == prev.r && c == prev.c {
				continue
			}
			currChr := grid[curr.r][curr.c]
			if currChr == "S" {
				currChr = "|-LJ7F"
			}

			switch grid[r][c] {
			case "|", "-", "L", "J", "7", "F":
				if dirs[grid[r][c]](i) && strings.ContainsAny(currChr, valids[i]) {
					prev = curr
					curr = vec2{r, c}
					loop[encode(r, c)] = true
					break main
				}
			case "S":
				if strings.ContainsAny(currChr, valids[i]) {
					curr = vec2{r, c}
					loop[encode(r, c)] = true
					break outer
				}
			}
		}
	}
	vAdj, j := [2]int{}, 0

	for i, check := range checks {
		sAdj := vec2{
			r: min(max(curr.r+check.r, 0), len(grid)-1),
			c: min(max(curr.c+check.c, 0), len(grid[curr.r])-1),
		}

		if chrAdj := grid[sAdj.r][sAdj.c]; chrAdj != "." && chrAdj != "S" && dirs[chrAdj](i) {
			vAdj[j] = i
			j++
		}
	}

	chrs := make(map[rune]bool)
	for _, chr := range valids[vAdj[0]] {
		chrs[chr] = true
	}
	for _, chr := range valids[vAdj[1]] {
		if chrs[chr] {
			grid[curr.r][curr.c] = string(chr)
			break
		}
	}
	return grid, loop
}

type strStack []string

func (s *strStack) push(str string) {
	*s = append(*s, str)
}

func (s *strStack) peek() string {
	return (*s)[len(*s)-1]
}

func (s *strStack) pop() string {
	str := (*s)[len(*s)-1]
	*s = (*s)[:len(*s)-1]
	return str
}

func part2(input string) (area int) {
	grid, loop := processInput2(input)

	for r, row := range grid {
		for c := range row {
			if loop[encode(r, c)] {
				continue
			}
			stack := strStack{}

			for i, chr := range row[c:] {
				if loop[encode(r, c+i)] {
					switch chr {
					case "|", "L", "F":
						stack.push(chr)
					case "-":
						continue
					case "J":
						switch stack.peek() {
						case "L":
							stack.pop()
						case "F":
							stack.pop()
							stack.push("|")
						}
					case "7":
						switch stack.peek() {
						case "F":
							stack.pop()
						case "L":
							stack.pop()
							stack.push("|")
						}
					}
				}
			}
			if len(stack)%2 == 1 {
				area++
			}
		}
	}
	return area
}

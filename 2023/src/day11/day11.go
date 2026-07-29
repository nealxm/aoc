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

	fmt.Printf("2023:d11p1 - %d\n", part1(string(file)))
	fmt.Printf("2023:d11p2 - %d\n", part2(string(file)))
}

type vec2 struct {
	r, c int32
}

func findGalaxies(lines []string) ([]bool, []bool) {
	rows := make([]bool, len(lines))
	cols := make([]bool, len(lines[0]))

	for r, line := range lines {
		for c, chr := range line {
			if !(rows[r] && cols[c]) && chr == '#' {
				rows[r], cols[c] = true, true
			}
		}
	}
	return rows, cols
}

func processInput1(input string) (galaxies []vec2) {
	lines := strings.Split(input, "\n")
	rows, cols := findGalaxies(lines)
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

	for r, row := range grid {
		for c, chr := range row {
			if chr == "#" {
				galaxies = append(galaxies, vec2{int32(r), int32(c)})
			}
		}
	}
	return galaxies
}

func encode(a, b int32) int32 {
	return ((a + b) * (a + b + 1) / 2) + b
}

func processGalaxies(galaxies []vec2) (sum uint64) {
	seen := make(map[int32]bool)

	for i, galaxya := range galaxies {
		for j, galaxyb := range galaxies {
			if i == j || seen[encode(int32(i), int32(j))] || seen[encode(int32(j), int32(i))] {
				continue
			}
			seen[encode(int32(i), int32(j))] = true
			sum += uint64(math.Abs(float64(galaxyb.r-galaxya.r))) + uint64(math.Abs(float64(galaxyb.c-galaxya.c)))
		}
	}
	return sum
}

func part1(input string) uint32 {
	return uint32(processGalaxies(processInput1(input)))
}

func processInput2(input string) (galaxies []vec2) {
	lines := strings.Split(input, "\n")
	rows, cols := findGalaxies(lines)
	rowOffset := make([]int, len(rows))
	colOffset := make([]int, len(cols))
	totalRowOffset := 0
	totalColOffset := 0

	for r, row := range rows {
		if !row {
			totalRowOffset += 999999
		}
		rowOffset[r] = totalRowOffset
	}
	for c, col := range cols {
		if !col {
			totalColOffset += 999999
		}
		colOffset[c] = totalColOffset
	}

	for r, line := range lines {
		for c, chr := range line {
			if chr == '#' {
				galaxies = append(galaxies, vec2{int32(r + rowOffset[r]), int32(c + colOffset[c])})
			}
		}
	}
	return galaxies
}

func part2(input string) uint64 {
	return processGalaxies(processInput2(input))
}

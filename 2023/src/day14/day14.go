package day14

import (
	"bytes"
	"crypto/sha256"
	"fmt"
	"log"
	"os"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day14/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("2023:d14p1 - %d\n", part1(string(file)))
	fmt.Printf("2023:d14p2 - %d\n", part2(string(file)))
}

func parseInput(input string) *[][]byte {
	lines := strings.Split(input, "\n")
	grid := make([][]byte, len(lines))

	for i, line := range lines {
		grid[i] = []byte(line)
	}
	return &grid
}

func tiltNorth(grid *[][]byte) {
	for r, row := range *grid {
		for c, chr := range row {
			if chr == 'O' {
				newRow := r

				for newRow > 0 && (*grid)[newRow-1][c] == '.' {
					newRow--
				}
				if newRow != r {
					(*grid)[r][c] = '.'
					(*grid)[newRow][c] = 'O'
				}
			}
		}
	}
}

func tiltWest(grid *[][]byte) {
	for r, row := range *grid {
		for c, chr := range row {
			if chr == 'O' {
				newCol := c

				for newCol > 0 && (*grid)[r][newCol-1] == '.' {
					newCol--
				}
				if newCol != c {
					(*grid)[r][c] = '.'
					(*grid)[r][newCol] = 'O'
				}
			}
		}
	}
}

func tiltSouth(grid *[][]byte) {
	for r := len(*grid) - 2; r >= 0; r-- {
		for c, chr := range (*grid)[r] {
			if chr == 'O' {
				newRow := r

				for newRow < len(*grid)-1 && (*grid)[newRow+1][c] == '.' {
					newRow++
				}
				if newRow != r {
					(*grid)[r][c] = '.'
					(*grid)[newRow][c] = 'O'
				}
			}
		}
	}
}

func tiltEast(grid *[][]byte) {
	for r, row := range *grid {
		for c := len(row) - 2; c >= 0; c-- {
			if row[c] == 'O' {
				newCol := c

				for newCol < len(row)-1 && (*grid)[r][newCol+1] == '.' {
					newCol++
				}
				if newCol != c {
					(*grid)[r][c] = '.'
					(*grid)[r][newCol] = 'O'
				}
			}
		}
	}
}

func northLoad(grid [][]byte) (sum uint32) {
	for r, row := range grid {
		sum += uint32(bytes.Count(row, []byte{'O'})) * uint32(len(grid)-r)
	}
	return sum
}

func part1(input string) uint32 {
	grid := parseInput(input)
	tiltNorth(grid)
	return northLoad(*grid)
}

func cRun(grid *[][]byte) {
	tiltNorth(grid)
	tiltWest(grid)
	tiltSouth(grid)
	tiltEast(grid)
}

func part2(input string) uint32 {
	grid := parseInput(input)
	seen := make(map[string]uint32)

	for i := range 1_000_000_000 {
		hasher := sha256.New()
		for _, row := range *grid {
			hasher.Write(row)
		}
		hash := string(hasher.Sum(nil))

		if lastSeen, exists := seen[hash]; exists {
			remaining := (1_000_000_000 - lastSeen) % (uint32(i) - lastSeen)

			for range remaining {
				cRun(grid)
			}
			return northLoad(*grid)
		}
		seen[hash] = uint32(i)
		cRun(grid)
	}
	return northLoad(*grid)
}

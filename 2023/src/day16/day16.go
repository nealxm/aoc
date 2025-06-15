package day16

import (
	"fmt"
	"log"
	"os"
	"slices"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day16/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day sixteen part one: %d\n", part1(string(file)))
	fmt.Printf("day sixteen part two: %d\n", part2(string(file)))
}

type direction uint8

const (
	up direction = iota
	right
	down
	left
)

type beam struct {
	row, col int16
	dir      direction
}

type state struct {
	grid        [][]byte
	visited     map[[2]int16]map[direction]bool
	energized   map[[2]int16]bool
	activeBeams []beam
}

var (
	forwardSlash = map[direction]direction{
		up:    right,
		right: up,
		down:  left,
		left:  down,
	}
	backwardSlash = map[direction]direction{
		up:    left,
		right: down,
		down:  right,
		left:  up,
	}
)

func parseInput(input string) (grid [][]byte) {
	for _, line := range strings.Split(input, "\n") {
		grid = append(grid, []byte(line))
	}
	return grid
}

func moveBeam(b beam) beam {
	var offset [2]int16
	switch b.dir {
	case up:
		offset = [2]int16{-1, 0}
	case right:
		offset = [2]int16{0, 1}
	case down:
		offset = [2]int16{1, 0}
	case left:
		offset = [2]int16{0, -1}
	}
	return beam{b.row + offset[0], b.col + offset[1], b.dir}
}

func processBeam(grid [][]byte, start beam) int {
	s := &state{
		grid,
		make(map[[2]int16]map[direction]bool),
		make(map[[2]int16]bool),
		[]beam{start},
	}
	for len(s.activeBeams) > 0 {
		curr := s.activeBeams[0]
		s.activeBeams = slices.Delete(s.activeBeams, 0, 1)

		if curr.row < 0 || curr.row >= int16(len(s.grid)) ||
			curr.col < 0 || curr.col >= int16(len(s.grid[0])) {
			continue
		}
		pos := [2]int16{curr.row, curr.col}

		if dirs, exists := s.visited[pos]; !exists {
			s.visited[pos] = make(map[direction]bool)
		} else if dirs[curr.dir] {
			continue
		}
		s.visited[pos][curr.dir] = true
		s.energized[pos] = true

		switch s.grid[curr.row][curr.col] {
		case '.':
			s.activeBeams = append(s.activeBeams, moveBeam(curr))
		case '/':
			s.activeBeams = append(s.activeBeams, moveBeam(beam{
				curr.row, curr.col,
				forwardSlash[curr.dir],
			}))
		case '\\':
			s.activeBeams = append(s.activeBeams, moveBeam(beam{
				curr.row, curr.col,
				backwardSlash[curr.dir],
			}))
		case '|':
			if curr.dir == up || curr.dir == down {
				s.activeBeams = append(s.activeBeams, moveBeam(curr))
			} else {
				s.activeBeams = append(s.activeBeams, moveBeam(beam{
					curr.row, curr.col,
					up,
				}), moveBeam(beam{
					curr.row, curr.col,
					down,
				}))
			}
		case '-':
			if curr.dir == right || curr.dir == left {
				s.activeBeams = append(s.activeBeams, moveBeam(curr))
			} else {
				s.activeBeams = append(s.activeBeams, moveBeam(beam{
					curr.row, curr.col,
					right,
				}), moveBeam(beam{
					curr.row, curr.col,
					left,
				}))
			}
		}
	}
	return len(s.energized)
}

func part1(input string) int {
	return processBeam(parseInput(input), beam{
		0, 0,
		right,
	})
}

func part2(input string) (maxE int) {
	grid := parseInput(input)
	for r, row := range grid {
		for c := range row {
			if !(r == 0 || r == len(grid)-1 || c == 0 || c == len(row)-1) {
				continue
			}

			if r == 0 && c == 0 {
				maxE = max(maxE, processBeam(grid, beam{
					int16(r), int16(c),
					right,
				}), processBeam(grid, beam{
					int16(r), int16(c),
					down,
				}))
			} else if r == 0 && c == len(row)-1 {
				maxE = max(maxE, processBeam(grid, beam{
					int16(r), int16(c),
					down,
				}), processBeam(grid, beam{
					int16(r), int16(c),
					left,
				}))
			} else if r == len(grid)-1 && c == len(row)-1 {
				maxE = max(maxE, processBeam(grid, beam{
					int16(r), int16(c),
					up,
				}), processBeam(grid, beam{
					int16(r), int16(c),
					left,
				}))
			} else if r == len(grid)-1 && c == 0 {
				maxE = max(maxE, processBeam(grid, beam{
					int16(r), int16(c),
					up,
				}), processBeam(grid, beam{
					int16(r), int16(c),
					right,
				}))
			} else {
				if r == 0 {
					maxE = max(maxE, processBeam(grid, beam{
						int16(r), int16(c),
						down,
					}))
				} else if c == len(row)-1 {
					maxE = max(maxE, processBeam(grid, beam{
						int16(r), int16(c),
						left,
					}))
				} else if r == len(grid)-1 {
					maxE = max(maxE, processBeam(grid, beam{
						int16(r), int16(c),
						up,
					}))
				} else if c == 0 {
					maxE = max(maxE, processBeam(grid, beam{
						int16(r), int16(c),
						right,
					}))
				}
			}
		}
	}
	return maxE
}

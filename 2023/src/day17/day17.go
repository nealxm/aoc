package day17

import (
	"container/heap"
	"fmt"
	"log"
	"math"
	"os"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day17/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("2023:d17p1 - %d\n", part1(string(file)))
	fmt.Printf("2023:d17p2 - %d\n", part2(string(file)))
}

type dir int8

const (
	north dir = iota
	east
	south
	west
)

type vertex struct {
	row, col uint8
	facing   dir
	straight uint8
}

type entry struct {
	vertex   vertex
	heatloss uint16
}

type priorityQueue []*entry

func (pq *priorityQueue) Len() int {
	return len(*pq)
}

func (pq *priorityQueue) Less(i, j int) bool {
	return (*pq)[i].heatloss < (*pq)[j].heatloss
}

func (pq *priorityQueue) Swap(i, j int) {
	(*pq)[i], (*pq)[j] = (*pq)[j], (*pq)[i]
}

func (pq *priorityQueue) Push(v any) {
	*pq = append(*pq, v.(*entry))
}

func (pq *priorityQueue) Pop() any {
	out := (*pq)[len(*pq)-1]
	*pq = (*pq)[:len(*pq)-1]
	return out
}

func parseInput(input string) (grid [][]uint8) {
	for _, line := range strings.Split(input, "\n") {
		row := make([]uint8, len(line))
		for col, char := range line {
			row[col] = uint8(char - '0')
		}
		grid = append(grid, row)
	}
	return grid
}

func (e *entry) genSteps1(grid [][]uint8) (steps []*entry) {
	cantidateDirs := []dir{}

	for d := range dir(4) {
		if d == e.vertex.facing {
			if e.vertex.straight < 3 {
				cantidateDirs = append(cantidateDirs, d)
			}
		} else if math.Abs(float64(d-e.vertex.facing)) != 2 {
			cantidateDirs = append(cantidateDirs, d)
		}
	}

	for _, d := range cantidateDirs {
		switch d {
		case north:
			if e.vertex.row > 0 {
				steps = append(steps, &entry{vertex{e.vertex.row - 1, e.vertex.col, north, 0}, 0})
			}
		case east:
			if e.vertex.col+1 < uint8(len(grid[0])) {
				steps = append(steps, &entry{vertex{e.vertex.row, e.vertex.col + 1, east, 0}, 0})
			}
		case south:
			if e.vertex.row+1 < uint8(len(grid)) {
				steps = append(steps, &entry{vertex{e.vertex.row + 1, e.vertex.col, south, 0}, 0})
			}
		case west:
			if e.vertex.col > 0 {
				steps = append(steps, &entry{vertex{e.vertex.row, e.vertex.col - 1, west, 0}, 0})
			}
		}
	}

	for _, step := range steps {
		step.heatloss = e.heatloss + uint16(grid[step.vertex.row][step.vertex.col])

		if step.vertex.facing == e.vertex.facing {
			step.vertex.straight = e.vertex.straight + 1
		} else {
			step.vertex.straight = 1
		}
	}
	return steps
}

func part1(input string) uint16 {
	grid := parseInput(input)

	pq := &priorityQueue{
		&entry{vertex: vertex{row: 0, col: 0, facing: north, straight: 0}, heatloss: 0},
		&entry{vertex: vertex{row: 0, col: 0, facing: east, straight: 0}, heatloss: 0},
		&entry{vertex: vertex{row: 0, col: 0, facing: south, straight: 0}, heatloss: 0},
		&entry{vertex: vertex{row: 0, col: 0, facing: west, straight: 0}, heatloss: 0},
	}
	heap.Init(pq)
	best := make(map[vertex]uint16)

	for pq.Len() > 0 {
		e := heap.Pop(pq).(*entry)
		if val, ok := best[e.vertex]; ok && e.heatloss > val {
			continue
		}
		if e.vertex.row == uint8(len(grid)-1) && e.vertex.col == uint8(len(grid[0])-1) {
			return e.heatloss
		}

		steps := e.genSteps1(grid)
		for _, step := range steps {
			if val, ok := best[step.vertex]; ok && step.heatloss >= val {
				continue
			}
			best[step.vertex] = step.heatloss
			heap.Push(pq, step)
		}
	}
	return 0
}

func (e *entry) genSteps2(grid [][]uint8) (steps []*entry) {
	cantidateDirs := []dir{}

	for d := range dir(4) {
		if d == e.vertex.facing {
			if e.vertex.straight >= 4 && e.vertex.straight < 10 {
				cantidateDirs = append(cantidateDirs, d)
			} else if e.vertex.straight < 4 {
				cantidateDirs = []dir{d}
				break
			}
		} else if math.Abs(float64(d-e.vertex.facing)) != 2 {
			cantidateDirs = append(cantidateDirs, d)
		}
	}

	for _, d := range cantidateDirs {
		switch d {
		case north:
			if e.vertex.row > 0 {
				steps = append(steps, &entry{vertex{e.vertex.row - 1, e.vertex.col, north, 0}, 0})
			}
		case east:
			if e.vertex.col+1 < uint8(len(grid[0])) {
				steps = append(steps, &entry{vertex{e.vertex.row, e.vertex.col + 1, east, 0}, 0})
			}
		case south:
			if e.vertex.row+1 < uint8(len(grid)) {
				steps = append(steps, &entry{vertex{e.vertex.row + 1, e.vertex.col, south, 0}, 0})
			}
		case west:
			if e.vertex.col > 0 {
				steps = append(steps, &entry{vertex{e.vertex.row, e.vertex.col - 1, west, 0}, 0})
			}
		}
	}

	for _, step := range steps {
		step.heatloss = e.heatloss + uint16(grid[step.vertex.row][step.vertex.col])

		if step.vertex.facing == e.vertex.facing {
			step.vertex.straight = e.vertex.straight + 1
		} else {
			step.vertex.straight = 1
		}
	}
	return steps
}

func part2(input string) uint16 {
	grid := parseInput(input)

	pq := &priorityQueue{
		&entry{vertex: vertex{row: 0, col: 0, facing: north, straight: 0}, heatloss: 0},
		&entry{vertex: vertex{row: 0, col: 0, facing: east, straight: 0}, heatloss: 0},
		&entry{vertex: vertex{row: 0, col: 0, facing: south, straight: 0}, heatloss: 0},
		&entry{vertex: vertex{row: 0, col: 0, facing: west, straight: 0}, heatloss: 0},
	}
	heap.Init(pq)
	best := make(map[vertex]uint16)

	for pq.Len() > 0 {
		e := heap.Pop(pq).(*entry)
		if val, ok := best[e.vertex]; ok && e.heatloss > val {
			continue
		}
		if e.vertex.straight >= 4 && (e.vertex.row == uint8(len(grid)-1) && e.vertex.col == uint8(len(grid[0])-1)) {
			return e.heatloss
		}

		steps := e.genSteps2(grid)
		for _, step := range steps {
			if val, ok := best[step.vertex]; ok && step.heatloss >= val {
				continue
			}
			best[step.vertex] = step.heatloss
			heap.Push(pq, step)
		}
	}
	return 0
}

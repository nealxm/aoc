package day12

import (
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day12/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day twelve part one: %d\n", part1(string(file)))
	fmt.Printf("day twelve part two: %d\n", part2(string(file)))
}

type rowCond struct {
	springs string
	groups  []uint8
}

func processInput1(input string) (springRows []rowCond) {
	for i, line := range strings.Split(input, "\n") {
		for j, part := range strings.Split(line, " ") {
			if j == 0 {
				springRows = append(springRows, rowCond{springs: part})
			} else if j == 1 {
				for _, aNum := range strings.Split(part, ",") {
					iNum, err := strconv.ParseInt(aNum, 10, 8)
					if err != nil {
						log.Fatalf("parse int error: %v", err)
					}
					springRows[i].groups = append(springRows[i].groups, uint8(iNum))
				}
			}
		}
	}
	return springRows
}

type rowState uint8

const (
	valid rowState = iota
	invalid
	earlyInvalid
)

func validRow(rc rowCond) rowState {
	var (
		curr, j uint8
	)
	for i, spring := range rc.springs {
		switch spring {
		case '?':
			return invalid
		case '#':
			curr++
			if i == len(rc.springs)-1 || rc.springs[i+1] == '.' {
				if j >= uint8(len(rc.groups)) || curr != rc.groups[j] {
					return earlyInvalid
				}
				j++
				curr = 0
			} else if rc.springs[i+1] == '?' {
				if j >= uint8(len(rc.groups)) || curr > rc.groups[j] {
					return earlyInvalid
				}
				j++
				curr = 0
			}
		}
	}
	if j != uint8(len(rc.groups)) {
		return earlyInvalid
	}
	return valid
}

func computeSum(rowConds []rowCond) (sum int) {
	var buildRow func(rowCond) int

	buildRow = func(rc rowCond) int {
		if state := validRow(rc); state == valid {
			return 1
		} else if state == earlyInvalid {
			return 0
		}
		idx := strings.IndexRune(rc.springs, '?')
		if idx == -1 {
			return 0
		}
		return buildRow(rowCond{
			springs: rc.springs[:idx] + "." + rc.springs[idx+1:],
			groups:  rc.groups,
		}) + buildRow(rowCond{
			springs: rc.springs[:idx] + "#" + rc.springs[idx+1:],
			groups:  rc.groups,
		})
	}
	for _, springRow := range rowConds {
		sum += buildRow(springRow)
	}
	return sum
}

func part1(input string) int {
	return computeSum(processInput1(input))
}

func processInput2(input string) (springRows []rowCond) {
	for _, springRow := range processInput1(input) {
		var (
			newSprings strings.Builder
			newGroups  []uint8
		)

		for i := 0; i < 5; i++ {
			newSprings.WriteString(springRow.springs)
			newGroups = append(newGroups, springRow.groups...)
			if i < 4 {
				newSprings.WriteByte('?')
			}
		}
		springRows = append(springRows, rowCond{
			springs: newSprings.String(),
			groups:  newGroups,
		})
	}
	return springRows
}

func part2(input string) (sum int) {
	return computeSum(processInput2(input))
}

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
}

type rowCond struct {
	springs string
	groups  []uint8
}

func processInput(input string) (springRows []rowCond) {
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

func validRow(rc rowCond) bool {
	var (
		curr, j uint8
	)
	for i, spring := range rc.springs {
		if spring == '?' {
			return false
		} else if spring == '#' {
			if i == len(rc.springs)-1 || rc.springs[i+1] == '.' || rc.springs[i+1] == '?' {
				curr++
				if j >= uint8(len(rc.groups)) || curr != rc.groups[j] {
					return false
				} else {
					j++
					curr = 0
				}
			} else if rc.springs[i+1] == '#' {
				curr++
			}
		}
	}
	if j != uint8(len(rc.groups)) {
		return false
	}
	return true
}

func part1(input string) (sum int) {
	var buildRow func(rowCond) int

	buildRow = func(rc rowCond) int {
		if validRow(rc) {
			return 1
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

	for _, springRow := range processInput(input) {
		sum += buildRow(springRow)
	}

	return sum
}

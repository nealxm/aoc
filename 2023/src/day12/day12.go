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

func countArrangements(springs string, groups []uint8, cache map[string]int) (result int) {
	key := fmt.Sprintf("%s|%v", springs, groups)
	if val, exists := cache[key]; exists {
		return val
	}
	if len(springs) == 0 {
		if len(groups) == 0 {
			return 1
		}
		return 0
	}
	if len(groups) == 0 {
		if strings.IndexByte(springs, '#') != -1 {
			return 0
		}
		return 1
	}

	if springs[0] == '.' || springs[0] == '?' {
		result += countArrangements(springs[1:], groups, cache)
	}
	if springs[0] == '#' || springs[0] == '?' {
		currentGroup := int(groups[0])
		if currentGroup <= len(springs) {
			canPlace := true

			for i := range currentGroup {
				if springs[i] == '.' {
					canPlace = false
					break
				}
			}
			if canPlace && currentGroup < len(springs) && springs[currentGroup] == '#' {
				canPlace = false
			}
			if canPlace {
				newPos := int(groups[0])
				if newPos < len(springs) {
					newPos++
				}
				result += countArrangements(springs[newPos:], groups[1:], cache)
			}
		}
	}
	cache[key] = result
	return result
}

func computeSum(rowConds []rowCond) (sum int) {
	for _, rc := range rowConds {
		cache := make(map[string]int)
		arrangements := countArrangements(rc.springs, rc.groups, cache)
		sum += arrangements
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

		for i := range 5 {
			newSprings.WriteString(springRow.springs)
			newGroups = append(newGroups, springRow.groups...)
			if i < 4 {
				newSprings.WriteRune('?')
			}
		}
		springRows = append(springRows, rowCond{
			springs: newSprings.String(),
			groups:  newGroups,
		})
	}
	return springRows
}

func part2(input string) int {
	return computeSum(processInput2(input))
}

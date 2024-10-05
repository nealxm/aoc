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
	rle    string
	groups []uint8
}

func processInput(input string) (springRows []rowCond) {
	for i, line := range strings.Split(input, "\n") {
		for j, part := range strings.Split(line, " ") {
			if j == 0 {
				var encoded strings.Builder
				count := 1

				for k := 1; k < len(part); k++ {
					if part[k] == part[k-1] {
						count++
					} else {
						encoded.WriteString(string(part[k-1]))
						encoded.WriteString(strconv.Itoa(count))
						count = 1
					}
				}
				encoded.WriteString(string(part[len(part)-1]))
				encoded.WriteString(strconv.Itoa(count))

				springRows = append(springRows, rowCond{rle: encoded.String()})
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

func part1(input string) (sum int) {
	for _, springRow := range processInput(input) {

	}
	return sum
}

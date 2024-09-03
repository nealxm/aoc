package day03

import (
	"fmt"
	"log"
	"os"
	"regexp"
	"strconv"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day03/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day three part one: %d\n", Part1(string(file)))
}

type number struct {
	value int
	row   int
	col   []int
	valid bool
}

var (
	numRe  = regexp.MustCompile(`\d{1,}`)
	specRe = regexp.MustCompile(`[^\d.]`)
)

func processInput(input string) (numbers []number, source []string) {
	source = strings.Split(input, "\n")
	for i, line := range source {
		for _, numIdx := range numRe.FindAllStringIndex(line, -1) {
			val, err := strconv.Atoi(line[numIdx[0]:numIdx[1]])
			if err != nil {
				log.Fatal(err)
			}

			numbers = append(numbers, number{
				value: val,
				row:   i,
				col:   numIdx,
			})
		}
	}
	return numbers, source
}

func Part1(input string) (sum int) {
	numbers, source := processInput(input)

	for _, num := range numbers {
	numLoop:
		for i := max(0, num.row-1); i <= min(len(source)-1, num.row+1); i++ {
			for j := max(0, num.col[0]-1); j < min(len(source[i]), num.col[1]+1); j++ {
				if i == num.row && (j >= num.col[0] && j < num.col[1]) {
					continue
				}
				if specRe.Match([]byte{source[i][j]}) {
					num.valid = true
					break numLoop
				}
			}
		}
		if num.valid {
			sum += num.value
		}
	}
	return sum
}

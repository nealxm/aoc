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

	fmt.Printf("day three part one: %d\n", part1(string(file)))
	fmt.Printf("day three part two: %d\n", part2(string(file)))
}

type number struct {
	value int
	row   int
	col   []int
	valid bool
}

var (
	numRe  = regexp.MustCompile(`\d+`)
	specRe = regexp.MustCompile(`[^\d.]`)
	starRe = regexp.MustCompile(`\*`)
)

func processNumbers(input string) (numbers []number, source []string) {
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

func part1(input string) (sum int) {
	numbers, source := processNumbers(input)

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

// using cantor paring function to store 2d coords as 1d num
// after encoding, don't need access to original 2d coords so decode is unnecessary
func encode(a, b int) int {
	return ((a + b) * (a + b + 1) / 2) + b
}

func processStars(input string) (map[int][]*number, []*number, []string) {
	stars := map[int][]*number{}
	numbers := []*number{}
	source := strings.Split(input, "\n")

	for i, line := range source {
		for _, numIdx := range numRe.FindAllStringIndex(line, -1) {
			val, err := strconv.Atoi(line[numIdx[0]:numIdx[1]])
			if err != nil {
				log.Fatal(err)
			}

			numbers = append(numbers, &number{
				value: val,
				row:   i,
				col:   numIdx,
			})
		}
		for _, starIdx := range starRe.FindAllStringIndex(line, -1) {
			stars[encode(i, starIdx[0])] = []*number{}
		}
	}
	return stars, numbers, source
}

func part2(input string) (sum int) {
	stars, numbers, source := processStars(input)

	for _, num := range numbers {
		for i := max(0, num.row-1); i <= min(len(source)-1, num.row+1); i++ {
			for j := max(0, num.col[0]-1); j < min(len(source[i]), num.col[1]+1); j++ {
				if i == num.row && (j >= num.col[0] && j < num.col[1]) {
					continue
				}
				if starRe.Match([]byte{source[i][j]}) {
					stars[encode(i, j)] = append(stars[encode(i, j)], num)
				}
			}
		}
	}

	for _, nums := range stars {
		if len(nums) != 2 {
			continue
		}
		sum += nums[0].value * nums[1].value
	}
	return sum
}

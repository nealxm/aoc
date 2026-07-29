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

	fmt.Printf("2023:d03p1 - %d\n", part1(string(file)))
	fmt.Printf("2023:d03p2 - %d\n", part2(string(file)))
}

type number struct {
	value uint16
	row   uint8
	col   []uint8
	valid bool
}

var (
	numRe  = regexp.MustCompile(`\d+`)
	specRe = regexp.MustCompile(`[^\d.]`)
	starRe = regexp.MustCompile(`\*`)
)

func touint8[T int](input []T) []uint8 {
	result := make([]uint8, len(input))

	for i, val := range input {
		result[i] = uint8(val)
	}
	return result
}

func processNumbers(input string) (numbers []number, source []string) {
	source = strings.Split(input, "\n")
	for i, line := range source {
		for _, numIdx := range numRe.FindAllStringIndex(line, -1) {
			val, err := strconv.ParseUint(line[numIdx[0]:numIdx[1]], 10, 16)
			if err != nil {
				log.Fatal(err)
			}

			numbers = append(numbers, number{
				value: uint16(val),
				row:   uint8(i),
				col:   touint8(numIdx),
			})
		}
	}
	return numbers, source
}

func lowerBound(val uint8) uint8 {
	if val == 0 {
		return 0
	}
	return val - 1
}

func part1(input string) (sum uint32) {
	numbers, source := processNumbers(input)

	for _, num := range numbers {
	numLoop:
		for i := lowerBound(num.row); i <= min(uint8(len(source)-1), num.row+1); i++ {
			for j := lowerBound(num.col[0]); j < min(uint8(len(source[i])), num.col[1]+1); j++ {
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
			sum += uint32(num.value)
		}
	}
	return sum
}

// using cantor paring function to store 2d coords as 1d num
// after encoding, don't need access to original 2d coords so decode is unnecessary
func encode(a, b uint16) uint16 {
	return ((a + b) * (a + b + 1) / 2) + b
}

func processStars(input string) (map[uint16][]*number, []*number, []string) {
	stars := map[uint16][]*number{}
	numbers := []*number{}
	source := strings.Split(input, "\n")

	for i, line := range source {
		for _, numIdx := range numRe.FindAllStringIndex(line, -1) {
			val, err := strconv.Atoi(line[numIdx[0]:numIdx[1]])
			if err != nil {
				log.Fatal(err)
			}

			numbers = append(numbers, &number{
				value: uint16(val),
				row:   uint8(i),
				col:   touint8(numIdx),
			})
		}
		for _, starIdx := range starRe.FindAllStringIndex(line, -1) {
			stars[encode(uint16(i), uint16(starIdx[0]))] = []*number{}
		}
	}
	return stars, numbers, source
}

func part2(input string) (sum uint32) {
	stars, numbers, source := processStars(input)

	for _, num := range numbers {
		for i := lowerBound(num.row); i <= min(uint8(len(source)-1), num.row+1); i++ {
			for j := lowerBound(num.col[0]); j < min(uint8(len(source[i])), num.col[1]+1); j++ {
				if i == num.row && (j >= num.col[0] && j < num.col[1]) {
					continue
				}
				if starRe.Match([]byte{source[i][j]}) {
					stars[encode(uint16(i), uint16(j))] = append(stars[encode(uint16(i), uint16(j))], num)
				}
			}
		}
	}

	for _, nums := range stars {
		if len(nums) != 2 {
			continue
		}
		sum += uint32(nums[0].value) * uint32(nums[1].value)
	}
	return sum
}

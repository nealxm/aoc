package day04

import (
	"fmt"
	"log"
	"os"
	"regexp"
	"strconv"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day04/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day four part one: %d\n", Part1(string(file)))
}

var (
	numRe = regexp.MustCompile(`\d+`)
	winRe = regexp.MustCompile(`(?:Card\s+\d+:)((\s+\d+)+)(?:\s\|)`)
	givRe = regexp.MustCompile(`(?:\s\|)((\s+\d+)+)`)
)

func processNums(line string) (nums []int) {
	for _, sNum := range numRe.FindAllString(line, -1) {
		iNum, err := strconv.Atoi(sNum)
		if err != nil {
			log.Fatal(err)
		}

		nums = append(nums, iNum)
	}
	return nums
}

func getPoints(matches int) int {
	if matches == 0 {
		return 0
	}

	points := 1
	for n := 1; n < matches; n++ {
		points *= 2
	}
	return points
}

func Part1(input string) (sum int) {
	for _, line := range strings.Split(input, "\n") {
		matches := 0

		for _, given := range processNums(givRe.FindAllStringSubmatch(line, -1)[0][1]) {
			for _, winner := range processNums(winRe.FindAllStringSubmatch(line, -1)[0][1]) {
				if given != winner {
					continue
				}
				matches += 1
			}
		}
		sum += getPoints(matches)
	}
	return sum
}

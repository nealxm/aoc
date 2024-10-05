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

	fmt.Printf("day four part one: %d\n", part1(string(file)))
	fmt.Printf("day four part two: %d\n", part2(string(file)))
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

func part1(input string) (sum int) {
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

type scorecard struct {
	instances int
	winners   []int
	givens    []int
}

func processCards(input string) (cards []scorecard) {
	for _, line := range strings.Split(input, "\n") {
		cards = append(cards, scorecard{
			instances: 1,
			winners:   processNums(winRe.FindAllStringSubmatch(line, -1)[0][1]),
			givens:    processNums(givRe.FindAllStringSubmatch(line, -1)[0][1]),
		})
	}
	return cards
}

func part2(input string) (sum int) {
	cards := processCards(input)

	for i, card := range cards {
		matches := 0

		for _, given := range card.givens {
			for _, winner := range card.winners {
				if given != winner {
					continue
				}
				matches += 1
			}
		}
		for j := 1; j <= matches; j++ {
			cards[i+j].instances += card.instances
		}
	}

	for _, card := range cards {
		sum += card.instances
	}
	return sum
}

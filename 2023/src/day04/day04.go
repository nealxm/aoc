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

	fmt.Printf("2023:d04p1 - %d\n", part1(string(file)))
	fmt.Printf("2023:d04p2 - %d\n", part2(string(file)))
}

var (
	numRe = regexp.MustCompile(`\d+`)
	winRe = regexp.MustCompile(`(?:Card\s+\d+:)((\s+\d+)+)(?:\s\|)`)
	givRe = regexp.MustCompile(`(?:\s\|)((\s+\d+)+)`)
)

func processNums(line string) (nums []uint8) {
	for _, sNum := range numRe.FindAllString(line, -1) {
		iNum, err := strconv.ParseUint(sNum, 10, 8)
		if err != nil {
			log.Fatal(err)
		}

		nums = append(nums, uint8(iNum))
	}
	return nums
}

func getPoints(matches uint16) uint16 {
	if matches == 0 {
		return 0
	}

	var points uint16 = 1
	for n := 1; uint16(n) < matches; n++ {
		points *= 2
	}
	return points
}

func part1(input string) (sum uint16) {
	for _, line := range strings.Split(input, "\n") {
		var matches uint16 = 0

		for _, given := range processNums(givRe.FindAllStringSubmatch(line, -1)[0][1]) {
			for _, winner := range processNums(winRe.FindAllStringSubmatch(line, -1)[0][1]) {
				if given != winner {
					continue
				}
				matches += 1
			}
		}
		sum += uint16(getPoints(matches))
	}
	return sum
}

type scorecard struct {
	instances uint32
	winners   []uint8
	givens    []uint8
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

func part2(input string) (sum uint32) {
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

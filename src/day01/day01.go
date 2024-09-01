package day01

import (
	"fmt"
	"log"
	"os"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day01/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day one part one: %d\n", Part1(string(file)))
	fmt.Printf("day one part two: %d\n", Part2(string(file)))
}

func Part1(input string) int {
	sum := 0
	for _, line := range strings.Split(input, "\n") {
		sum += (firstDigit(line) * 10) + lastDigit(line)
	}
	return sum
}

func firstDigit(line string) int {
	for i := 0; i < len(line); i++ {
		if line[i] >= '0' && line[i] <= '9' {
			return int(line[i] - '0')
		}
	}
	log.Fatal("first digit not found in: ", line)
	return -1
}

func lastDigit(line string) int {
	for i := len(line) - 1; i >= 0; i-- {
		if line[i] >= '0' && line[i] <= '9' {
			return int(line[i] - '0')
		}
	}
	log.Fatal("last digit not found in: ", line)
	return -1
}

func Part2(input string) int {
	sum := 0
	for _, line := range strings.Split(input, "\n") {
		sum += (firstNum(line) * 10) + lastNum(line)
	}
	return sum
}

var numbers = []string{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}

func firstNum(line string) int {
	for i := 0; i < len(line); i++ {
		if line[i] >= '0' && line[i] <= '9' {
			return int(line[i] - '0')
		}

		for j, num := range numbers {
			if strings.HasSuffix(line[:i+1], num) {
				return j + 1
			}
		}
	}
	log.Fatal("first number not found in: ", line)
	return -1
}

func lastNum(line string) int {
	for i := len(line) - 1; i >= 0; i-- {
		if line[i] >= '0' && line[i] <= '9' {
			return int(line[i] - '0')
		}

		for j, num := range numbers {
			if strings.HasPrefix(line[i-1:], num) {
				return j + 1
			}
		}
	}
	log.Fatal("last number not found in: ", line)
	return -1
}

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

	fmt.Printf("day one part one: %d\n", One(string(file)))
}

func One(input string) int {
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
	log.Fatal("first number not found in: ", line)
	return -1
}

func lastDigit(line string) int {
	for i := len(line) - 1; i >= 0; i-- {
		if line[i] >= '0' && line[i] <= '9' {
			return int(line[i] - '0')
		}
	}
	log.Fatal("last number not found in: ", line)
	return -1
}

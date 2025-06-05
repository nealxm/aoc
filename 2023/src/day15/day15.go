package day15

import (
	"fmt"
	"log"
	"os"
)

func Main() {
	file, err := os.ReadFile("src/day15/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day fifteen part one: %d\n", part1(string(file)))
	fmt.Printf("day fifteen part two: %d\n", part2(string(file)))
}

func part1(input string) int {
	return 0
}

func part2(input string) int {
	return 0
}

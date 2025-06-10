package day15

import (
	"fmt"
	"log"
	"os"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day15/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day fifteen part one: %d\n", part1(string(file)))
	fmt.Printf("day fifteen part two: %d\n", part2(string(file)))
}

func part1(input string) (sum int) {
	for _, seq := range strings.Split(input, ",") {
		curr := 0
		for _, chr := range seq {
			curr = ((curr + int(chr)) * 17) % 256
		}
		sum += curr
	}
	return sum
}

func part2(input string) int {
	return 0
}

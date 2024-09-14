package day08

import (
	"fmt"
	"log"
	"os"
	"regexp"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day08/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day eight part one: %d\n", part1(string(file)))
}

var nodeRe = regexp.MustCompile(`\w{3}`)

type node struct {
	l, r string
}

func processInput1(input string) (string, map[string]node) {
	chunks := strings.Split(input, "\n\n")
	network := map[string]node{}

	for _, line := range strings.Split(chunks[1], "\n") {
		parts := nodeRe.FindAllString(line, -1)

		network[parts[0]] = node{
			l: parts[1],
			r: parts[2],
		}
	}
	return chunks[0], network
}

func part1(input string) (steps int) {
	dirs, network := processInput1(input)
	curr := "AAA"

main:
	for {
		for _, char := range dirs {
			steps++

			if char == 'L' {
				curr = network[curr].l
			} else if char == 'R' {
				curr = network[curr].r
			}
		}
		if curr != "ZZZ" {
			continue main
		}
		break
	}
	return steps
}

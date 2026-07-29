package day08

import (
	"fmt"
	"log"
	"math"
	"os"
	"regexp"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day08/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("2023:d08p1 - %d\n", part1(string(file)))
	fmt.Printf("2023:d08p2 - %d\n", part2(string(file)))
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

func part1(input string) (steps uint16) {
	dirs, network := processInput1(input)
	curr := "AAA"

main:
	for {
		for _, char := range dirs {
			steps++

			switch char {
			case 'L':
				curr = network[curr].l
			case 'R':
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

func processInput2(input string) (string, []string, map[string]node) {
	chunks := strings.Split(input, "\n\n")
	currs := []string{}
	network := map[string]node{}

	for _, line := range strings.Split(chunks[1], "\n") {
		parts := nodeRe.FindAllString(line, -1)

		network[parts[0]] = node{
			l: parts[1],
			r: parts[2],
		}
		if strings.HasSuffix(parts[0], "A") {
			currs = append(currs, parts[0])
		}
	}
	return chunks[0], currs, network
}

func gcd(a, b uint64) uint64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func lcm(a, b uint64) uint64 {
	return uint64(math.Abs(float64(a*b))) / gcd(a, b)
}

// find least common multiple using euclidian algorithm,
// compare all nums in slice to find overall lcm
func slicelcm(nums []uint64) uint64 {
	result := nums[0]

	for _, num := range nums[1:] {
		result = lcm(result, num)
	}
	return uint64(result)
}

func part2(input string) uint64 {
	dirs, currs, network := processInput2(input)
	lsteps := []uint64{}

	for i := range currs {
		var steps uint64 = 0
	main:
		for {
			for _, char := range dirs {
				steps++

				switch char {
				case 'L':
					currs[i] = network[currs[i]].l
				case 'R':
					currs[i] = network[currs[i]].r
				}
			}
			if !strings.HasSuffix(currs[i], "Z") {
				continue main
			}
			lsteps = append(lsteps, steps)
			break
		}
	}
	return slicelcm(lsteps)
}

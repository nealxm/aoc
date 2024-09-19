package day09

import (
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day09/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day nine part one: %d\n", part1(string(file)))
}

func extrapolateReading(curr []int32) int32 {
	next := []int32{}
	allZeros := true

	for i, val := range curr {
		if i == len(curr)-1 {
			break
		}

		diff := curr[i+1] - val
		if allZeros && diff != 0 {
			allZeros = false
		}
		next = append(next, diff)
	}
	if allZeros {
		return curr[0]
	}
	return curr[len(curr)-1] + extrapolateReading(next)
}

func part1(input string) (sum int32) {
	for _, line := range strings.Split(input, "\n") {
		readings := []int32{}

		for _, sNum := range strings.Split(line, " ") {
			dNum, err := strconv.Atoi(sNum)
			if err != nil {
				log.Fatal(err)
			}
			readings = append(readings, int32(dNum))
		}
		sum += extrapolateReading(readings)
	}
	return sum
}

package day02

import (
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day02/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day two part one: %d\n", Part1(string(file)))
}

const (
	MAX_RED   = 12
	MAX_GREEN = 13
	MAX_BLUE  = 14
)

func Part1(input string) int {
	sum := 0
	for i, game := range strings.Split(input, "\n") {
		validGame := true
		game = strings.Split(game, ": ")[1]
		game = strings.ReplaceAll(game, ";", ",")

		for _, draw := range strings.Split(game, ", ") {
			drawParts := strings.Split(draw, " ")
			color := drawParts[1]
			amount, err := strconv.Atoi(drawParts[0])
			if err != nil {
				log.Fatal(err)
			}

			if (color == "red" && amount > MAX_RED) ||
				(color == "green" && amount > MAX_GREEN) ||
				(color == "blue" && amount > MAX_BLUE) {
				validGame = false
				break
			}
		}
		if validGame {
			sum += (i + 1)
		}
	}
	return sum
}

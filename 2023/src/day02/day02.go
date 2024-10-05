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

	fmt.Printf("day two part one: %d\n", part1(string(file)))
	fmt.Printf("day two part two: %d\n", part2(string(file)))
}

const (
	MAX_RED   = 12
	MAX_GREEN = 13
	MAX_BLUE  = 14
)

func part1(input string) (sum int) {
	for i, game := range processInput(input) {
		validGame := true

		for _, draw := range game {
			amount, color := processDraw(draw)

			if (color == "red" && amount > MAX_RED) ||
				(color == "green" && amount > MAX_GREEN) ||
				(color == "blue" && amount > MAX_BLUE) {
				validGame = false
				break
			}
		}
		if validGame {
			sum += i + 1
		}
	}
	return sum
}

func processInput(input string) (games [][]string) {
	for _, line := range strings.Split(input, "\n") {
		line = strings.ReplaceAll(strings.Split(line, ": ")[1], ";", ",")
		var game []string

		for _, draw := range strings.Split(line, ", ") {
			game = append(game, draw)
		}
		games = append(games, game)
	}
	return games
}

func processDraw(draw string) (int, string) {
	parts := strings.Split(draw, " ")
	amount, err := strconv.Atoi(parts[0])
	if err != nil {
		log.Fatal(err)
	}
	return amount, parts[1]
}

func part2(input string) (sum int) {
	for _, game := range processInput(input) {
		var mRed, mGreen, mBlue int

		for _, draw := range game {
			amount, color := processDraw(draw)

			if color == "red" && amount > mRed {
				mRed = amount
			} else if color == "green" && amount > mGreen {
				mGreen = amount
			} else if color == "blue" && amount > mBlue {
				mBlue = amount
			}
		}
		sum += mRed * mGreen * mBlue
	}
	return sum
}

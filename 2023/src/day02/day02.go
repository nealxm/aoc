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

	fmt.Printf("2023:d02p1 - %d\n", part1(string(file)))
	fmt.Printf("2023:d02p2 - %d\n", part2(string(file)))
}

const (
	MAX_RED   = 12
	MAX_GREEN = 13
	MAX_BLUE  = 14
)

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

func processDraw(draw string) (uint8, string) {
	parts := strings.Split(draw, " ")
	amount, err := strconv.ParseUint(parts[0], 10, 8)
	if err != nil {
		log.Fatal(err)
	}
	return uint8(amount), parts[1]
}

func part1(input string) (sum uint16) {
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
			sum += uint16(i + 1)
		}
	}
	return sum
}

func part2(input string) (sum uint32) {
	for _, game := range processInput(input) {
		var mRed, mGreen, mBlue uint16

		for _, draw := range game {
			amount, color := processDraw(draw)

			if color == "red" && uint16(amount) > mRed {
				mRed = uint16(amount)
			} else if color == "green" && uint16(amount) > mGreen {
				mGreen = uint16(amount)
			} else if color == "blue" && uint16(amount) > mBlue {
				mBlue = uint16(amount)
			}
		}
		sum += uint32(mRed * mGreen * mBlue)
	}
	return sum
}

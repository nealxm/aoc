package main

import (
	"aoc2023/src/day01"
	"aoc2023/src/day02"
	"aoc2023/src/day03"
	"aoc2023/src/day04"
	"aoc2023/src/day05"
	"aoc2023/src/day06"
	"aoc2023/src/day07"
	"aoc2023/src/day08"
	"log"
	"os"
)

func main() {
	if len(os.Args) != 2 {
		log.Fatalln("invalid arguements: must specify an aoc day to run (1-25)")
	}

	switch os.Args[1] {
	case "1":
		day01.Main()
	case "2":
		day02.Main()
	case "3":
		day03.Main()
	case "4":
		day04.Main()
	case "5":
		day05.Main()
	case "6":
		day06.Main()
	case "7":
		day07.Main()
	case "8":
		day08.Main()
	default:
		log.Fatalln("invalid day specified: either not implemented or not 1-25")
	}
}

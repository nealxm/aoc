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
	"aoc2023/src/day09"
	"log"
	"os"
)

var funcs = map[string]func(){
	"1": day01.Main,
	"2": day02.Main,
	"3": day03.Main,
	"4": day04.Main,
	"5": day05.Main,
	"6": day06.Main,
	"7": day07.Main,
	"8": day08.Main,
	"9": day09.Main,
}

func main() {
	if len(os.Args) != 2 {
		log.Fatalln("invalid arguements: must specify an aoc day to run (1-25)")
	}

	if day, exists := funcs[os.Args[1]]; !exists {
		log.Fatalln("invalid day specified: either not implemented or not 1-25")
	} else {
		day()
	}
}

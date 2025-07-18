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
	"aoc2023/src/day10"
	"aoc2023/src/day11"
	"aoc2023/src/day12"
	"aoc2023/src/day13"
	"aoc2023/src/day14"
	"aoc2023/src/day15"
	"aoc2023/src/day16"
	"log"
	"os"
)

var funcs = map[string]func(){
	"1":  day01.Main,
	"2":  day02.Main,
	"3":  day03.Main,
	"4":  day04.Main,
	"5":  day05.Main,
	"6":  day06.Main,
	"7":  day07.Main,
	"8":  day08.Main,
	"9":  day09.Main,
	"10": day10.Main,
	"11": day11.Main,
	"12": day12.Main,
	"13": day13.Main,
	"14": day14.Main,
	"15": day15.Main,
	"16": day16.Main,
}

func main() {
	if len(os.Args) != 2 {
		log.Fatalln("invalid arguments: must specify an aoc day to run (1-25)")
	}

	if day, exists := funcs[os.Args[1]]; !exists {
		log.Fatalln("invalid day specified: either not implemented or not 1-25")
	} else {
		day()
	}
}

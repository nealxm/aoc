package main

import (
	"aoc2023/src/day01"
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
	default:
		log.Fatalln("invalid day specified: either not implemented or not 1-25")
	}
}

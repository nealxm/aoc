package day06

import (
	"fmt"
	"log"
	"os"
	"regexp"
	"strconv"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day06/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day six part one: %d\n", part1(string(file)))
	fmt.Printf("day six part two: %d\n", part2(string(file)))
}

var numRe = regexp.MustCompile(`\d+`)

type race struct {
	time, dist, comb int
}

func processRaces(input string) (races []race) {
	for i, line := range strings.Split(input, "\n") {
		for j, sNum := range numRe.FindAllString(line, -1) {
			dNum, err := strconv.Atoi(sNum)
			if err != nil {
				log.Fatal(err)
			}

			if i == 0 {
				races = append(races, race{
					time: dNum,
				})
			} else if i == 1 {
				races[j].dist = dNum
			}
		}
	}
	return races
}

func part1(input string) (prod int) {
	races := processRaces(input)
	for i, race := range races {
		for ms := 1; ms < race.time; ms++ {
			att := ms * (race.time - ms)

			if att > race.dist {
				races[i].comb++
			}
		}

		if i == 0 {
			prod = races[i].comb
		} else {
			prod *= races[i].comb
		}
	}
	return prod
}

func processRace(input string) (race race) {
	for i, line := range strings.Split(input, "\n") {
		var build strings.Builder

		for _, sNum := range numRe.FindAllString(line, -1) {
			build.WriteString(sNum)
		}
		dNum, err := strconv.Atoi(build.String())
		if err != nil {
			log.Fatal(err)
		}

		if i == 0 {
			race.time = dNum
		} else if i == 1 {
			race.dist = dNum
		}
	}
	return race
}

func part2(input string) (comb int) {
	race := processRace(input)
	for ms := 0; ms <= race.time; ms++ {
		att := ms * (race.time - ms)

		if att > race.dist {
			race.comb = (race.time - ms) - ms + 1
			break
		}
	}
	return race.comb
}

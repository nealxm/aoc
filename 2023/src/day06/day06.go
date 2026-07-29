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

	fmt.Printf("2023:d06p1 - %d\n", part1(string(file)))
	fmt.Printf("2023:d06p2 - %d\n", part2(string(file)))
}

var numRe = regexp.MustCompile(`\d+`)

type race1 struct {
	time, dist, comb uint16
}

func processRaces(input string) (races []race1) {
	for i, line := range strings.Split(input, "\n") {
		for j, sNum := range numRe.FindAllString(line, -1) {
			dNum, err := strconv.ParseUint(sNum, 10, 32)
			if err != nil {
				log.Fatal(err)
			}

			switch i {
			case 0:
				races = append(races, race1{
					time: uint16(dNum),
				})
			case 1:
				races[j].dist = uint16(dNum)
			}
		}
	}
	return races
}

func part1(input string) (prod uint32) {
	races := processRaces(input)
	for i, race := range races {
		var ms uint16

		for ms = 1; ms < race.time; ms++ {
			att := ms * (race.time - ms)

			if att > race.dist {
				races[i].comb++
			}
		}

		if i == 0 {
			prod = uint32(races[i].comb)
		} else {
			prod *= uint32(races[i].comb)
		}
	}
	return prod
}

type race2 struct {
	time, dist, comb uint64
}

func processRace(input string) (race race2) {
	for i, line := range strings.Split(input, "\n") {
		var build strings.Builder

		for _, sNum := range numRe.FindAllString(line, -1) {
			build.WriteString(sNum)
		}
		dNum, err := strconv.ParseUint(build.String(), 10, 64)
		if err != nil {
			log.Fatal(err)
		}

		switch i {
		case 0:
			race.time = dNum
		case 1:
			race.dist = dNum
		}
	}
	return race
}

func part2(input string) uint32 {
	race := processRace(input)
	var ms uint64

	for ms = 0; ms <= race.time; ms++ {
		att := ms * (race.time - ms)

		if att > race.dist {
			race.comb = (race.time - ms) - ms + 1
			break
		}
	}
	return uint32(race.comb)
}

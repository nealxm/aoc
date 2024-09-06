package day05

import (
	"fmt"
	"log"
	"os"
	"regexp"
	"strconv"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day05/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day five part one: %d\n", part1(string(file)))
}

var (
	seedRe = regexp.MustCompile(`(?:seeds:)((?:\s\d+)+)`)
	numRe  = regexp.MustCompile(`\d+`)
	mapRe  = regexp.MustCompile(`(\w+)(?:-to-)(\w+)(?:\smap:\n)((?:\d+\s\d+\s\d+\s)+)`)
)

type spec uint8

const (
	base spec = iota
	soil
	fert
	water
	light
	temp
	humid
	loc
)

var strSpec = map[string]spec{
	"seed":        base,
	"soil":        soil,
	"fertilizer":  fert,
	"water":       water,
	"light":       light,
	"temperature": temp,
	"humidity":    humid,
	"location":    loc,
}

type seed struct {
	id  spec
	val int64
}

type mapRange struct {
	srcRange [2]int64
	trans    int64
}

type seedMap struct { // must be used with map[spec]seedMap for source id
	dstId  spec
	ranges []mapRange
}

func processInput(input string) ([]seed, map[spec]seedMap) {
	seeds := []seed{}
	seedMaps := map[spec]seedMap{}

	for _, sNum := range numRe.FindAllString(seedRe.FindStringSubmatch(input)[1], -1) {
		dNum, err := strconv.ParseInt(sNum, 10, 64)
		if err != nil {
			log.Fatal(err)
		}

		seeds = append(seeds, seed{
			id:  base,
			val: dNum,
		})
	}

	for _, group := range mapRe.FindAllStringSubmatch(input, -1) {
		sm := seedMap{
			dstId:  strSpec[group[2]],
			ranges: []mapRange{},
		}

		for _, nums := range strings.Split(group[3], "\n") {
			if nums == "" {
				continue
			}
			mr := mapRange{}
			var dstStart int64

			for i, sNum := range numRe.FindAllString(nums, -1) {
				dNum, err := strconv.ParseInt(sNum, 10, 64)
				if err != nil {
					log.Fatal(err)
				}

				if i == 0 {
					dstStart = dNum
				} else if i == 1 {
					mr.srcRange = [2]int64{dNum, 0}
				} else if i == 2 {
					mr.srcRange[1] = mr.srcRange[0] + dNum
				}
			}
			mr.trans = dstStart - mr.srcRange[0]
			sm.ranges = append(sm.ranges, mr)
		}
		seedMaps[strSpec[group[1]]] = sm
	}
	return seeds, seedMaps
}

func part1(input string) (min int64) {
	seeds, seedMaps := processInput(input)

	for i := base; i < loc; i++ {
		for j, mapRange := range seedMaps[i].ranges {
			for k, seed := range seeds {
				if seed.id != i {
					continue
				}

				if seed.val >= mapRange.srcRange[0] && seed.val < mapRange.srcRange[1] {
					seeds[k].id++
					seeds[k].val += mapRange.trans
				} else if j == len(seedMaps[i].ranges)-1 {
					seeds[k].id++
				}
			}
		}
	}

	for i, seed := range seeds {
		if i == 1 {
			min = seed.val
		}
		if seed.val < min {
			min = seed.val
		}
	}
	return min
}

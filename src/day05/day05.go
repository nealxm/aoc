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
	numRe = regexp.MustCompile(`\d+`)
	mapRe = regexp.MustCompile(`(\w+)-to-(\w+)`)
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
	src   [2]int64
	trans int64
}

func processInput1(input string) ([]seed, map[spec][]mapRange) {
	seeds := []seed{}
	seedMaps := map[spec][]mapRange{}
	chunks := strings.Split(input, "\n\n")

	for _, sNum := range numRe.FindAllString(chunks[0], -1) {
		dNum, err := strconv.ParseInt(sNum, 10, 64)
		if err != nil {
			log.Fatal(err)
		}

		seeds = append(seeds, seed{
			id:  base,
			val: dNum,
		})
	}

	for _, chunk := range chunks[1:] {
		specs := mapRe.FindAllStringSubmatch(chunk, -1)[0]
		mrs := []mapRange{}

		for i, nums := range strings.Split(chunk, "\n") {
			if i == 0 {
				continue
			}
			mr := mapRange{}
			var dstStart int64

			for i, sNum := range strings.Split(nums, " ") {
				dNum, err := strconv.ParseInt(sNum, 10, 64)
				if err != nil {
					log.Fatal(err)
				}

				if i == 0 {
					dstStart = dNum
				} else if i == 1 {
					mr.src = [2]int64{dNum, 0}
				} else if i == 2 {
					mr.src[1] = mr.src[0] + dNum
				}
			}
			mr.trans = dstStart - mr.src[0]
			mrs = append(mrs, mr)
		}
		seedMaps[strSpec[specs[1]]] = mrs
	}
	return seeds, seedMaps
}

func part1(input string) (min int64) {
	seeds, seedMaps := processInput1(input)

	for i := base; i < loc; i++ {
		for j, mapRange := range seedMaps[i] {
			for k, seed := range seeds {
				if seed.id != i {
					continue
				}

				if seed.val >= mapRange.src[0] && seed.val < mapRange.src[1] {
					seeds[k].id++
					seeds[k].val += mapRange.trans
				} else if j == len(seedMaps[i])-1 {
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

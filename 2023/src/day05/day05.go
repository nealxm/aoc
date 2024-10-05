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
	fmt.Printf("day five part two: %d\n", part2(string(file)))
}

var (
	numRe  = regexp.MustCompile(`\d+`)
	mapRe  = regexp.MustCompile(`(\w+)-to-(\w+)`)
	num2Re = regexp.MustCompile(`\s\d+\s\d+`)
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

type numRange struct {
	min, max int64
}

type mapRange struct {
	numRange
	trans int64
}

func processMaps(chunks []string) map[spec][]mapRange {
	seedMaps := map[spec][]mapRange{}

	for _, chunk := range chunks {
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
					mr.min = dNum
				} else if i == 2 {
					mr.max = mr.min + dNum
				}
			}
			mr.trans = dstStart - mr.min
			mrs = append(mrs, mr)
		}
		seedMaps[strSpec[specs[1]]] = mrs
	}
	return seedMaps
}

func processInput1(input string) ([]seed, map[spec][]mapRange) {
	seeds := []seed{}
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
	return seeds, processMaps(chunks[1:])
}

func part1(input string) (min int64) {
	seeds, seedMaps := processInput1(input)

	for i := base; i < loc; i++ {
		for j, mapRange := range seedMaps[i] {
			for k, seed := range seeds {
				if seed.id != i {
					continue
				}

				if seed.val >= mapRange.min && seed.val < mapRange.max {
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

type seedRange struct {
	id spec
	numRange
}

func processInput2(input string) ([]seedRange, map[spec][]mapRange) {
	seedRanges := []seedRange{}
	chunks := strings.Split(input, "\n\n")

	for _, nums := range num2Re.FindAllString(chunks[0], -1) {
		sr := seedRange{}

		for i, sNum := range strings.Split(strings.TrimSpace(nums), " ") {
			dNum, err := strconv.ParseInt(sNum, 10, 64)
			if err != nil {
				log.Fatal(err)
			}

			if i == 0 {
				sr.min = dNum
			} else if i == 1 {
				sr.max = sr.min + dNum
			}
		}
		seedRanges = append(seedRanges, sr)
	}
	return seedRanges, processMaps(chunks[1:])
}

func part2(input string) (min int64) {
	seedRanges, seedMaps := processInput2(input)

main:
	for {
		for i, sr := range seedRanges {
			if sr.id == loc {
				continue
			}

			for j, mr := range seedMaps[sr.id] {
				if sr.max <= mr.min || sr.min >= mr.max {
					if j == len(seedMaps[sr.id])-1 {
						seedRanges[i].id++
					}
					continue

				} else if sr.min >= mr.min && sr.max <= mr.max {
					seedRanges[i].min += mr.trans
					seedRanges[i].max += mr.trans
					seedRanges[i].id++
					break

				} else if sr.min < mr.min && sr.max > mr.max {
					seedRanges = append(seedRanges, seedRange{
						id: sr.id,
						numRange: numRange{
							min: sr.min,
							max: mr.min,
						},
					})
					seedRanges = append(seedRanges, seedRange{
						id: sr.id,
						numRange: numRange{
							min: mr.max,
							max: sr.max,
						},
					})
					seedRanges[i].min = mr.min + mr.trans
					seedRanges[i].max = mr.max + mr.trans
					seedRanges[i].id++
					break

				} else if sr.min < mr.max && sr.max > mr.max && sr.min >= mr.min {
					seedRanges = append(seedRanges, seedRange{
						id: sr.id,
						numRange: numRange{
							min: mr.max,
							max: sr.max,
						},
					})
					seedRanges[i].min = sr.min + mr.trans
					seedRanges[i].max = mr.max + mr.trans
					seedRanges[i].id++
					break

				} else if sr.max > mr.min && sr.min < mr.max && sr.max <= mr.max {
					seedRanges = append(seedRanges, seedRange{
						id: sr.id,
						numRange: numRange{
							min: sr.min,
							max: mr.min,
						},
					})
					seedRanges[i].min = mr.min + mr.trans
					seedRanges[i].max = sr.max + mr.trans
					seedRanges[i].id++
					break
				}
			}
		}

		for _, sr := range seedRanges {
			if sr.id != loc {
				continue main
			}
		}
		break
	}

	for i, seedRange := range seedRanges {
		if i == 1 {
			min = seedRange.min
		}
		if seedRange.min < min {
			min = seedRange.min
		}
	}
	return min
}

package day15

import (
	"fmt"
	"log"
	"os"
	"regexp"
	"slices"
	"strconv"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day15/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day fifteen part one: %d\n", part1(string(file)))
	fmt.Printf("day fifteen part two: %d\n", part2(string(file)))
}

func hash(seqStr string) (sum int) {
	for _, chr := range seqStr {
		sum = ((sum + int(chr)) * 17) % 256
	}
	return sum
}

func part1(input string) (sum int) {
	for _, seqStr := range strings.Split(input, ",") {
		sum += hash(seqStr)
	}
	return sum
}

type seq struct {
	label string
	add   bool
	power uint8
}

var opRe = regexp.MustCompile(`-|=`)

func parseInput(input string) (seqs []seq) {
	for _, seqStr := range strings.Split(input, ",") {
		opIdx := opRe.FindStringIndex(seqStr)
		if opIdx[1] >= len(seqStr) {
			seqs = append(seqs, seq{
				label: seqStr[:opIdx[0]],
				add:   false,
			})
			continue
		}
		power, err := strconv.Atoi(seqStr[opIdx[0]+1:])
		if err != nil {
			log.Fatalln(err)
		}
		seqs = append(seqs, seq{
			seqStr[:opIdx[0]],
			true,
			uint8(power),
		})
	}
	return seqs
}

type lens struct {
	label string
	power uint8
}

func part2(input string) (sum int) {
	boxes := make([][]lens, 256)

	for _, seq := range parseInput(input) {
		boxIdx := hash(seq.label)
		i := slices.IndexFunc(boxes[boxIdx], func(l lens) bool {
			return l.label == seq.label
		})
		if i != -1 {
			if seq.add {
				boxes[boxIdx][i].power = seq.power
			} else {
				boxes[boxIdx] = slices.Delete(boxes[boxIdx], i, i+1)
			}
		} else if seq.add {
			boxes[boxIdx] = append(boxes[boxIdx], lens{
				seq.label,
				seq.power,
			})
		}
	}
	for b, box := range boxes {
		for l, lens := range box {
			sum += (b + 1) * (l + 1) * int(lens.power)
		}
	}
	return sum
}

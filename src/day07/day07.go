package day07

import (
	"fmt"
	"log"
	"os"
	"slices"
	"strconv"
	"strings"
)

func Main() {
	file, err := os.ReadFile("src/day07/data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("day six part one: %d\n", part1(string(file)))
}

type rank uint8
type class1 uint8

const (
	high rank = iota
	one
	two
	three
	full
	four
	five
)

const (
	c12 class1 = iota
	c13
	c14
	c15
	c16
	c17
	c18
	c19
	c1t
	c1j
	c1q
	c1k
	c1a
)

var strClass1 = map[byte]class1{
	'2': c12,
	'3': c13,
	'4': c14,
	'5': c15,
	'6': c16,
	'7': c17,
	'8': c18,
	'9': c19,
	'T': c1t,
	'J': c1j,
	'Q': c1q,
	'K': c1k,
	'A': c1a,
}

type hand struct {
	cards string
	kind  rank
	bid   int
}

func processInput1(input string) (hands []hand) {
	for i, line := range strings.Split(input, "\n") {
		for j, part := range strings.Split(line, " ") {
			if j == 0 {
				cards := map[rune]int{}
				for _, char := range part {
					cards[char]++
				}

				var rnk rank
				if len(cards) == 1 {
					rnk = five
				} else if len(cards) == 2 {
					var max int
					for _, val := range cards {
						if val > max {
							max = val
						}
					}

					if max == 4 {
						rnk = four
					} else if max == 3 {
						rnk = full
					}
				} else if len(cards) == 3 {
					var max int
					for _, val := range cards {
						if val > max {
							max = val
						}
					}

					if max == 3 {
						rnk = three
					} else if max == 2 {
						rnk = two
					}
				} else if len(cards) == 4 {
					rnk = one
				} else if len(cards) == 5 {
					rnk = high
				}

				hands = append(hands, hand{
					cards: part,
					kind:  rnk,
				})
			} else if j == 1 {
				dNum, err := strconv.Atoi(part)
				if err != nil {
					log.Fatal(err)
				}
				hands[i].bid = dNum
			}
		}
	}
	return hands
}

func part1(input string) (sum int) {
	hands := processInput1(input)

	slices.SortFunc(hands, func(a, b hand) int {
		if a.kind == b.kind {
			for i := 0; i < len(a.cards); i++ {
				if a.cards[i] == b.cards[i] {
					continue
				}
				return int(strClass1[a.cards[i]]) - int(strClass1[b.cards[i]])
			}
		}
		return int(a.kind) - int(b.kind)
	})

	for i, hand := range hands {
		sum += (i + 1) * hand.bid
	}
	return sum
}

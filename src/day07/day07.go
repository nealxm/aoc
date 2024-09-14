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

	fmt.Printf("day seven part one: %d\n", part1(string(file)))
	fmt.Printf("day seven part two: %d\n", part2(string(file)))
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

type class2 uint8

const (
	c2j class2 = iota
	c22
	c23
	c24
	c25
	c26
	c27
	c28
	c29
	c2t
	c2q
	c2k
	c2a
)

var strClass2 = map[byte]class2{
	'J': c2j,
	'2': c22,
	'3': c23,
	'4': c24,
	'5': c25,
	'6': c26,
	'7': c27,
	'8': c28,
	'9': c29,
	'T': c2t,
	'Q': c2q,
	'K': c2k,
	'A': c2a,
}

func processInput2(input string) (hands []hand) {
	for i, line := range strings.Split(input, "\n") {
		for j, part := range strings.Split(line, " ") {
			if j == 0 {
				cards := map[rune]int{}
				var (
					adjLen int
					max    int
					rnk    rank
				)

				for _, char := range part {
					cards[char]++
				}
				for card, val := range cards {
					if card == 'J' {
						continue
					}
					if val > max {
						max = val
					}
				}

				adjLen = len(cards)
				if cards['J'] != 0 && adjLen != 1 {
					max += cards['J']
					adjLen--
				}

				if adjLen == 1 {
					rnk = five
				} else if adjLen == 2 {
					if max == 4 {
						rnk = four
					} else if max == 3 {
						rnk = full
					}
				} else if adjLen == 3 {
					if max == 3 {
						rnk = three
					} else if max == 2 {
						rnk = two
					}
				} else if adjLen == 4 {
					rnk = one
				} else if adjLen == 5 {
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

func part2(input string) (sum int) {
	hands := processInput2(input)

	slices.SortFunc(hands, func(a, b hand) int {
		if a.kind == b.kind {
			for i := 0; i < len(a.cards); i++ {
				if a.cards[i] == b.cards[i] {
					continue
				}
				return int(strClass2[a.cards[i]]) - int(strClass2[b.cards[i]])
			}
		}
		return int(a.kind) - int(b.kind)
	})

	for i, hand := range hands {
		sum += (i + 1) * hand.bid
	}
	return sum
}

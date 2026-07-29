package day10

import (
	at "aoc2023/common/aoc_testing"
	"os"
	"testing"
)

var example01, example02, example03, example04, example05, example06, example07, example08, input *string

func TestMain(m *testing.M) {
	example01 = at.MustRead("./data/example01.txt")
	example02 = at.MustRead("./data/example02.txt")
	example03 = at.MustRead("./data/example03.txt")
	example04 = at.MustRead("./data/example04.txt")
	example05 = at.MustRead("./data/example05.txt")
	example06 = at.MustRead("./data/example06.txt")
	example07 = at.MustRead("./data/example07.txt")
	example08 = at.MustRead("./data/example08.txt")
	input = at.MustRead("./data/input.txt")

	os.Exit(m.Run())
}

func TestD10p1(t *testing.T) {
	at.Run(t, part1, []at.Case[uint32]{
		{Name: "d10_p1_e01", Input: example01, Expected: 4},
		{Name: "d10_p1_e02", Input: example02, Expected: 4},
		{Name: "d10_p1_e03", Input: example03, Expected: 8},
		{Name: "d10_p1_e04", Input: example04, Expected: 8},
		{Name: "d10_p1_i", Input: input, Expected: 7102},
	})
}

func TestD10p2(t *testing.T) {
	at.Run(t, part2, []at.Case[uint32]{
		{Name: "d10_p2_e05", Input: example05, Expected: 4},
		{Name: "d10_p2_e06", Input: example06, Expected: 4},
		{Name: "d10_p2_e07", Input: example07, Expected: 8},
		{Name: "d10_p2_e08", Input: example08, Expected: 10},
		{Name: "d10_p2_i", Input: input, Expected: 363},
	})
}

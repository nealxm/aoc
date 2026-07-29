package day15

import (
	at "aoc2023/common/aoc_testing"
	"os"
	"testing"
)

var example01, example02, input *string

func TestMain(m *testing.M) {
	example01 = at.MustRead("./data/example01.txt")
	example02 = at.MustRead("./data/example02.txt")
	input = at.MustRead("./data/input.txt")

	os.Exit(m.Run())
}

func TestD15p1(t *testing.T) {
	at.Run(t, part1, []at.Case[uint32]{
		{Name: "d15_p1_e01", Input: example01, Expected: 52},
		{Name: "d15_p1_e02", Input: example02, Expected: 1320},
		{Name: "d15_p1_i", Input: input, Expected: 505427},
	})
}

func TestD15p2(t *testing.T) {
	at.Run(t, part2, []at.Case[uint32]{
		{Name: "d15_p2_e02", Input: example02, Expected: 145},
		{Name: "d15_p2_i", Input: input, Expected: 243747},
	})
}

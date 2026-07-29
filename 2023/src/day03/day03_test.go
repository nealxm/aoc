package day03

import (
	at "aoc2023/common/aoc_testing"
	"os"
	"testing"
)

var example01, input *string

func TestMain(m *testing.M) {
	example01 = at.MustRead("./data/example01.txt")
	input = at.MustRead("./data/input.txt")

	os.Exit(m.Run())
}

func TestD03p1(t *testing.T) {
	at.Run(t, part1, []at.Case[uint32]{
		{Name: "d03_p1_e01", Input: example01, Expected: 4361},
		{Name: "d03_p1_i", Input: input, Expected: 544664},
	})
}

func TestD03p2(t *testing.T) {
	at.Run(t, part2, []at.Case[uint32]{
		{Name: "d03_p2_e01", Input: example01, Expected: 467835},
		{Name: "d03_p2_i", Input: input, Expected: 84495585},
	})
}

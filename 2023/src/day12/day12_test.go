package day12

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

func TestD12p1(t *testing.T) {
	at.Run(t, part1, []at.Case[uint16]{
		{Name: "d12_p1_e01", Input: example01, Expected: 21},
		{Name: "d12_p1_i", Input: input, Expected: 7599},
	})
}

func TestD12p2(t *testing.T) {
	at.Run(t, part2, []at.Case[uint64]{
		{Name: "d12_p2_e01", Input: example01, Expected: 525152},
		{Name: "d12_p2_i", Input: input, Expected: 15454556629917},
	})
}

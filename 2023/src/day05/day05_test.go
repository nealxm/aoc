package day05

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

func TestD05p1(t *testing.T) {
	at.Run(t, part1, []at.Case[uint32]{
		{Name: "d05_p1_e01", Input: example01, Expected: 35},
		{Name: "d05_p1_i", Input: input, Expected: 379811651},
	})
}

func TestD05p2(t *testing.T) {
	at.Run(t, part2, []at.Case[uint32]{
		{Name: "d05_p2_e01", Input: example01, Expected: 46},
		{Name: "d05_p2_i", Input: input, Expected: 27992443},
	})
}

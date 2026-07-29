package day14

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

func TestD14p1(t *testing.T) {
	at.Run(t, part1, []at.Case[uint32]{
		{Name: "d14_p1_e01", Input: example01, Expected: 136},
		{Name: "d14_p1_i", Input: input, Expected: 112773},
	})
}

func TestD14p2(t *testing.T) {
	at.Run(t, part2, []at.Case[uint32]{
		{Name: "d14_p2_e01", Input: example01, Expected: 64},
		{Name: "d14_p2_i", Input: input, Expected: 98894},
	})
}

package day07

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

func TestD07p1(t *testing.T) {
	at.Run(t, part1, []at.Case[uint32]{
		{Name: "d07_p1_e01", Input: example01, Expected: 6440},
		{Name: "d07_p1_i", Input: input, Expected: 250058342},
	})
}

func TestD07p2(t *testing.T) {
	at.Run(t, part2, []at.Case[uint32]{
		{Name: "d07_p2_e01", Input: example01, Expected: 5905},
		{Name: "d07_p2_i", Input: input, Expected: 250506580},
	})
}

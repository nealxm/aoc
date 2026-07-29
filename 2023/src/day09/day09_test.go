package day09

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

func TestD09p1(t *testing.T) {
	at.Run(t, part1, []at.Case[int32]{
		{Name: "d09_p1_e01", Input: example01, Expected: 114},
		{Name: "d09_p1_i", Input: input, Expected: 1637452029},
	})
}

func TestD09p2(t *testing.T) {
	at.Run(t, part2, []at.Case[int32]{
		{Name: "d09_p2_e01", Input: example01, Expected: 2},
		{Name: "d09_p2_i", Input: input, Expected: 908},
	})
}

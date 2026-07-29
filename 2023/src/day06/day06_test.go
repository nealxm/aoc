package day06

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

func TestD06p1(t *testing.T) {
	at.Run(t, part1, []at.Case[uint32]{
		{Name: "d06_p1_e01", Input: example01, Expected: 288},
		{Name: "d06_p1_i", Input: input, Expected: 138915},
	})
}

func TestD06p2(t *testing.T) {
	at.Run(t, part2, []at.Case[uint32]{
		{Name: "d06_p2_e01", Input: example01, Expected: 71503},
		{Name: "d06_p2_i", Input: input, Expected: 27340847},
	})
}

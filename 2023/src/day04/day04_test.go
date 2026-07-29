package day04

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

func TestD04p1(t *testing.T) {
	at.Run(t, part1, []at.Case[uint16]{
		{Name: "d04_p1_e01", Input: example01, Expected: 13},
		{Name: "d04_p1_i", Input: input, Expected: 26218},
	})
}

func TestD04p2(t *testing.T) {
	at.Run(t, part2, []at.Case[uint32]{
		{Name: "d04_p2_e01", Input: example01, Expected: 30},
		{Name: "d04_p2_i", Input: input, Expected: 9997537},
	})
}

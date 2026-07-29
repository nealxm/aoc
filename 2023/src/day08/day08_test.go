package day08

import (
	at "aoc2023/common/aoc_testing"
	"os"
	"testing"
)

var example01, example02, example03, input *string

func TestMain(m *testing.M) {
	example01 = at.MustRead("./data/example01.txt")
	example02 = at.MustRead("./data/example02.txt")
	example03 = at.MustRead("./data/example03.txt")
	input = at.MustRead("./data/input.txt")

	os.Exit(m.Run())
}

func TestD08p1(t *testing.T) {
	at.Run(t, part1, []at.Case[uint16]{
		{Name: "d08_p1_e01", Input: example01, Expected: 2},
		{Name: "d08_p1_e02", Input: example02, Expected: 6},
		{Name: "d08_p1_i", Input: input, Expected: 18727},
	})
}

func TestD08p2(t *testing.T) {
	at.Run(t, part2, []at.Case[uint64]{
		{Name: "d08_p2_e03", Input: example03, Expected: 6},
		{Name: "d08_p2_i", Input: input, Expected: 18024643846273},
	})
}

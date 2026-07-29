package day11

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

func TestD11p1(t *testing.T) {
	at.Run(t, part1, []at.Case[uint32]{
		{Name: "d11_p1_e01", Input: example01, Expected: 374},
		{Name: "d11_p1_i", Input: input, Expected: 9605127},
	})
}

func TestD11p2(t *testing.T) {
	at.Run(t, part2, []at.Case[uint64]{
		{Name: "d11_p2_e01", Input: example01, Expected: 82000210},
		{Name: "d11_p2_i", Input: input, Expected: 458191688761},
	})
}

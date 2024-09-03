package test

import (
	"aoc2023/src/day03"
	"testing"
)

func TestD3p1(t *testing.T) {
	input1 := `467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..`
	expected1 := 4361

	if result := day03.Part1(input1); result != expected1 {
		t.Error("day 3 part 1 failed")
	}
}

package test

import (
	"aoc2023/src/day01"
	"testing"
)

func TestD1p1(t *testing.T) {
	input1 := `1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet`
	expected1 := 142

	if result := day01.Part1(input1); result != expected1 {
		t.Error("day one part one failed")
	}
}

func TestD1p2(t *testing.T) {
	input2 := `two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen`
	expected2 := 281

	if result := day01.Part2(input2); result != expected2 {
		t.Error("day one part two failed")
	}
}

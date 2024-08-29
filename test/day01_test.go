package test

import (
	"aoc2023/src/day01"
	"testing"
)

func TestOne(t *testing.T) {
	input := `1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet`
	expected := 142

	if result := day01.One(input); result != expected {
		t.Error("one failed")
	}

}

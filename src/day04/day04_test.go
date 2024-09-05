package day04

import (
	"log"
	"os"
	"testing"
)

var example, input *string

func TestMain(m *testing.M) {
	example1File, err := os.ReadFile("./data/example.txt")
	if err != nil {
		log.Fatal(err)
	}
	inputFile, err := os.ReadFile("./data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	e, i := string(example1File), string(inputFile)
	example, input = &e, &i

	code := m.Run()
	os.Exit(code)
}

type testCase struct {
	name     string
	input    *string
	expected int
}

func TestD4p1(t *testing.T) {
	testCases := []testCase{
		{"example", example, 13},
		{"input", input, 26218},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			if result := part1(*tc.input); result != tc.expected {
				t.Errorf("(d4p1) got %d, need %d", result, tc.expected)
			}
		})
	}
}

func TestD4p2(t *testing.T) {
	testCases := []testCase{
		{"example", example, 30},
		{"input", input, 9997537},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			if result := part2(*tc.input); result != tc.expected {
				t.Errorf("(d4p2) got %d, need %d", result, tc.expected)
			}
		})
	}
}

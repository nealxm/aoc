package day03

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

func TestD3p1(t *testing.T) {
	testCases := []testCase{
		{"example", example, 4361},
		{"input", input, 544664},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			if result := part1(*tc.input); result != tc.expected {
				t.Errorf("(d3p1) got %d, need %d", result, tc.expected)
			}
		})
	}
}

func TestD3p2(t *testing.T) {
	testCases := []testCase{
		{"example", example, 467835},
		{"input", input, 84495585},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			if result := part2(*tc.input); result != tc.expected {
				t.Errorf("(d3p2) got %d, need %d", result, tc.expected)
			}
		})
	}
}

package day02

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

func TestD2p1(t *testing.T) {
	testCases := []testCase{
		{"example", example, 8},
		{"input", input, 2369},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			if result := part1(*tc.input); result != tc.expected {
				t.Errorf("(d2p1) got %d, need %d", result, tc.expected)
			}
		})
	}
}

func TestD2p2(t *testing.T) {
	testCases := []testCase{
		{"example", example, 2286},
		{"input", input, 66363},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			if result := part2(*tc.input); result != tc.expected {
				t.Errorf("(d2p2) got %d, need %d", result, tc.expected)
			}
		})
	}
}

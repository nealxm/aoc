package day15

import (
	"log"
	"os"
	"testing"
)

var example1, example2, input *string

func TestMain(m *testing.M) {
	example1File, err := os.ReadFile("./data/example1.txt")
	if err != nil {
		log.Fatal(err)
	}
	example2File, err := os.ReadFile("./data/example2.txt")
	if err != nil {
		log.Fatal(err)
	}
	inputFile, err := os.ReadFile("./data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	e1, e2, i := string(example1File), string(example2File), string(inputFile)
	example1, example2, input = &e1, &e2, &i

	code := m.Run()
	os.Exit(code)
}

type testCase struct {
	name     string
	input    *string
	expected int
}

func TestD15p1(t *testing.T) {
	testCases := []testCase{
		{"example1", example1, 52},
		{"example2", example2, 1320},
		{"input", input, 505427},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			if result := part1(*tc.input); result != tc.expected {
				t.Errorf("(d15p1) got %d, need %d", result, tc.expected)
			}
		})
	}
}

func TestD15p2(t *testing.T) {
	testCases := []testCase{
		// {"example", example, 64},
		// {"input", input, 98894},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			if result := part2(*tc.input); result != tc.expected {
				t.Errorf("(d15p2) got %d, need %d", result, tc.expected)
			}
		})
	}
}

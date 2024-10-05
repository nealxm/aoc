package day08

import (
	"log"
	"os"
	"testing"
)

var example1, example2, example3, input *string

func TestMain(m *testing.M) {
	example1File, err := os.ReadFile("./data/example1.txt")
	if err != nil {
		log.Fatal(err)
	}
	example2File, err := os.ReadFile("./data/example2.txt")
	if err != nil {
		log.Fatal(err)
	}
	example3File, err := os.ReadFile("./data/example3.txt")
	if err != nil {
		log.Fatal(err)
	}
	inputFile, err := os.ReadFile("./data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	e1, e2, e3, i := string(example1File), string(example2File), string(example3File), string(inputFile)
	example1, example2, example3, input = &e1, &e2, &e3, &i

	code := m.Run()
	os.Exit(code)
}

type testCase struct {
	name     string
	input    *string
	expected int
}

func TestD8p1(t *testing.T) {
	testCases := []testCase{
		{"example1", example1, 2},
		{"example2", example2, 6},
		{"input", input, 18727},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			if result := part1(*tc.input); result != tc.expected {
				t.Errorf("(d8p1) got %d, need %d", result, tc.expected)
			}
		})
	}
}

func TestD8p2(t *testing.T) {
	testCases := []testCase{
		{"example3", example3, 6},
		{"input", input, 18024643846273},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			if result := part2(*tc.input); result != tc.expected {
				t.Errorf("(d8p2) got %d, need %d", result, tc.expected)
			}
		})
	}
}

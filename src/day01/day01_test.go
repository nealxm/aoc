package day01

import (
	"log"
	"os"
	"testing"
)

var example1, example2, input *string

func TestMain(m *testing.M) {
	exampleFile, err := os.ReadFile("./data/example1.txt")
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

	e1, e2, i := string(exampleFile), string(example2File), string(inputFile)
	example1, example2, input = &e1, &e2, &i

	code := m.Run()
	os.Exit(code)
}

type testCase struct {
	name     string
	input    *string
	expected int
}

func TestD1p1(t *testing.T) {
	testCases := []testCase{
		{"example1", example1, 142},
		{"input", input, 54697},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			if result := part1(*tc.input); result != tc.expected {
				t.Errorf("(d1p1) got %d, need %d", result, tc.expected)
			}
		})
	}
}

func TestD1p2(t *testing.T) {
	testCases := []testCase{
		{"example2", example2, 281},
		{"input", input, 54885},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			if result := part2(*tc.input); result != tc.expected {
				t.Errorf("(d1p2) got %d, need %d", result, tc.expected)
			}
		})
	}
}

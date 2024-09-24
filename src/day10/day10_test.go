package day10

import (
	"log"
	"os"
	"testing"
)

var example1a, example1b, example2a, example2b, example3a, example3b, example4a, example4b, input *string

func TestMain(m *testing.M) {
	example1aFile, err := os.ReadFile("./data/example1a.txt")
	if err != nil {
		log.Fatal(err)
	}
	example1bFile, err := os.ReadFile("./data/example1b.txt")
	if err != nil {
		log.Fatal(err)
	}
	example2aFile, err := os.ReadFile("./data/example2a.txt")
	if err != nil {
		log.Fatal(err)
	}
	example2bFile, err := os.ReadFile("./data/example2b.txt")
	if err != nil {
		log.Fatal(err)
	}
	example3aFile, err := os.ReadFile("./data/example3a.txt")
	if err != nil {
		log.Fatal(err)
	}
	example3bFile, err := os.ReadFile("./data/example3b.txt")
	if err != nil {
		log.Fatal(err)
	}
	example4aFile, err := os.ReadFile("./data/example4a.txt")
	if err != nil {
		log.Fatal(err)
	}
	example4bFile, err := os.ReadFile("./data/example4b.txt")
	if err != nil {
		log.Fatal(err)
	}
	inputFile, err := os.ReadFile("./data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	e1a, e1b, e2a, e2b, e3a, e3b, e4a, e4b, i := string(example1aFile), string(example1bFile), string(example2aFile), string(example2bFile), string(example3aFile), string(example3bFile), string(example4aFile), string(example4bFile), string(inputFile)
	example1a, example1b, example2a, example2b, example3a, example3b, example4a, example4b, input = &e1a, &e1b, &e2a, &e2b, &e3a, &e3b, &e4a, &e4b, &i

	code := m.Run()
	os.Exit(code)
}

type testCase struct {
	name     string
	input    *string
	expected int
}

func TestD10p1(t *testing.T) {
	testCases := []testCase{
		{"example1a", example1a, 4},
		{"example1b", example1b, 4},
		{"example2a", example2a, 8},
		{"example2b", example2b, 8},
		{"input", input, 7102},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			if result := part1(*tc.input); result != tc.expected {
				t.Errorf("(d10p1) got %d, need %d", result, tc.expected)
			}
		})
	}
}

func TestD10p2(t *testing.T) {
	testCases := []testCase{
		{"example3a", example3a, 4},
		{"example3b", example3b, 4},
		{"example4a", example4a, 8},
		{"example4b", example4b, 10},
		{"input", input, 363},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			if result := part2(*tc.input); result != tc.expected {
				t.Errorf("(d10p2) got %d, need %d", result, tc.expected)
			}
		})
	}
}

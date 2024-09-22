package day10

import (
	"log"
	"os"
	"testing"
)

var example1a, example1b, example2a, example2b, input *string

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
	inputFile, err := os.ReadFile("./data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	e1a, e1b, e2a, e2b, i := string(example1aFile), string(example1bFile), string(example2aFile), string(example2bFile), string(inputFile)
	example1a, example1b, example2a, example2b, input = &e1a, &e1b, &e2a, &e2b, &i

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

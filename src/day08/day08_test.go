package day08

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

func TestD8p1(t *testing.T) {
	testCases := []testCase{
		{"example1", example1, 2},
		{"example2", example2, 6},
		{"input", input, 18727},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			if result := part1(*tc.input); result != tc.expected {
				t.Errorf("(d7p1) got %d, need %d", result, tc.expected)
			}
		})
	}
}

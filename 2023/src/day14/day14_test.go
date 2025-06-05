package day14

import (
	"log"
	"os"
	"testing"
)

var example, input *string

func TestMain(m *testing.M) {
	exampleFile, err := os.ReadFile("./data/example.txt")
	if err != nil {
		log.Fatal(err)
	}
	inputFile, err := os.ReadFile("./data/input.txt")
	if err != nil {
		log.Fatal(err)
	}

	e, i := string(exampleFile), string(inputFile)
	example, input = &e, &i

	code := m.Run()
	os.Exit(code)
}

type testCase struct {
	name     string
	input    *string
	expected int
}

func TestD13p1(t *testing.T) {
	testCases := []testCase{
		{"example", example, 136},
		{"input", input, 112773},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			if result := part1(*tc.input); result != tc.expected {
				t.Errorf("(d14p1) got %d, need %d", result, tc.expected)
			}
		})
	}
}

func TestD12p2(t *testing.T) {
	testCases := []testCase{
		{"example", example, 64},
		{"input", input, 98894},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			if result := part2(*tc.input); result != tc.expected {
				t.Errorf("(d14p2) got %d, need %d", result, tc.expected)
			}
		})
	}
}

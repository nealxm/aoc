package aoc_testing

import (
	"log"
	"os"
	"testing"
)

type Integer interface {
	~int8 | ~int16 | ~int32 | ~int64 | ~uint8 | ~uint16 | ~uint32 | ~uint64 | ~int
}

func MustRead(path string) *string {
	fileBytes, err := os.ReadFile(path)
	if err != nil {
		log.Fatal(err)
	}

	s := string(fileBytes)
	return &s
}

type Case[T Integer] struct {
	Name     string
	Input    *string
	Expected T
}

func Run[T Integer](t *testing.T, fn func(string) T, cases []Case[T]) {
	t.Helper()

	for _, tc := range cases {
		t.Run(tc.Name, func(t *testing.T) {
			if got := fn(*tc.Input); got != tc.Expected {
				t.Errorf("got %d, need %d", got, tc.Expected)
			}
		})
	}
}

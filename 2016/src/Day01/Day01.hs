module Day01.Day01 (run) where

import Data.Kind qualified as K (Type)
import Data.Text qualified as T (Text, head, splitOn, tail, unpack)
import Data.Text.IO qualified as T (readFile)
import Prelude (Enum, Eq, IO, Int, abs, error, map, null, otherwise, pred, putStrLn, read, show, succ, until, (+), (++), (-), (.), (==))

run :: IO ()
run = do
    input <- T.readFile "./src/Day01/data/input.txt"
    putStrLn ("2016:d01p1 - " ++ show (part1 input))

type Dir :: K.Type
data Dir = North | East | South | West
    deriving stock (Eq, Enum)

type Instr :: K.Type
data Instr = TurnLeft {dist :: Int} | TurnRight {dist :: Int}

type State :: K.Type
data State = State {x :: Int, y :: Int, facing :: Dir, instrs :: [Instr]}

parseInstr :: T.Text -> Instr
parseInstr instr
    | dir == 'R' = TurnRight{dist}
    | dir == 'L' = TurnLeft{dist}
    | otherwise = error "failed to parse instruction"
  where
    dir = T.head instr
    dist = (read . T.unpack . T.tail) instr

stateInit :: T.Text -> State
stateInit input = State{x = 0, y = 0, facing = North, instrs = map parseInstr (T.splitOn ", " input)}

turnLeft, turnRight :: Dir -> Dir
turnLeft dir
    | dir == North = West
    | otherwise = pred dir
turnRight dir
    | dir == West = North
    | otherwise = succ dir

turn :: State -> Dir
turn state = case instrs state of
    [] -> dir
    instr : _ -> case instr of
        TurnLeft _ -> turnLeft dir
        TurnRight _ -> turnRight dir
  where
    dir = facing state

move :: State -> (Int, Int)
move state = case instrs state of
    [] -> (x state, y state)
    instr : _ -> case turn state of
        North -> (x state, y state + dist instr)
        South -> (x state, y state - dist instr)
        East -> (x state + dist instr, y state)
        West -> (x state - dist instr, y state)

applyInstr :: State -> State
applyInstr state = case instrs state of
    [] -> state
    (_ : xs) -> State newX newY (turn state) xs
  where
    (newX, newY) = move state

part1 :: T.Text -> Int
part1 input = abs (x finalState) + abs (y finalState)
  where
    initialState = stateInit input
    finalState = until (null . instrs) applyInstr initialState

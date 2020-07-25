#pragma once

using MinMaxValue = int;
using Result = pair<Move, MinMaxValue>;

Result computeBestMove(const Board& b, const Moves& possibleMoves);


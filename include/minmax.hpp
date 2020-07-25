#pragma once

using MinMaxValue = int;
using Result = pair<Move, MinMaxValue>;

Result computeBestMove(const Board&, const Moves&);


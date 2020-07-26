#pragma once

using MinMaxValue = int;
using Result = pair<Move, MinMaxValue>;

enum class Player { Human, AI };

Player other(Player);

Result computeBestMove(const Board&, const Moves&);
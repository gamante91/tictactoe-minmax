#pragma once

using Result = pair<Move, int>;

Result computeBestMove(const Board& b, const Moves& possibleMoves);


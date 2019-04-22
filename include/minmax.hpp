#ifndef MinMax_h
#define MinMax_h

using Result = pair<Move, int>;

Result computeBestMove(const Board& b, const Moves& possibleMoves);

#endif /* MinMax_h */

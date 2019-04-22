#ifndef Utilities_h
#define Utilities_h

#include "board.hpp"

namespace Utilities {
   
BoardState checkBoard(const Board& b);
    
bool isValid(const Board& b, const Move& m);
bool isEmpty(const Board& b);
bool isFull(const Board& b);


} // namespace Utilities

#endif /* Utilities_h */

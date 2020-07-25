#pragma once

#include <board.hpp>

namespace Utilities {
   
BoardState checkBoard(const Board&);
    
bool isValid(const Board&, const Move&);
bool isEmpty(const Board&);
bool isFull(const Board&);


} // namespace Utilities
#include "include/utilities.hpp"
#include "include/board.hpp"

namespace Utilities {
    
    bool isValid(const Board& b, const Move& m)
    {
        auto withinBounds = [](int i){ return i >= 0 and i < 3;};
        
        if (not withinBounds(m.first) or not withinBounds(m.second))
            return false;
        
        return b.at(m.first,m.second) == Mark::None;
    }
    
    bool isEmpty(const Board& b)
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (b.at(i,j) != Mark::None)
                    return false;
        
        return true;
    }
    
    bool isFull(const Board& b)
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (b.at(i,j) == Mark::None)
                    return false;
        
        return true;
    }
    
    BoardState checkRows(const Board& b)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (b.at(i,0) == b.at(i,1) and b.at(i,1) == b.at(i,2))
                if (b.at(i,0) == Mark::Human)
                    return BoardState::HumanWon;
                else if (b.at(i,0) == Mark::AI)
                    return BoardState::AIWon;
        }
        
        return BoardState::Ongoing;
    }
    
    BoardState checkCols(const Board& b)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (b.at(0,i) == b.at(1,i) and b.at(1,i) == b.at(2,i))
                if (b.at(0,i) == Mark::Human)
                    return BoardState::HumanWon;
                else if (b.at(0,i) == Mark::AI)
                    return BoardState::AIWon;
        }
        
        return BoardState::Ongoing;
    }
    
    BoardState checkDiagonal(const Board& b)
    {
        if (b.at(0,0) == b.at(1,1) and b.at(1,1) == b.at(2,2))
            if (b.at(0,0) == Mark::Human)
                return BoardState::HumanWon;
            else if (b.at(0,0) == Mark::AI)
                return BoardState::AIWon;
        
        if (b.at(0,2) == b.at(1,1) and b.at(1,1) == b.at(2,0))
            if (b.at(0,2) == Mark::Human)
                return BoardState::HumanWon;
            else if (b.at(0,2) == Mark::AI)
                return BoardState::AIWon;
        
        return BoardState::Ongoing;
    }
    
    BoardState checkBoard(const Board& b)
    {
        auto rowsState = checkRows(b);
        if (rowsState != BoardState::Ongoing)
            return rowsState;
        
        auto colsState = checkCols(b);
        if (colsState != BoardState::Ongoing)
            return colsState;
        
        auto diagState = checkDiagonal(b);
        if (diagState != BoardState::Ongoing)
            return diagState;
        
        if (isFull(b))
            return BoardState::Tie;
        
        return BoardState::Ongoing;
    }
    
} // namespace Utilities


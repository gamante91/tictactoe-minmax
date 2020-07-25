#include <iostream>
#include <vector>

#include <board.hpp>

namespace {

Mark convert(char c)
{
    if (c == 'X')
        return Mark::Human;
    if (c == 'O')
        return Mark::AI;

    return Mark::None;
}
    
} // namespace

Board::Board() : m_board(vector<vector<Mark>>(n,  vector<Mark>(n, Mark::None))) {}

Board::Board(const Board& b) : m_board(b.m_board) {}

Board::Board(const vector<vector<char>>& board)
{
    for (const auto& row : board)
    {
        vector<Mark> newRow;
        for (const auto& elem : row)
            newRow.emplace_back(convert(elem));
        m_board.emplace_back(newRow);
    }
}

Board::Board(const Board& b, const Move& m, Mark x) : m_board(b.m_board) { update(m,x); }

void Board::update(const Move& m, Mark x)
{
    m_board[m.first][m.second] = x;
}

Moves Board::getPossibleMoves() const
{
    Moves possibleMoves;

    for (int i = 0; i < Board::n; ++i)
        for (int j = 0; j < Board::n; ++j)
            if (m_board[i][j] == Mark::None)
                possibleMoves.emplace_back(make_pair(i,j));

    return possibleMoves;
}

Mark Board::at(int i, int j) const
{
    return m_board[i][j];
}

ostream& operator<<(ostream& o, const Mark& m)
{
    if (m == Mark::Human)
        o << "X";
    else if (m == Mark::AI)
        o << "O";
    else if (m == Mark::None)
        o << "-";
    
    return o;
}

ostream& operator<<(ostream& o, const Board& b)
{
    for (int i = 0; i < Board::n; ++i)
    {
        for (int j = 0; j < Board::n; ++j)
            o << b.at(i,j);
        o << endl;
    }
    
    return o;
}

ostream& operator<<(ostream& o, const Move& move)
{
    o << "<" << move.first + 1 << "," << move.second + 1 << ">";
    
    return o;
}

ostream& operator<<(ostream& o, const Moves& moves)
{
    for (const Move& move : moves)
        o << move << " ";
    
    return o;
}

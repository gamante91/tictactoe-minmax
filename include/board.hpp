#pragma once

#include <vector>
#include <string>
#include <ostream>

using namespace std;
using Move = pair<int,int>;
using Moves = vector<Move>;

enum class Mark { Human, AI, None };
enum class BoardState { HumanWon, AIWon, Tie, Ongoing };

class Board {
public:
    static const int n = 3;

    Board();
    Board(const Board&);
    Board(const vector<vector<char>>&);
    Board(const Board& b, const Move&, Mark);
    
    void update(const Move&, Mark);
    Moves getPossibleMoves() const;
    Mark at(int, int) const;

private:
    vector<vector<Mark>> m_board;
};

ostream& operator<<(ostream&, const Move&);
ostream& operator<<(ostream&, const Moves&);
ostream& operator<<(ostream&, const Mark&);
ostream& operator<<(ostream&, const Board&);
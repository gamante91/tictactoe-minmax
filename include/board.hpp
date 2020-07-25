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
    Board(const Board& b);
    Board(const vector<vector<char>>& board);
    Board(const Board& b, const Move& m, Mark x);
    
    void update(const Move& m, Mark x);
    Moves getPossibleMoves() const;
    Mark at(int i, int j) const;

private:
    vector<vector<Mark>> m_board;
};

ostream& operator<<(ostream& o, const Move& m);
ostream& operator<<(ostream& o, const Moves& m);
ostream& operator<<(ostream& o, const Mark& m);
ostream& operator<<(ostream& o, const Board& b);

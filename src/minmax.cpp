#include <algorithm>
#include <iostream>
#include <sstream>

#include <board.hpp>
#include <minmax.hpp>
#include <utilities.hpp>

using namespace std;

enum class Player {Human, AI};

Player other(Player p) {
    return p == Player::Human ? Player::AI : Player::Human;
}

int recursiveMinMax(const Board& b, Player p) {
    auto state = Utilities::checkBoard(b);
    auto possibleMoves = b.getPossibleMoves();
    
    if (state == BoardState::AIWon)
        return +10;
    if (state == BoardState::HumanWon)
        return -10;
    if(state == BoardState::Tie || possibleMoves.empty())
        return 0;

    vector<int> outcomes;
    
    for (const auto& move : possibleMoves) {
        Board newBoard(b, move, p == Player::Human ? Mark::Human : Mark::AI);
        int outcome = recursiveMinMax(newBoard, other(p));
        outcomes.emplace_back(outcome);
    }
    
    int minMaxValue = (p == Player::AI) ? *max_element(outcomes.begin(),outcomes.end())
                                        : *min_element(outcomes.begin(),outcomes.end());
    
    return minMaxValue;
}

namespace {
    ostream& operator<<(ostream& o, const Move& move) {
        o << "(" << move.first + 1 << ", " << move.second + 1 << ")";

        return o;
    }

    ostream& operator<<(ostream& o, const vector<Result>& results) {
        for (const auto& result : results)
            o << "Move: " << result.first << " with MinMaxValue: " << result.second << endl;

        return o;
    }
}

Result computeBestMove(const Board& b, const Moves& possibleMoves) {
    if (Utilities::isEmpty(b))
        return make_pair(make_pair(1,1), +10);
    
    vector<Result> outcomes;
    
    for (const auto& move : possibleMoves) {
        Board newBoard(b, move, Mark::AI);
        
        int minmaxValue = recursiveMinMax(newBoard, Player::Human);        
        outcomes.emplace_back(make_pair(move, minmaxValue));
    }

    cout << "AI possible moves:" << endl
         << outcomes << endl;
    
    auto bestMove = *max_element(outcomes.cbegin(), outcomes.cend(),
                                 [](const Result& outcome1, const Result& outcome2){ return outcome1.second < outcome2.second; });
                                      
    return bestMove;
}

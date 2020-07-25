#include <algorithm>
#include <iostream>
#include <sstream>

#include <board.hpp>
#include <minmax.hpp>
#include <utilities.hpp>

using namespace std;

enum class Player { Human, AI };

Player other(Player p) {
    return p == Player::Human ? Player::AI : Player::Human;
}

int recursiveMinMax(const Board& board, Player player) {
    auto state = Utilities::checkBoard(board);
    auto possibleMoves = board.getPossibleMoves();
    
    if (state == BoardState::AIWon)
        return +10;
    if (state == BoardState::HumanWon)
        return -10;
    if(state == BoardState::Tie || possibleMoves.empty())
        return 0;

    vector<int> outcomes;
    
    for (const auto& move : possibleMoves) {
        Board newBoard(board, move, player == Player::Human ? Mark::Human : Mark::AI);
        int outcome = recursiveMinMax(newBoard, other(player));
        outcomes.emplace_back(outcome);
    }
    
    int minMaxValue = (player == Player::AI) ? *max_element(outcomes.begin(),outcomes.end())
                                             : *min_element(outcomes.begin(),outcomes.end());
    
    return minMaxValue;
}

ostream& operator<<(ostream& o, const vector<Result>& results) {
    for (const auto& result : results)
        o << "Move: " << result.first << " with MinMaxValue: " << result.second << endl;

    return o;
}

Result computeBestMove(const Board& board, const Moves& possibleMoves) {
    if (Utilities::isEmpty(board))
        return make_pair(make_pair(1,1), +10);
    
    vector<Result> outcomes;
    
    for (const auto& move : possibleMoves) {
        Board newBoard(board, move, Mark::AI);
        
        int minmaxValue = recursiveMinMax(newBoard, Player::Human);        
        outcomes.emplace_back(make_pair(move, minmaxValue));
    }

    cout << "AI possible moves:" << endl
         << outcomes << endl;
    
    auto bestMove = *max_element(outcomes.cbegin(), outcomes.cend(),
                                 [](const Result& outcome1, const Result& outcome2){ return outcome1.second < outcome2.second; });
                                      
    return bestMove;
}

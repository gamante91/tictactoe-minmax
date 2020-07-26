#include <algorithm>
#include <iostream>
#include <sstream>
#include <random>
#include <time.h>

#include <board.hpp>
#include <minmax.hpp>
#include <utilities.hpp>

using namespace std;

enum class Player { Human, AI };

Player other(Player p) {
    return p == Player::Human ? Player::AI : Player::Human;
}

MinMaxValue recursiveMinMax(const Board& board, Player player) {
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
        auto newBoard = Board(board, move, player == Player::Human ? Mark::Human : Mark::AI);
        auto outcome = recursiveMinMax(newBoard, other(player));
        outcomes.emplace_back(outcome);
    }
    
    auto minMaxValue = (player == Player::AI) ? *max_element(outcomes.cbegin(),outcomes.cend())
                                              : *min_element(outcomes.cbegin(),outcomes.cend());
    
    return minMaxValue;
}

ostream& operator<<(ostream& o, const vector<Result>& results) {
    for (const auto& result : results)
        o << "Move: " << result.first << " with MinMaxValue: " << result.second << endl;

    return o;
}

Result selectBestMove(const vector<Result>& outcomes) {
    auto bestMove = max_element(outcomes.begin(),
                                outcomes.end(),
                                [](const Result& outcome1, const Result& outcome2){ return outcome1.second < outcome2.second; });
    vector<Result> bestMoves;
    copy_if(outcomes.begin(),
            outcomes.end(),
            back_inserter(bestMoves),
            [&bestMove](const auto& result){ return result.second == bestMove->second; });
    static auto seed = time(nullptr);
    srand(seed);
    auto it = outcomes.begin();
    std::advance(it, std::rand() % bestMoves.size());

    return *it;
}

Result computeBestMove(const Board& board, const Moves& possibleMoves) {
    vector<Result> outcomes;
    
    for (const auto& move : possibleMoves) {
        Board newBoard(board, move, Mark::AI);
        
        auto minmaxValue = recursiveMinMax(newBoard, Player::Human);        
        outcomes.emplace_back(make_pair(move, minmaxValue));
    }

    cout << "AI possible moves:" << endl
         << outcomes << endl;
    
    return selectBestMove(outcomes);
}

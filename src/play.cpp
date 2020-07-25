#include <iostream>

#include <board.hpp>
#include <minmax.hpp>
#include <utilities.hpp>

using namespace std;

Move getHumanMove(const Board& b)
{
    Move m;

    do {
        int i,j;
        cout << "Enter a valid move:" << endl;
        cout << "row: "; cin >> i;
        cout << "col: "; cin >> j;
        m = make_pair(--i, --j);
    } while (not Utilities::isValid(b, m));
    
    return m;
}

BoardState playAI(Board& b)
{
    auto validMoves = b.getPossibleMoves();
    
    if (not validMoves.empty())
    {
        auto result = computeBestMove(b, validMoves);
        const Move& selectedMove = result.first;
        int minMaxValue = result.second;
        b.update(selectedMove, Mark::AI);
        
        cout << "AI selected move " << selectedMove << " with minmax value " << minMaxValue << endl;
        cout << b;
    }
    
    return Utilities::checkBoard(b);
}

BoardState playHuman(Board& b)
{
    Move humanSelectedMove = getHumanMove(b);
    b.update(humanSelectedMove, Mark::Human);
    
    cout << "You selected move " << humanSelectedMove << endl;
    cout << b;
    
    return Utilities::checkBoard(b);
}

int main() {
    Board b;
    bool done = false;
    BoardState state = BoardState::Ongoing;
    
    while (not done) {
        state = playAI(b);
        done = state != BoardState::Ongoing;
        
        if (not done) {
            state = playHuman(b);
            done = state != BoardState::Ongoing;
        }
    }
    
    if (state == BoardState::HumanWon)
        cout << "Congratulations, you won!" << endl;
    else if (state == BoardState::AIWon)
        cout << "AI won!" << endl;
    else
        cout << "It's a tie, well done!" << endl;

    return 0;
}

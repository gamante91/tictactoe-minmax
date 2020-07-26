#include <iostream>
#include <time.h>

#include <board.hpp>
#include <minmax.hpp>
#include <utilities.hpp>

using namespace std;

Move getHumanMove(const Board& board) {
    Move move;

    do {
        int i = 0, j = 0;
        cout << "Enter a valid move:" << endl;
        cout << "row: "; cin >> i;
        cout << "col: "; cin >> j;
        move = make_pair(--i, --j);
    } while (not Utilities::isValid(board, move));
    
    return move;
}

BoardState play(Board& board, Player player) {
    if (player == Player::AI) {
        const auto& validMoves = board.getPossibleMoves();
    
        if (not validMoves.empty()) {
            const auto& [selectedMove, minMaxValue] = computeBestMove(board, validMoves);
            board.update(selectedMove, Mark::AI);
        
            cout << "AI selected move " << selectedMove << " with minmax value " << minMaxValue << endl;
            cout << board;
        }
    } else {
        Move humanSelectedMove = getHumanMove(board);
        board.update(humanSelectedMove, Mark::Human);
    
        cout << "You selected move " << humanSelectedMove << endl;
        cout << board;
    }

    return Utilities::checkBoard(board);
}

Player selectRandomPlayer() {
    static auto seed = time(nullptr);
    srand(seed);

    return Player(std::rand() % 2);
}

int main() {
    Board board;
    bool done = false;
    BoardState state = BoardState::Ongoing;
    Player player1 = selectRandomPlayer();
    Player player2 = other(player1);

    cout << (player1 == Player::AI ? "AI" : "You") << " will start the game!" << endl;
    
    while (not done) {
        state = play(board, player1);
        done = state != BoardState::Ongoing;
        
        if (not done) {
            state = play(board, player2);
            done = state != BoardState::Ongoing;
        }
    }
    
    if (state == BoardState::HumanWon) {
        cout << "Congratulations, you won!" << endl;
    } else if (state == BoardState::AIWon) {
        cout << "AI won!" << endl;
    } else {
        cout << "It's a tie, well done!" << endl;
    }

    return 0;
}

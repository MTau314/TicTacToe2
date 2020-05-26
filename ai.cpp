/* Matthew Louigi Cabie Ong 2020 */
#include "ai.h"
#include <ctime>
#include <iostream>
#include <random>

namespace Signature //do not touch
{
    char clear = 'i';
    int W = 10;
    int L = -10;
    int T = 0;
};

void AI::setSignature(playField_t& board)
{
    std::cout << "Analyzing...\n";
    if (!bHard)
    {
        static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) }; //seed
        std::uniform_int_distribution<> die{ 1,9 };
        bool bValid{ false };

        while (!bValid)
        {
            int nLocation{ die(mt) };
            if (board[nLocation] != Signature::x && board[nLocation] != Signature::o)
            {
                std::cout << "Choosing position " << nLocation << '\n';
                board[nLocation] = m_signature; //marks location
                std::cout << std::endl;
                return;
            }
        }
    }

    playField_t aiBoard{ board };
    int best{ -1000 };
    int index{};

    for (int i{ 1 }; i < static_cast<int>(aiBoard.size()); ++i) //move through cells
    {
        if (aiBoard[i] != Signature::x && aiBoard[i] != Signature::o) //ie empty
        {
            aiBoard[i] = m_signature; //ai marks the location
            int score{ minimax(aiBoard, false, 0) }; //play as human
            aiBoard[i] = Signature::clear;

            if (score > best)
            {
                best = score;
                index = i;
            }
        }
    }

    //finalized routine
    std::cout << "Choosing postion " << index << '\n';
    board[index] = m_signature; //commit to location
    std::cout << std::endl;
    return;

}

bool AI::isMovesLeft(playField_t& grid)
{
    for (int nIndex{ 1 }; nIndex < 9; nIndex++)
        if (grid[nIndex] != Signature::x && grid[nIndex] != Signature::o) //ie empty
            return true; //there is still a location 

    return false; //no more locations
}

int AI::checkGlobalWinner(playField_t& board)
{
    int centre{ 5 };

    //row
    for (int r{ 1 }; r < 8; r += 3) //iterates through column 1 of all rows
    {
        if (board[r] == Signature::x && board[r + 1] == Signature::x && board[r + 2] == Signature::x) //iterate adjacent column locations
            return Signature::L;
        else if (board[r] == Signature::o && board[r + 1] == Signature::o && board[r + 2] == Signature::o) //iterate adjacent column locations
            return Signature::W;
    }

    //col
    for (int c{ 1 }; c < 4; ++c) //iterates through row 1 of all columns
    {
        if (board[c] == Signature::x && board[c + 3] == Signature::x && board[c + 6] == Signature::x) //iterate adjacent row locations
            return Signature::L;
        else if (board[c] == Signature::o && board[c + 3] == Signature::o && board[c + 6] == Signature::o) //iterate adjacent row locations
            return Signature::W;
    }

    //dia prelim check => if centre is not filled dont bother checking
    if (board[centre] == Signature::x || board[centre] == Signature::o)
    {
        if (board[centre - 4] == Signature::x && board[centre + 4] == Signature::x && board[centre] == Signature::x)
            return Signature::L;
        else if (board[centre - 2] == Signature::x && board[centre + 2] == Signature::x && board[centre] == Signature::x)
            return Signature::L;
        if (board[centre - 4] == Signature::o && board[centre + 4] == Signature::o && board[centre] == Signature::o)
            return Signature::W;
        else if (board[centre - 2] == Signature::o && board[centre + 2] == Signature::o && board[centre] == Signature::o)
            return Signature::W;
    }

    return 0; //allc checks are done => tied state probably
}

int AI::minimax(playField_t& state, bool isMax, int depth) //depth not implemented
{
    //state is a copy of the real gameboard
    int score = checkGlobalWinner(state);
    //terminal conditions
    if (score == Signature::W || score == Signature::L) //if one player win
        return score; //return state of winnings relative to AI
    if (!isMovesLeft(state))
        return Signature::T; //tied state

    if (isMax) //ai turn
    {
        int best{ -1000 };

        for (int i{ 1 }; i < static_cast<int>(state.size()); ++i) //check all cells
        {
            if (state[i] != Signature::x && state[i] != Signature::o) //ie clear
            {
                state[i] = Signature::o; //marks as ai
                best = std::max(best, minimax(state, false, depth + 1)); //play as human and get Max value
                state[i] = Signature::clear; //undoes mark
            }
        }
        return best;
    }

    else //human turn
    {
        int best{ 1000 };

        for (int j{ 1 }; j < static_cast<int>(state.size()); ++j) //check all cells
        {
            if (state[j] != Signature::x && state[j] != Signature::o) //ie clear
            {
                state[j] = Signature::x; //marks as human
                best = std::min(best, minimax(state, true, depth + 1)); //play as ai
                state[j] = Signature::clear;
            }
        }
        return best;
    }
}

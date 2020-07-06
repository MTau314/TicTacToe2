#include "player.h"
#include <iostream>

namespace Signature //change the icons for fun
{
    char x = 'o';
    char o = 'x';
    char h = '-';
    char v = '|';
    char d = '/';
};

void Player::setSignature(playField_t& board)
{
    int nIndex{};
    do
    {
        std::cout << "Player " << m_id << " choose a location to place: ";
        std::cin >> nIndex;

    } while (board[nIndex] == Signature::x || board[nIndex] == Signature::o || std::cin.fail() || nIndex > 9 || nIndex < 1);

    board[nIndex] = m_signature;
    std::cin.ignore(32767, '\n');
    std::cout << std::endl;
    return;
}

bool Player::checkWinner(playField_t& board)
{
    bool winner{ false };
    //row check
    for (int r{ 1 }; r < 8; r += 3) //iterates through column 1 of all rows
        if (board[r] == m_signature && board[r + 1] == m_signature && board[r + 2] == m_signature) //iterate adjacent column locations
        {
            board[r] = board[r + 1] = board[r + 2] = Signature::h;
            winner = true;
        }

    //col check
    for (int c{ 1 }; !winner && c < 4; ++c) //iterates through row 1 of all columns
        if (board[c] == m_signature && board[c + 3] == m_signature && board[c + 6] == m_signature) //iterate adjacent row locations
        {
            board[c] = board[c + 3] = board[c + 6] = Signature::v;
            winner = true;
        }

    //diagonal check
    int centre{ 5 };
    if (!winner && board[centre] == m_signature)
    {
        bool rightDiag{ board[centre - 4] == m_signature && board[centre + 4] == m_signature },
             leftDiag{ board[centre - 2] == m_signature && board[centre + 2] == m_signature };
        if (rightDiag)
            board[centre] = board[centre - 4] = board[centre + 4] = Signature::d;
        if (leftDiag)
            board[centre] = board[centre - 2] = board[centre + 2] = Signature::d;
        winner = (rightDiag || leftDiag);
    }

    m_win = winner;
    return m_win; //all checks fail
}

bool isMovesLeft(playField_t& grid)
{
    for (int nIndex{ 1 }; nIndex < static_cast<int>(grid.size()); nIndex++)
        if (grid[nIndex] != Signature::x && grid[nIndex] != Signature::o) //ie empty
            return true; //there is still a location 

    return false; //no more locations
}
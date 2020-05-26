/* Matthew Louigi Cabie Ong 2020 */
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

    while (true)
    {
        std::cout << "Player " << m_id << " choose a location to place: ";
        std::cin >> nIndex;

        if (board[nIndex] == Signature::x || board[nIndex] == Signature::o || std::cin.fail() || nIndex > 9 || nIndex < 1)
        {
            std::cout << "Invalid location\n";
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            continue;
        }
        else
        {
            board[nIndex] = m_signature;
            std::cin.ignore(32767, '\n');
            std::cout << std::endl;
            return;
        }
    }
}

bool Player::checkWinner(playField_t& board)
{
    //row check
    for (int r{ 1 }; r < 8; r += 3) //iterates through column 1 of all rows
        if (board[r] == m_signature && board[r + 1] == m_signature && board[r + 2] == m_signature) //iterate adjacent column locations
        {
            board[r] = board[r + 1] = board[r + 2] = Signature::h;
            return (m_win = true);
        }


    //col check
    for (int c{ 1 }; c < 4; ++c) //iterates through row 1 of all columns
        if (board[c] == m_signature && board[c + 3] == m_signature && board[c + 6] == m_signature) //iterate adjacent row locations
        {
            board[c] = board[c + 3] = board[c + 6] = Signature::v;
            return (m_win = true);
        }


    //diagonal check
    int centre{ 5 }; //not optimized!
    if (board[centre] == m_signature)
    {
        //1,5,9 diagonal
        if (board[centre - 4] == m_signature && board[centre + 4] == m_signature)
        {
            board[centre] = board[centre - 4] = board[centre + 4] = Signature::d;
            return (m_win = true);
        }
        //3,5,7 diagonal
        else if (board[centre - 2] == m_signature && board[centre + 2] == m_signature)
        {
            board[centre] = board[centre - 2] = board[centre + 2] = Signature::d;
            return (m_win = true);
        }
    }

    return false; //all checks fail
}

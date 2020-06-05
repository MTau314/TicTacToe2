/* Matthew Louigi Cabie Ong 2020 */
#include "ai.h"
#include "player.h"
#include <iostream>

void printArray(const playField_t& grid)
{
    for (int element{ 1 }; element < static_cast<int>(grid.size()); ++element)
    {
        std::cout << "|  " << grid[element] << "  ";

        if (element % 3 == 0)
            std::cout << "|\n|-----|-----|-----|\n";
    }
}

bool fullBoard(const playField_t& grid)
{
    for (int nIndex{ 1 }; nIndex < static_cast<int>(grid.size()); ++nIndex)
        if (grid[nIndex] != Signature::x && grid[nIndex] != Signature::o)
            return false; //there is still a location 

    return true; //it is full
}

void playTicTacToe(playField_t& board, AI& p1, Player& p2) //function overload for 1player
{
    bool p1turn{ true };

    while (!fullBoard(board))
    {
        printArray(board);
        if (p1turn)
        {
            p1.setSignature(board);
            if (p1.checkWinner(board))
                break;

            p1turn = false;
        }

        else
        {
            p2.setSignature(board);
            if (p2.checkWinner(board))
                break;

            p1turn = true;
        }
    }
    printArray(board);

    if (p1.hasWon())
        std::cout << "Player 1 has won!\n\a";
    else if (p2.hasWon())
        std::cout << "Player 2 has won!\n\a";
    else if (fullBoard(board) && !p1.hasWon() && !p2.hasWon())
        std::cout << "Tied game!\n";
    return;
}

void playTicTacToe(playField_t& board, Player& p1, Player& p2) //function overload for 2players
{
    bool p1turn{ true };

    while (!fullBoard(board))
    {
        printArray(board);
        if (p1turn)
        {
            p1.setSignature(board);
            if (p1.checkWinner(board))
                break;

            p1turn = false;
        }

        else
        {
            p2.setSignature(board);
            if (p2.checkWinner(board))
                break;

            p1turn = true;
        }
    }
    printArray(board);

    if (p1.hasWon())
        std::cout << "Player 1 has won!\n\a";
    else if (p2.hasWon())
        std::cout << "Player 2 has won!\n\a";
    else if (fullBoard(board) && !p1.hasWon() && !p2.hasWon())
        std::cout << "Tied game!\n";
    return;
}

int getPlayers()
{
    while (true)
    {
        std::cout << "How many players? (1-2): ";
        int c{};
        std::cin >> c;

        if (c == 1 || c == 2)
            return c;

        std::cout << "Invalid number of players!\a\n";
        std::cin.clear();
        std::cin.ignore(32767, '\n');
    }
}
bool getDiff()
{
    std::cout << "Would you like to play against a smarter AI? (y/n): ";
    char c{};
    std::cin >> c;

    if (c == 'Y' || c == 'y')
        return true;

    return false;
}

int main()
{
    std::cout << "Tic Tac Toe v2.8\n\n";

    int nPlayers{ getPlayers() };
    playField_t playField{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    if (nPlayers == 1)
    {
        AI p1(getDiff());
        Player p2(Signature::x, 2);
        std::cout << "Instantiating AI... You are Player 2\n\n";
        playTicTacToe(playField, p1, p2);
    }
    else if (nPlayers == 2)
    {
        Player p1(Signature::o, 1);
        Player p2(Signature::x, 2);
        std::cout << "Loading board...\n\n";
        playTicTacToe(playField, p1, p2);
    }
    return 0;
}

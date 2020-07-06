#ifndef PLAYER_H
#define PLAYER_H
#include <array>

using playField_t = std::array<char, 10>;
namespace Signature
{
    extern char x;
    extern char o;
    extern char h;
    extern char clear;
    extern int W;
    extern int L;
    extern int T;
};

class Player
{
protected:
    char m_signature{ Signature::x };
    bool m_win{ false };
    int m_id{ 1 };

public:
    Player(char signature, int id) : m_signature{ signature }, m_id{ id }
    {
    }

    //core mechanic functions
    virtual void setSignature(playField_t& board);
    bool checkWinner(playField_t& board);

    //access functions
    const bool hasWon() const { return m_win; }
    const bool getId() const { return m_id; }
};

bool isMovesLeft(playField_t& grid);

#endif // !PLAYER_H

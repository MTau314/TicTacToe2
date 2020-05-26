/* Matthew Louigi Cabie Ong 2020 */
#ifndef AI_H
#define AI_H

#include "player.h"

class AI : public Player
{
private:
    bool bHard{ false };

public:
    AI(bool difficulty) : Player(Signature::o, 1), bHard{ difficulty }
    {
    }

    //core mechanic function
    void setSignature(playField_t& board) override;

    //minimax check functions
    int checkGlobalWinner(playField_t& board);
    bool isMovesLeft(playField_t& grid);

private:
    int minimax(playField_t& state, bool isMax, int depth);
};

#endif // !AI_H

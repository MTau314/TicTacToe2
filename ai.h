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

    //function
    void setSignature(playField_t& board) override;

    //minimax check functions
    int checkGlobalWinner(playField_t& board);
    
private:
    int minimax(playField_t& state, bool isMax);
};

#endif // !AI_H

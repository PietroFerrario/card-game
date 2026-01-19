#ifndef GAINBLOCKEFFECT_H
#define GAINBLOCKEFFECT_H

#include "effect.h"

class GainBlockEffect : public Effect
{
public:
    void apply(CardMatch &card_match, Card &card) override;

private:
};

#endif // GAINBLOCKEFFECT_H
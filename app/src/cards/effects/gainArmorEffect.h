#ifndef GAINBLOCKEFFECT_H
#define GAINBLOCKEFFECT_H

#include "cards/effect.h"

class GainArmorEffect : public Effect
{
public:
    void apply(CardMatch &card_match, CardInstance &card) override;

private:
};

#endif // GAINBLOCKEFFECT_H
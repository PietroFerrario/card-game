#ifndef EFFECT_H
#define EFFECT_H

class CardMatch;
class Card;

class Effect
{
public:
    virtual void apply(CardMatch &card_match, Card &card) = 0;

    virtual ~Effect() = default;

private:
};

#endif // EFFECT_H
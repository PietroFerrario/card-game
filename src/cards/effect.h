#ifndef EFFECT_H
#define EFFECT_H

class CardMatch;
class CardInstance;

class Effect
{
public:
    virtual void apply(CardMatch &card_match, CardInstance &card) = 0;

    virtual ~Effect() = default;

private:
};

#endif // EFFECT_H
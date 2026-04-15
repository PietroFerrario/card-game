#ifndef GAMEEVENT_H
#define GAMEEVENT_H

class GameEvent
{
  public:
    virtual ~GameEvent() = default;
    virtual void resolve() = 0;

  private:
};

#endif // GAMEEVENT_H
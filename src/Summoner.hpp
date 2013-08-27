#ifndef SUMMONER_HPP
#define SUMMONER_HPP

#include <Tank/Utility/Timer.hpp>
#include "Field.hpp"
#include "Hand.hpp"

class MainState;
class Deck;

class Summoner
{
public:
    Summoner(Deck const* deck, MainState& game);

    void update(unsigned int turnTime);

    void damage (unsigned int deeps);
    void heal (unsigned int antideeps);

    unsigned int getLife() const { return life_; }
    unsigned int getMana() const { return mana_; }
    unsigned int getTime() const { return time_; }
    unsigned int getManaTicks() const { return manaTimer_.getTicks(); }

    Field& getField() { return field_; }
    Hand& getHand() { return hand_; }

    std::string name;

    void beginTurn();
    void endTurn();
protected:
    virtual void gameLogic(unsigned int turnTime) = 0;
    void play(unsigned int slot);
    void shiftHandLeft();
    void shiftHandRight();
    void toggleAttack(unsigned int slot);

    unsigned int life_;
    unsigned int time_;
    unsigned int mana_;

    Field field_;
    Hand hand_;

    tank::Timer manaTimer_;
    MainState& game_;
};

class AI : public Summoner
{
public:
    AI(Deck const* deck, MainState& game): Summoner(deck,game) {}
private:
    virtual void gameLogic(unsigned int turnTime) override;

    tank::Timer moveTimer_;
};

#endif /* SUMMONER_HPP */

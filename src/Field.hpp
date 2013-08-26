#ifndef FIELD_HPP
#define FIELD_HPP

#include <array>
#include <Tank/Utility/Timer.hpp>
#include "Deck.hpp"

class Field
{
public:
    struct Slot
    {
        Card const* card {nullptr};
        bool attacking {false};
        tank::Timer timer{};
    };

    Field();

    void update();

    void removeCard(unsigned int slot);
    void setCard(Card const*, unsigned int slot);
    Card const* getCard(unsigned int slot) const;

    bool isActive(unsigned int slot) const;
    void toggleAttack(unsigned int slot);
    bool isAttacking(unsigned int slot) const;
private:
    std::array<Slot, 6> slots_;
};

#endif /* FIELD_HPP */

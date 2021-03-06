#include "Hand.hpp"

#include "Resources.hpp"
#include "Settings.hpp"
#include "Summoner.hpp"

Hand::Hand(std::unique_ptr<Deck> const& deck, Field& field)
    : deck_(deck)
    , field_(field)
{
    for (unsigned int i = 0; i < cards_.size(); ++i)
    {
        drawCard(i);
    }
}

Card const* Hand::getCard(unsigned int slot) const
{
    return cards_[slot];
}

void Hand::drawCard(unsigned int slot)
{
    cards_[slot] = deck_->drawCard();
}

bool Hand::play(unsigned int slot)
{
    if (field_.isActive(slot))
    {
        return false;
    }

    field_.setCard(getCard(slot), slot);
    drawCard(slot);

    return true;
}

void Hand::shiftLeft()
{
    std::rotate(cards_.begin(), cards_.begin() + 1, cards_.end());
}

void Hand::shiftRight()
{
    std::rotate(cards_.begin(), cards_.end() - 1, cards_.end());
}

HandGUI::HandGUI(tank::Vectorf pos, std::unique_ptr<Summoner> const& summoner)
    : Entity(pos)
    , overlay_({})
    , summoner_(summoner)
{
    for (unsigned int i = 0; i < 6; ++i)
    {
        cardSlots_[i].setPos({getPos().x + settings::cardSpace * i,
                              getPos().y});
    }
}

void HandGUI::update()
{
    for (unsigned int i = 0; i < 6; ++i)
    {
        if (cardSlots_[i].getCard() != summoner_->getHand().getCard(i))
        {
            cardSlots_[i].setCard(summoner_->getHand().getCard(i));
        }
    }
}

void HandGUI::draw(tank::Camera const& cam)
{
    for (unsigned int i = 0; i < 6; ++i)
    {
        cardSlots_[i].draw(cam);

        if (summoner_->getField().isActive(i))
        {
            tank::Vectorf pos = getPos() + tank::Vectorf{
                        static_cast<float>(settings::cardSpace * i), 0.f};

            overlay_.setPos(pos);
            overlay_.draw(cam);
        }
    }
}

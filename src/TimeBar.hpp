#ifndef TIMEBAR_HPP
#define TIMEBAR_HPP

#include <Tank/System/Entity.hpp>
#include <Tank/Graphics/Image.hpp>
#include "Summoner.hpp"

class TimeBar : public tank::Entity
{
public:
    TimeBar(Summoner const* summoner);

    virtual void update() override;
private:
    Summoner const* summoner_;
    tank::observing_ptr<tank::Image> bar_;

    void setRatio(float ratio);
    static const unsigned int maxWidth;
};

#endif /* TIMEBAR_HPP */

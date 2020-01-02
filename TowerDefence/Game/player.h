#ifndef PLAYER_H
#define PLAYER_H
#include "../Course/CourseLib/core/playerbase.h"

class Player: public Course::PlayerBase
{
public:
    Player(const std::string& name,
           const std::vector
           <std::shared_ptr<Course::GameObject>> objects);
private:
    int op_;
    int concrete_;
    int mead_;
};

#endif // PLAYER_H

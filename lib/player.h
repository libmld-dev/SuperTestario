#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body2d.hpp>

namespace godot {

class Player : public CharacterBody2D {
    GDCLASS(Player, CharacterBody2D)

private:
    const float SPEED = 300.0f;
    const float DAMPING = 30.0f;
    const float JUMP_VELOCITY = -400.0f;

    float gravity;
    bool lookLeft;

protected:
    static void _bind_methods();

public:
    Player();
    virtual ~Player();

    void _process(double delta);
    void _physics_process(double delta);
};

}

#endif // PLAYER_H

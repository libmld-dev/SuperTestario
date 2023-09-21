#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Player::_bind_methods()
{
}

Player::Player() : lookLeft(true)
{
    if(Engine::get_singleton()->is_editor_hint())
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);

    gravity = ProjectSettings::get_singleton()->get_setting("physics/2d/default_gravity");
}

Player::~Player()
{
}

void Player::_process(double delta)
{
    const Input *input = Input::get_singleton();
    AnimatedSprite2D *animBody = get_node<AnimatedSprite2D>(NodePath("CollisionShape2D/MainBody"));
    AnimatedSprite2D *animHead = get_node<AnimatedSprite2D>(NodePath("CollisionShape2D/Head"));

    if(input->is_action_pressed("ui_left"))
    {
        lookLeft = true;
        animBody->play("walk_left");
        animHead->play("left");
    }
    else if(input->is_action_pressed("ui_right"))
    {
        lookLeft = false;
        animBody->play("walk_right");
        animHead->play("right");
    }
    else
    {
        animBody->play(lookLeft ? "idle_left" : "idle_right");
        animHead->play(lookLeft ? "left" : "right");
    }

    // sync
    const int32_t frame = animBody->get_frame();
    const double progress = animBody->get_frame_progress();
    animHead->set_frame_and_progress(frame, progress);
}

void Player::_physics_process(double delta)
{

	Vector2& velo = get_velocity();
    const Input *input = Input::get_singleton();

    if(!is_on_floor())
        velo.y += gravity * delta;

    if(input->is_action_pressed("ui_accept") && is_on_floor())
        velo.y = JUMP_VELOCITY;

    const double dir = input->get_axis("ui_left", "ui_right");
    if(dir != 0)
        velo.x = UtilityFunctions::move_toward(velo.x, dir * SPEED, DAMPING);
    else
		velo.x = UtilityFunctions::move_toward(velo.x, 0, DAMPING);

    set_velocity(velo);
    move_and_slide();
}

#pragma once

#include <tyga/ActorDelegate.hpp>
#include <tyga/ActorWorld.hpp>

#include <vector>

class Bloke;

class Badger : public tyga::ActorDelegate
{
public:

    Badger();

    static std::shared_ptr<Badger>
    makeBadgerWithBloke(std::shared_ptr<tyga::ActorWorld>);

    void
    setSpeed(float speed);

    void
    setTurnAngle(float norm_angle);

    std::shared_ptr<tyga::Actor>
    boundsActor();

private:

    virtual void
    actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorClockTick(std::shared_ptr<tyga::Actor> actor) override;

    void
    setBloke(std::shared_ptr<Bloke> bloke);

    float speed_;
    float turn_angle_;
    float wheel_angle_;

    std::shared_ptr<tyga::Actor> chassis_actor_;
    std::shared_ptr<tyga::Actor> luggage_actor_;
    std::shared_ptr<tyga::Actor> handlebar_actor_;
    std::shared_ptr<tyga::Actor> front_left_wheel_actor_;
    std::shared_ptr<tyga::Actor> front_right_wheel_actor_;
    std::shared_ptr<tyga::Actor> back_left_wheel_actor_;
    std::shared_ptr<tyga::Actor> back_right_wheel_actor_;
    std::shared_ptr<tyga::Actor> physics_actor_;

    std::shared_ptr<Bloke> bloke_;
};

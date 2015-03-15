#pragma once

#include <tyga/ActorDelegate.hpp>
#include "MyPhysicsCentre.hpp"

class ToyMine : public tyga::ActorDelegate
{
public:

    ToyMine();

    void
    reset(tyga::Vector3 position, float mass);

    void
    applyForce(tyga::Vector3 force);

    void
    trigger();

private:

    virtual void
    actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor) override;

    virtual void
    actorClockTick(std::shared_ptr<tyga::Actor> actor) override;

    std::shared_ptr<PhysicsSphere> physics_model_;

};

#pragma once

#include <tyga/RunloopTaskProtocol.hpp>
#include <tyga/Actor.hpp>
#include <tyga/Math.hpp>
#include <memory>
#include <list>

//namespace your_name_here
//{

struct PhysicsObject : public tyga::ActorComponent
{
    tyga::Vector3 position() const;

    tyga::Vector3 velocity;
    
    float mass;
    
    tyga::Vector3 force;

    PhysicsObject();
};

struct PhysicsPlane : public PhysicsObject
{
    tyga::Vector3 normal() const;

    PhysicsPlane();
};

struct PhysicsSphere : public PhysicsObject
{
    float radius;

    PhysicsSphere();
};

struct PhysicsBox : public PhysicsObject
{
    tyga::Vector3 U() const;

    tyga::Vector3 V() const;

    tyga::Vector3 W() const;

    PhysicsBox();
};

class MyPhysicsCentre : public tyga::RunloopTaskProtocol
{
public:

    static std::shared_ptr<MyPhysicsCentre>
    defaultCentre();

    MyPhysicsCentre();

    ~MyPhysicsCentre();

    std::shared_ptr<PhysicsPlane>
    newPlane();

    std::shared_ptr<PhysicsSphere>
    newSphere();

    std::shared_ptr<PhysicsBox>
    newBox();

private:

    void
    pruneDeadObjects();

    void
    runloopWillBegin() override;

    void
    runloopExecuteTask() override;

    void
    runloopDidEnd() override;

    static std::shared_ptr<MyPhysicsCentre> default_centre_;

    std::list<std::weak_ptr<PhysicsPlane>> planes_;
    std::list<std::weak_ptr<PhysicsSphere>> spheres_;
    std::list<std::weak_ptr<PhysicsBox>> boxes_;

};

//} // end namespace

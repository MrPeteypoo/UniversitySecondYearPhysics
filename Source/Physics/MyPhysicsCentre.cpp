#include "MyPhysicsCentre.hpp"
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Log.hpp>
#include <Maths/RK4Integrator.hpp>
#include <Maths/EulerIntegrator.hpp>
#include <cassert>
#include <Utility/MyUtils.hpp>

//namespace your_name_here
//{

PhysicsObject::PhysicsObject() : mass(0)
{
}

tyga::Vector3 PhysicsObject::
position() const
{
    auto actor = this->Actor();
    if (actor != nullptr) {
        const auto& xform = actor->Transformation();
        return tyga::Vector3(xform._30, xform._31, xform._32);
    }
    return tyga::Vector3();
}

PhysicsPlane::PhysicsPlane()
{
}

tyga::Vector3 PhysicsPlane::
normal() const
{
    auto actor = this->Actor();
    if (actor != nullptr) {
        const auto& xform = actor->Transformation();
        return tyga::Vector3(xform._20, xform._21, xform._22);
    }
    return tyga::Vector3();
}

PhysicsSphere::PhysicsSphere() : radius(1)
{
}

PhysicsBox::PhysicsBox()
{
}

tyga::Vector3 PhysicsBox::
U() const
{
    auto actor = this->Actor();
    if (actor != nullptr) {
        const auto& xform = actor->Transformation();
        return tyga::Vector3(xform._00, xform._01, xform._02);
    }
    return tyga::Vector3();
}

tyga::Vector3 PhysicsBox::
V() const
{
    auto actor = this->Actor();
    if (actor != nullptr) {
        const auto& xform = actor->Transformation();
        return tyga::Vector3(xform._10, xform._11, xform._12);
    }
    return tyga::Vector3();
}

tyga::Vector3 PhysicsBox::
W() const
{
    auto actor = this->Actor();
    if (actor != nullptr) {
        const auto& xform = actor->Transformation();
        return tyga::Vector3(xform._20, xform._21, xform._22);
    }
    return tyga::Vector3();
}

std::shared_ptr<MyPhysicsCentre> MyPhysicsCentre::default_centre_;

std::shared_ptr<MyPhysicsCentre> MyPhysicsCentre::
defaultCentre()
{
    if (default_centre_ == nullptr) {
        default_centre_ = std::make_shared<MyPhysicsCentre>();
    }
    return default_centre_;
}

MyPhysicsCentre::
MyPhysicsCentre()
{
}

MyPhysicsCentre::
~MyPhysicsCentre()
{
}

template<typename T> static void
_prune(std::list<T>& list)
{
    for (auto it = list.begin(); it != list.end(); ) {
        if (it->expired()) {
            it = list.erase(it);
        } else {
            it++;
        }
    }
}

void MyPhysicsCentre::
pruneDeadObjects()
{
    _prune(planes_);
    _prune(spheres_);
    _prune(boxes_);
}

std::shared_ptr<PhysicsPlane> MyPhysicsCentre::
newPlane()
{
    auto new_plane = std::make_shared<PhysicsPlane>();
    planes_.push_back(new_plane);
    return new_plane;
}

std::shared_ptr<PhysicsSphere> MyPhysicsCentre::
newSphere()
{
    auto new_sphere = std::make_shared<PhysicsSphere>();
    spheres_.push_back(new_sphere);
    return new_sphere;
}

std::shared_ptr<PhysicsBox> MyPhysicsCentre::
newBox()
{
    auto new_box = std::make_shared<PhysicsBox>();
    boxes_.push_back(new_box);
    return new_box;
}

void MyPhysicsCentre::
runloopWillBegin()
{
    for (auto s_iter = spheres_.begin(); s_iter != spheres_.end(); s_iter++)
    {
        // only continue if a strong reference is available
        if (s_iter->expired()) continue;
        auto sphere = s_iter->lock();

        // very crude ground plane collision detection and response
        // TODO: this could be improved
        const auto& p = sphere->position();
        if (p.y < sphere->radius) {
            sphere->velocity.y = 0;
            auto actor = sphere->Actor();
            if (actor != nullptr) {
                auto xform = actor->Transformation();
                xform._31 = sphere->radius;
                actor->setTransformation(xform);
            }
        }
    }
}

void MyPhysicsCentre::
runloopExecuteTask()
{
    // Obtain the frames current time values.
    const float time      = tyga::BasicWorldClock::CurrentTime();
    const float deltaTime = tyga::BasicWorldClock::CurrentTickInterval();

    const auto gravity    = tyga::Vector3 (0.f, -9.81f, 0.f);

    for (const auto& ptr : spheres_) 
    {
        // Only process the sphere if the object exists and it has an actor.
        const auto model = ptr.lock();
        const auto actor = model ? model->Actor() : nullptr;
        
        if (actor) 
        { 
            // Cache the physics object.
            auto& object = *model;
            assert (object.mass != 0);

            tyga::Vector3 translation { };

            const auto acceleration = object.force / object.mass + gravity;

            const auto& calcAccel = [&acceleration] (const tyga::Vector3& position, const tyga::Vector3& velocity, const float deltaTime)
            {
                return acceleration;
            };
            
            RK4Integrator<tyga::Vector3, float>::integrate (translation, object.velocity, calcAccel, 0, deltaTime);
            //EulerIntegrator<tyga::Vector3, float>::integrate (translation, object.velocity, acceleration, deltaTime);

            
            // TODO: update the actor's transformation
            actor->setTransformation (actor->Transformation() * util::translate (translation.x, translation.y, translation.z));

            // reset the force
            model->force = tyga::Vector3(0,0,0);
        }
    }
}

void MyPhysicsCentre::
runloopDidEnd()
{
    pruneDeadObjects();
}

//} // end namespace tyga

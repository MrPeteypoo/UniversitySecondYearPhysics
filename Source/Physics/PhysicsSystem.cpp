#include "PhysicsSystem.hpp"


// STL headers.
#include <cassert>


// Engine headers.
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Log.hpp>


// Personal headers.
#include <Maths/RK4Integrator.hpp>
#include <Maths/EulerIntegrator.hpp>
#include <Physics/CollisionDetection.hpp>
#include <Physics/PhysicsObject.hpp>
#include <Physics/PhysicsSphere.hpp>
#include <Utility/Misc.hpp>
#include <Utility/Tyga.hpp>


namespace spc
{
    //////////////////////////
    // Static functionality //
    //////////////////////////

    std::shared_ptr<PhysicsSystem> PhysicsSystem::m_defaultSystem = nullptr;


    std::shared_ptr<PhysicsSystem> PhysicsSystem::defaultSystem()
    {
        if (!m_defaultSystem)
        {
            m_defaultSystem = std::make_shared<PhysicsSystem>();
        }

        return m_defaultSystem;
    }


    //////////////////
    // Constructors //
    //////////////////

    PhysicsSystem::PhysicsSystem (const unsigned int reserve)
    {
        // Allocate some memory.
        m_objects.reserve (reserve);

        // Set gravity to earths standard gravity.
        m_gravity = { 0.f, -9.81f, 0.f };
    }


    //////////////////////////////
    // Delegate implementations //
    //////////////////////////////

    void PhysicsSystem::
    runloopWillBegin()
    {
        // Perform collision detection.
        for (const auto& element : m_objects)
        {
            const auto lock = element.lock();

            if (lock && lock->getType() == PhysicsObject::Type::Sphere)
            {
                // We can safely downcast because of the implementation of the getType function.
                auto& object = *std::static_pointer_cast<PhysicsSphere> (lock);

                // Ensure the actor is valid.
                const auto actor = object.Actor();
                if (actor)
                {
                    // Obtain the transform and position of the sphere.
                    auto transform      = actor->Transformation();
                    const auto position = util::position (transform);

                    if (position.y < object.radius)
                    {
                        object.velocity.y = 0.f;
                        transform._31 = object.radius;
                        actor->setTransformation (transform);
                    }
                }
            }
        }
        
        // Test every object against every other object.
        for (auto i = 0U; i < m_objects.size(); ++i)
        {
            // Don't bother checking anything if the object has expired.
            const auto lockI = m_objects[i].lock();

            if (lockI)
            {
                for (auto j = i + 1; j < m_objects.size(); ++j)
                {
                    // Again, don't bother checking for collision if the object has expired.
                    const auto lockJ = m_objects[j].lock();

                    if (lockJ)
                    {
                        CollisionDetection::detectCollision (*lockI, *lockJ);
                    }
                }
            }
        }
    }

    void PhysicsSystem::
    runloopExecuteTask()
    {
        // Obtain the frames current time values.
        const float time      = tyga::BasicWorldClock::CurrentTime();
        const float deltaTime = tyga::BasicWorldClock::CurrentTickInterval();

        for (const auto& element : m_objects) 
        {
            // Only process the sphere if the object exists and it has an actor.
            const auto lock  = element.lock();
            const auto actor = lock ? lock->Actor() : nullptr;
        
            if (actor) 
            { 
                // Cache the physics object.
                auto& object = *lock;

                // Create a function to calculate the acceleration of the object.
                const auto calcAccel = [&] (const tyga::Vector3& position, const tyga::Vector3& velocity, const float deltaTime)
                {
                    const float k = 1.0f;
                    const float b = 0.3f;
                    return (-k * position - b * velocity + object.force) / object.getMass() + m_gravity;
                };
            
                // Use the Runge-Kutta order of 4 method to integrate an accurate solution.
                tyga::Vector3 translation { };
                RK4Integrator<tyga::Vector3, float>::integrate (translation, object.velocity, calcAccel, time, deltaTime);

                // Update the transformation.
                actor->setTransformation (actor->Transformation() * util::translate (translation.x, translation.y, translation.z));

                // Reset the applied force.
                object.force = tyga::Vector3(0,0,0);
            }
        }
    }

    void PhysicsSystem::
    runloopDidEnd()
    {
        // Remove any dead objects.
        const auto removeCondition = [] (const std::weak_ptr<PhysicsObject>& object) 
        { 
            return object.expired(); 
        };

        util::unorderedRemove<std::weak_ptr<PhysicsObject>> (m_objects, removeCondition);
    }
} 

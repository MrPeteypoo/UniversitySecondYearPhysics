#include "PhysicsSystem.hpp"
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Log.hpp>
#include <Maths/RK4Integrator.hpp>
#include <Maths/EulerIntegrator.hpp>
#include <Physics/PhysicsObject.hpp>
#include <cassert>
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
        for (const auto& object : m_objects)
        {
            
        }
        
        /*for (auto s_iter = spheres_.begin(); s_iter != spheres_.end(); s_iter++)
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
        }*/
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
            const auto model = element.lock();
            const auto actor = model ? model->Actor() : nullptr;
        
            if (actor) 
            { 
                // Cache the physics object.
                auto& object = *model;

                tyga::Vector3 translation { };

                const auto acceleration = object.force / object.getMass() + m_gravity;

                const auto& calcAccel = [&] (const tyga::Vector3& position, const tyga::Vector3& velocity, const float deltaTime)
                {
                    //return acceleration;
                    const float k = 1.0f;
                    const float b = 0.3f;
                    return (-k * position - b * velocity + object.force) / object.getMass() + m_gravity;
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

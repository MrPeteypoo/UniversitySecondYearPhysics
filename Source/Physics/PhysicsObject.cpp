#include "PhysicsObject.hpp"


// STL headers.
#include <utility>


// Engine headers.
#include <Utility/Tyga.hpp>


namespace spc
{
    //////////////////
    // Constructors //
    //////////////////

    PhysicsObject::PhysicsObject (PhysicsObject&& move)
    {
        *this = std::move (move);
    }


    PhysicsObject& PhysicsObject::operator= (PhysicsObject&& move)
    {
        if (this != &move)
        {
            // Move thy data.
            velocity    = std::move (velocity);
            force       = std::move (force);
            drag        = move.drag;
            restitution = move.restitution;
            isStatic    = move.isStatic;

            m_mass      = move.m_mass;

            // Reset primitives.
            move.drag        = 0.f;
            move.restitution = 0.f;
            move.isStatic    = false;
            move.m_mass      = 0.f;
        }

        return *this;
    }


    ///////////////////////
    // Object properties //
    ///////////////////////

    tyga::Vector3 PhysicsObject::position() const
    {
        // Obtain the transform.
        const auto transform = util::transformation (*this);

        // Return the position vector.
        return util::position (transform);
    }


    void PhysicsObject::setMass (const float mass)
    {
        if (mass != 0.f)
        {
            m_mass = mass;
        }
    }
}
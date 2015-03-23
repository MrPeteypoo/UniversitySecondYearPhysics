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
            velocity = std::move (velocity);
            force    = std::move (force);
            m_mass   = move.m_mass;

            // Reset primitives.
            move.m_mass = 0.f;
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
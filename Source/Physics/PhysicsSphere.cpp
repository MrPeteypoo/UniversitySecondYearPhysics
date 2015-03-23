#include "PhysicsSphere.hpp"


// STL headers.
#include <utility>


namespace spc
{
    //////////////////
    // Constructors //
    //////////////////

    PhysicsSphere::PhysicsSphere (PhysicsSphere&& move)
    {
        *this = std::move (move);
    }


    PhysicsSphere& PhysicsSphere::operator= (PhysicsSphere&& move)
    {
        if (this != &move)
        {
            // Ensure parent data is moved.
            PhysicsObject::operator= (std::move (move));

            // Move our data.
            radius = move.radius;

            // Reset primitives.
            move.radius = 0.f;
        }

        return *this;
    }
}
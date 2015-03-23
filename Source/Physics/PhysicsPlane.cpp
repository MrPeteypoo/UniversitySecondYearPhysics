#include "PhysicsPlane.hpp"


// STL headers.
#include <utility>


// Engine headers.
#include <Utility/Tyga.hpp>


namespace spc
{
    //////////////////
    // Constructors //
    //////////////////

    PhysicsPlane::PhysicsPlane (PhysicsPlane&& move)
    {
        *this = std::move (move);
    }


    PhysicsPlane& PhysicsPlane::operator= (PhysicsPlane&& move)
    {
        if (this != &move)
        {
            // Ensure parent data is moved.
            PhysicsObject::operator= (std::move (move));
        }

        return *this;
    }

    
    ///////////////////////
    // Object properties //
    ///////////////////////

    tyga::Vector3 PhysicsPlane::normal() const
    {
        // The normal is stored the same way the Z rotation is for box colliders so we can take advantage of that.
        const auto transform = util::transformation (*this);

        // Return the position vector.
        return util::zRotation (transform);
    }
}
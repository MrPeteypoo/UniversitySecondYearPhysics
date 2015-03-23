#include "PhysicsBox.hpp"


// STL headers.
#include <utility>


// Engine headers.
#include <Utility/Tyga.hpp>


namespace spc
{
    //////////////////
    // Constructors //
    //////////////////

    PhysicsBox::PhysicsBox (PhysicsBox&& move)
    {
        *this = std::move (move);
    }


    PhysicsBox& PhysicsBox::operator= (PhysicsBox&& move)
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

    tyga::Vector3 PhysicsBox::U() const
    {
        // Obtain the transform.
        const auto transform = util::transformation (*this);

        // Return the rotational vector for the X axis.
        return util::xRotation (transform);
    }


    tyga::Vector3 PhysicsBox::V() const
    {
        // Obtain the transform.
        const auto transform = util::transformation (*this);

        // Return the rotational vector for the Y axis.
        return util::yRotation (transform);
    }

    tyga::Vector3 PhysicsBox::W() const
    {
        // Obtain the transform.
        const auto transform = util::transformation (*this);

        // Return the rotational vector for the Z axis.
        return util::zRotation (transform);
    }
}
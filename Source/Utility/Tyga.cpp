#include "Tyga.hpp"


// Engine headers.
#include <tyga/Actor.hpp>
#include <tyga/Math.hpp>


namespace util
{
    tyga::Matrix4x4 transformation (const tyga::ActorComponent& component)
    {
        // Obtain the pointer to the actor.
        const auto& actor = component.Actor();

        // Ensure it exists to avoid access violation errors.
        return actor ? actor->Transformation() : tyga::Matrix4x4();    
    }
}

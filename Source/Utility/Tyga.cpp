#include "Tyga.hpp"


// Engine headers.
#include <tyga/Actor.hpp>
#include <tyga/Math.hpp>


namespace util
{
    tyga::Vector3 position (const tyga::Matrix4x4& transform)
    {
        // The final row of the transform contains the translation of an object.
        return { transform._30, transform._31, transform._32 };
    }


    tyga::Vector3 xRotation (const tyga::Matrix4x4& transform)
    {
        // The first row of the transform contains rotation on the X axis.
        return { transform._00, transform._01, transform._02 };
    }


    tyga::Vector3 yRotation (const tyga::Matrix4x4& transform)
    {
        // The second row of the transform contains rotation on the Y axis.
        return { transform._10, transform._11, transform._12 };
    }


    tyga::Vector3 zRotation (const tyga::Matrix4x4& transform)
    {
        // The third row of the transform contains rotation on the Z axis.
        return { transform._20, transform._21, transform._22 };
    }


    tyga::Matrix4x4 transformation (const tyga::ActorComponent& component)
    {
        // Obtain the pointer to the actor.
        const auto& actor = component.Actor();

        // Ensure it exists to avoid access violation errors.
        return actor ? actor->Transformation() : tyga::Matrix4x4();    
    }


    tyga::Matrix4x4 translate (const tyga::Vector3& translation)
    {
        // Split the vector up.
        const auto x = translation.x,
                   y = translation.y,
                   z = translation.z;

        // Slot the values into the correct part of the matrix!
        return { 1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 x, y, z, 1 };
    }


    tyga::Matrix4x4 translate (float x, float y, float z)
    {
        // Slot the values into the correct part of the matrix!
        return { 1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 x, y, z, 1 };
    }

}

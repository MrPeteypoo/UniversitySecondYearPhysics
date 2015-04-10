#ifndef UTILITY_TYGA_ASP_HPP
#define UTILITY_TYGA_ASP_HPP


// Engine headers.
#include <tyga/Matrix.hpp>
#include <tyga/Vector.hpp>


// Forward declarations.
namespace tyga { class ActorComponent; }


namespace util
{
    /// <summary> Calculates the squared length of a vector. This is a relatively operation. </summary>
    /// <param name="vector"> The vector to calculate the length for. </param>
    /// <returns> The squared length. </returns>
    inline float sqrLength (const tyga::Vector3& vector);

    /// <summary> Obtains the position of an object from a given transformation matrix. </summary>
    /// <param name="transform"> The matrix to obtain the position vector from. </param>
    /// <returns> The position vector. </returns>
    inline tyga::Vector3 position (const tyga::Matrix4x4& transform);

    /// <summary> Calculate the rotation of an object on the X axis from a transformation matrix. </summary>
    /// <param name="transform"> The matrix containing rotation information. </param>
    /// <returns> The calculate rotation. </returns>
    inline tyga::Vector3 xRotation (const tyga::Matrix4x4& transform);

    /// <summary> Calculate the rotation of an object on the Y axis from a transformation matrix. </summary>
    /// <param name="transform"> The matrix containing rotation information. </param>
    /// <returns> The calculate rotation. </returns>
    inline tyga::Vector3 yRotation (const tyga::Matrix4x4& transform);

    /// <summary> Calculate the rotation of an object on the Z axis from a transformation matrix. </summary>
    /// <param name="transform"> The matrix containing rotation information. </param>
    /// <returns> The calculate rotation. </returns>
    inline tyga::Vector3 zRotation (const tyga::Matrix4x4& transform);
        
    /// <summary> Creates a translation matrix from the given vector. </summary>
    /// <returns> The calculated matrix. </returns>
    inline tyga::Matrix4x4 translate (const tyga::Vector3& translation);

    /// <summary> Creates a translation matrix from X, Y and Z translation values. </summary>
    /// <param name="x"> Desired translation on the X axis. </param>
    /// <param name="y"> Desired translation on the Y axis. </param>
    /// <param name="z"> Desired translation on the Z axis. </param>
    /// <returns> The calculated matrix. </returns>
    inline tyga::Matrix4x4 translate (const float x, const float y, const float z);
    
    /// <summary> Obtains the transformation matrix of an Actor from any given ActorComponent </summary>
    /// <param name="component"> The component connected to an actor. </param>
    /// <returns> The Actor transformation, if the component isn't attached then an identity matrix will be returned.
    tyga::Matrix4x4 transformation (const tyga::ActorComponent& component);
}


float util::sqrLength (const tyga::Vector3& vector)
{
    return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
}


tyga::Vector3 util::position (const tyga::Matrix4x4& transform)
{
    // The final row of the transform contains the translation of an object.
    return { transform._30, transform._31, transform._32 };
}


tyga::Vector3 util::xRotation (const tyga::Matrix4x4& transform)
{
    // The first row of the transform contains rotation on the X axis.
    return { transform._00, transform._01, transform._02 };
}


tyga::Vector3 util::yRotation (const tyga::Matrix4x4& transform)
{
    // The second row of the transform contains rotation on the Y axis.
    return { transform._10, transform._11, transform._12 };
}


tyga::Vector3 util::zRotation (const tyga::Matrix4x4& transform)
{
    // The third row of the transform contains rotation on the Z axis.
    return { transform._20, transform._21, transform._22 };
}


tyga::Matrix4x4 util::translate (const tyga::Vector3& translation)
{
    // Split the vector up.
    return translate (translation.x, translation.y, translation.z);
}


tyga::Matrix4x4 util::translate (const float x, const float y, const float z)
{
    // Slot the values into the correct part of the matrix!
    return { 1, 0, 0, 0,
             0, 1, 0, 0,
             0, 0, 1, 0,
             x, y, z, 1 };
}

#endif
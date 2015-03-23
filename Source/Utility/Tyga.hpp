#ifndef UTILITY_TYGA_ASP_HPP
#define UTILITY_TYGA_ASP_HPP


namespace tyga
{
    // Forward declarations.
    class ActorComponent;
    class Matrix4x4;
    class Vector3;
}


namespace util
{
    /// <summary> Obtains the position of an object from a given transformation matrix. </summary>
    /// <param name="transform"> The matrix to obtain the position vector from. </param>
    /// <returns> The position vector. </returns>
    tyga::Vector3 position (const tyga::Matrix4x4& transform);

    /// <summary> Calculate the rotation of an object on the X axis from a transformation matrix. </summary>
    /// <param name="transform"> The matrix containing rotation information. </param>
    /// <returns> The calculate rotation. </returns>
    tyga::Vector3 xRotation (const tyga::Matrix4x4& transform);

    /// <summary> Calculate the rotation of an object on the Y axis from a transformation matrix. </summary>
    /// <param name="transform"> The matrix containing rotation information. </param>
    /// <returns> The calculate rotation. </returns>
    tyga::Vector3 yRotation (const tyga::Matrix4x4& transform);

    /// <summary> Calculate the rotation of an object on the Z axis from a transformation matrix. </summary>
    /// <param name="transform"> The matrix containing rotation information. </param>
    /// <returns> The calculate rotation. </returns>
    tyga::Vector3 zRotation (const tyga::Matrix4x4& transform);
    
    /// <summary> Obtains the transformation matrix of an Actor from any given ActorComponent </summary>
    /// <param name="component"> The component connected to an actor. </param>
    /// <returns> The Actor transformation, if the component isn't attached then an identity matrix will be returned.
    tyga::Matrix4x4 transformation (const tyga::ActorComponent& component);
        
    /// <summary> Creates a translation matrix from the given vector. </summary>
    /// <returns> The calculated matrix. </returns>
    tyga::Matrix4x4 translate (const tyga::Vector3& translation);

    /// <summary> Creates a translation matrix from X, Y and Z translation values. </summary>
    /// <param name="x"> Desired translation on the X axis. </param>
    /// <param name="y"> Desired translation on the Y axis. </param>
    /// <param name="z"> Desired translation on the Z axis. </param>
    /// <returns> The calculated matrix. </returns>
    tyga::Matrix4x4 translate (const float x, const float y, const float z);
}

#endif
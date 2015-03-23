#ifndef SPC_COLLISION_DETECTION_ASP_HPP
#define SPC_COLLISION_DETECTION_ASP_HPP


namespace spc
{
    // Forward declarations.
    class PhysicsObject;
    class PhysicsBox;
    class PhysicsPlane;
    class PhysicsSphere;


    /// <summary>
    /// A static class which handles the collision detection of various different PhysicsObject types.
    /// </summary>
    class CollisionDetection final
    {
        public:

            //////////////////////
            // Public interface //
            //////////////////////

            /// <summary> Detects if any collision has happened between two PhysicsObject types. </summary>
            static void detectCollision (const PhysicsObject& lhs, const PhysicsObject& rhs);
    };
}

#endif
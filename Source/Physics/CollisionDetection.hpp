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

        private:
            
            /// <summary> Handles sphere on sphere collision. </summary>
            static void sphereSphereCollison (const PhysicsSphere& lhs, const PhysicsSphere& rhs);

            /// <summary> Handles sphere on box collision. </summary>
            static void sphereBoxCollision (const PhysicsSphere& sphere, const PhysicsBox& box);

            /// <summary> Handles sphere on plane collision. </summary>
            static void spherePlaneCollision (const PhysicsSphere& sphere, const PhysicsPlane& plane);

            /// <summary> Handles box on box collision. </summary>
            static void boxBoxCollision (const PhysicsBox& lhs, const PhysicsBox& rhs);

            /// <summary> Handles box on plane collision. </summary>
            static void boxPlaneCollision (const PhysicsBox& box, const PhysicsPlane& plane);

            /// <summary> Handles plane on plane collision. </summary>
            static void planePlaneCollision (const PhysicsPlane& lhs, const PhysicsPlane& rhs);
    };
}

#endif
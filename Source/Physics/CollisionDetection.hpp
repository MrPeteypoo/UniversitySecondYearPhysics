#ifndef SPC_COLLISION_DETECTION_ASP_HPP
#define SPC_COLLISION_DETECTION_ASP_HPP


// Forward declarations.
namespace tyga { class Actor; class Vector3; }


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
            static void detectCollision (PhysicsObject& lhs, PhysicsObject& rhs);

        private:

            /// <summary> Cast two objects to the specified types and pass them to the desired function. </summary>
            /// <param name="lhs"> The object to be cast to T. </param>
            /// <param name="rhs"> The object to be cast to U. </param>
            /// <param name="function"> The function to pass the objects to. </param>
            template <typename T, typename U, typename V> 
            static void passToFunction (PhysicsObject& lhs, PhysicsObject& rhs, const V& function);
            
            /// <summary> Handles sphere on sphere collision. </summary>
            static void sphereSphereCollision (PhysicsSphere& lhs, PhysicsSphere& rhs);

            /// <summary> Handles sphere on box collision. </summary>
            static void sphereBoxCollision (PhysicsSphere& sphere, PhysicsBox& box);

            /// <summary> Handles sphere on plane collision. </summary>
            static void spherePlaneCollision (PhysicsSphere& sphere, PhysicsPlane& plane);

            /// <summary> Handles box on box collision. </summary>
            static void boxBoxCollision (PhysicsBox& lhs, PhysicsBox& rhs);

            /// <summary> Handles box on plane collision. </summary>
            static void boxPlaneCollision (PhysicsBox& box, PhysicsPlane& plane);

            /// <summary> Handles plane on plane collision. </summary>
            static void planePlaneCollision (PhysicsPlane& lhs, PhysicsPlane& rhs);

            /// <summary> Performs collision response on the two given objects. </summary>
            /// <param name="lhs"> The first object. </param>
            /// <param name="rhs"> The second second. </param>
            /// <param name="normal"> The normal vector of the collision. </param>
            /// <param name="intersection"> How much the objects are colliding by. </param>
            static void collisionResponse (PhysicsObject& lhs, PhysicsObject& rhs, const tyga::Vector3& normal, const float intersection);
    };
}

#endif
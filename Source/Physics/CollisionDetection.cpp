#include "CollisionDetection.hpp"


// Personal headers.
#include <Physics/PhysicsBox.hpp>
#include <Physics/PhysicsPlane.hpp>
#include <Physics/PhysicsSphere.hpp>


namespace spc
{
    void CollisionDetection::detectCollision (const PhysicsObject& lhs, const PhysicsObject& rhs)
    {
        
    }


    void CollisionDetection::sphereSphereCollison (const PhysicsSphere& lhs, const PhysicsSphere& rhs)
    {
    
    }


    void CollisionDetection::sphereBoxCollision (const PhysicsSphere& sphere, const PhysicsBox& box)
    {
    
    }


    void CollisionDetection::spherePlaneCollision (const PhysicsSphere& sphere, const PhysicsPlane& plane)
    {
    
    }


    void CollisionDetection::boxBoxCollision (const PhysicsBox& lhs, const PhysicsBox& rhs)
    {
    
    }


    void CollisionDetection::boxPlaneCollision (const PhysicsBox& box, const PhysicsPlane& plane)
    {
    
    }


    void CollisionDetection::planePlaneCollision (const PhysicsPlane& lhs, const PhysicsPlane& rhs)
    {
    
    }
}
#include "CollisionDetection.hpp"


// STL headers.
#include <cassert>


// Personal headers.
#include <Physics/PhysicsBox.hpp>
#include <Physics/PhysicsPlane.hpp>
#include <Physics/PhysicsSphere.hpp>


namespace spc
{
    template <typename T, typename U, typename V>
    void CollisionDetection::passToFunction (const PhysicsObject& lhs, const PhysicsObject& rhs, const V& function)
    {
        function (static_cast<const T&> (lhs), static_cast<const U&> (rhs));
    }


    void CollisionDetection::detectCollision (const PhysicsObject& lhs, const PhysicsObject& rhs)
    {
        // We need to check which type each object is castable to.
        const auto lhsType = lhs.getType();
        const auto rhsType = rhs.getType();

        switch (lhsType)
        {
            case PhysicsObject::Type::Sphere:
                switch (rhsType)
                {
                    case PhysicsObject::Type::Sphere:
                        passToFunction<PhysicsSphere, PhysicsSphere> (lhs, rhs, &sphereSphereCollision);
                        break;

                    case PhysicsObject::Type::Box:
                        passToFunction<PhysicsSphere, PhysicsBox> (lhs, rhs, &sphereBoxCollision);
                        break;
                    
                    case PhysicsObject::Type::Plane:
                        passToFunction<PhysicsSphere, PhysicsPlane> (lhs, rhs, &spherePlaneCollision);
                        break;
                }
                break;

            case PhysicsObject::Type::Box:
                switch (rhsType)
                {
                    case PhysicsObject::Type::Box:
                        passToFunction<PhysicsBox, PhysicsBox> (lhs, rhs, &boxBoxCollision);
                        break;

                    case PhysicsObject::Type::Plane:
                        passToFunction<PhysicsBox, PhysicsPlane> (lhs, rhs, &boxPlaneCollision);
                        break;
                    
                    case PhysicsObject::Type::Sphere: // We've done this so swap the parameters.
                        passToFunction<PhysicsSphere, PhysicsBox> (rhs, lhs, &sphereBoxCollision);
                        break;
                }
                break;

            case PhysicsObject::Type::Plane:
                switch (rhsType)
                {
                    case PhysicsObject::Type::Plane:
                        passToFunction<PhysicsPlane, PhysicsPlane> (lhs, rhs, &planePlaneCollision);
                        break;

                    case PhysicsObject::Type::Sphere: // We've done this so swap the parameters.
                        passToFunction<PhysicsSphere, PhysicsPlane> (rhs, lhs, &spherePlaneCollision);
                        break;
                    
                    case PhysicsObject::Type::Box: // We've done this so swap the parameters.
                        passToFunction<PhysicsBox, PhysicsPlane> (rhs, lhs, &boxPlaneCollision);
                        break;
                }
                break;

            default:
                assert (false);
                break;

        }
    }


    void CollisionDetection::sphereSphereCollision (const PhysicsSphere& lhs, const PhysicsSphere& rhs)
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
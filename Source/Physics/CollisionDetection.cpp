#include "CollisionDetection.hpp"


// STL headers.
#include <cassert>


// Personal headers.
#include <Physics/PhysicsBox.hpp>
#include <Physics/PhysicsPlane.hpp>
#include <Physics/PhysicsSphere.hpp>
#include <Utility/Misc.hpp>
#include <Utility/Tyga.hpp>


namespace spc
{
    template <typename T, typename U, typename V>
    void CollisionDetection::passToFunction (PhysicsObject& lhs, PhysicsObject& rhs, const V& function)
    {
        function (static_cast<T&> (lhs), static_cast<U&> (rhs));
    }


    void CollisionDetection::detectCollision (PhysicsObject& lhs, PhysicsObject& rhs)
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


    void CollisionDetection::sphereSphereCollision (PhysicsSphere& lhs, PhysicsSphere& rhs)
    {
        // We need the position of each object.
        const auto lhsPos = lhs.position(),
                   rhsPos = rhs.position();

        // The square length will be lower than the sum of the squared radius of each sphere if there is a collision.
        const auto distanceSqr = util::sqrLength (lhsPos - rhsPos);

        if (distanceSqr < util::squared (lhs.radius) + util::squared (rhs.radius))
        {
            // We've collided!
            lhs.radius;
        }
    }


    void CollisionDetection::sphereBoxCollision (PhysicsSphere& sphere, PhysicsBox& box)
    {
    
    }


    void CollisionDetection::spherePlaneCollision (PhysicsSphere& sphere, PhysicsPlane& plane)
    {
    
    }


    void CollisionDetection::boxBoxCollision (PhysicsBox& lhs, PhysicsBox& rhs)
    {
    
    }


    void CollisionDetection::boxPlaneCollision (PhysicsBox& box, PhysicsPlane& plane)
    {
    
    }


    void CollisionDetection::planePlaneCollision (PhysicsPlane& lhs, PhysicsPlane& rhs)
    {
    
    }
}
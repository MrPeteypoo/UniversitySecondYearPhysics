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
        // Pre-condition: The actor is valid.
        if (lhs.Actor() && rhs.Actor())
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
    }


    void CollisionDetection::sphereSphereCollision (PhysicsSphere& lhs, PhysicsSphere& rhs)
    {
        // Obtain a reference to the actors.
        auto& lhsActor = *lhs.Actor();
        auto& rhsActor = *rhs.Actor();

        // We need the position of each object.
        const auto lhsPos = util::position (lhsActor.Transformation()),
                   rhsPos = util::position (rhsActor.Transformation());

        // The square length will be lower than the sum of the squared radius of each sphere if there is a collision.
        const auto distance  = lhsPos - rhsPos;
        const auto lengthSqr = util::sqrLength (lhsPos - rhsPos),
                   radiusSum = lhs.radius + rhs.radius;

        if (lengthSqr <= util::squared (radiusSum))
        {
            // We've collided! Move the objects out of collision with each other.
            const auto length       = std::sqrt (lengthSqr);
            const auto normal       = distance / length;
            const auto intersection = length - radiusSum;

            collisionResponse (lhs, rhs, normal, intersection);
        }
    }


    void CollisionDetection::sphereBoxCollision (PhysicsSphere& sphere, PhysicsBox& box)
    {
    
    }


    void CollisionDetection::spherePlaneCollision (PhysicsSphere& sphere, PhysicsPlane& plane)
    {
        // Obtain a reference to the actors.
        auto& sphereActor = *sphere.Actor();
        auto& planeActor  = *plane.Actor();

        // We need the position of each object.
        const auto spherePos = util::position (sphereActor.Transformation()),
                   planePos  = util::position (planeActor.Transformation()),
                   normal    = tyga::unit (plane.normal());

        // The formula for collision is c.n - q.n < radius.
        const auto sphereDot = tyga::dot (spherePos, normal),
                   planeDot  = tyga::dot (planePos, normal),
                   distance  = sphereDot - planeDot;

        if (distance < sphere.radius)
        {
            collisionResponse (plane, sphere, normal, sphere.radius - distance);
        }
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


    void CollisionDetection::collisionResponse (PhysicsObject& lhs, PhysicsObject& rhs, const tyga::Vector3& normal, const float intersection)
    {    
        // Obtain references to the actual actors.
        auto& lhsActor = *lhs.Actor();
        auto& rhsActor = *rhs.Actor();

        // We need to determine how much to reflect objects by.
        const auto lhsReflect = (lhs.velocity - 2 * -normal * (tyga::dot (lhs.velocity, -normal))) * lhs.restitution,
                   rhsReflect = (rhs.velocity - 2 * normal * (tyga::dot (rhs.velocity, normal))) * rhs.restitution;
        
        // Determine how much to correct each object by.
        const auto correction = normal * (intersection * 0.5001f);
        
        // Move the actors out of each others path.
        if (rhs.isStatic)
        {
            lhsActor.setTransformation (rhsActor.Transformation() * util::translate (correction * -2.f));
            lhs.velocity = lhsReflect;
        }

        else if (lhs.isStatic)
        {
            rhsActor.setTransformation (rhsActor.Transformation() * util::translate (correction * 2.f));
            rhs.velocity = rhsReflect;
        }

        else
        {
            lhsActor.setTransformation (lhsActor.Transformation() * util::translate (-correction));
            rhsActor.setTransformation (rhsActor.Transformation() * util::translate (correction));

            lhs.velocity = lhsReflect;
            rhs.velocity = rhsReflect;
        }

        // Trigger the collision events.
        if (lhs.onCollide)
        {
            lhs.onCollide (rhs);
        }

        if (rhs.onCollide)
        {
            rhs.onCollide (lhs);
        }
    }
}
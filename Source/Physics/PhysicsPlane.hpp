#ifndef SPC_PHYSICS_PLANE_ASP_HPP
#define SPC_PHYSICS_PLANE_ASP_HPP


// Engine headers.
#include <Physics/PhysicsObject.hpp>


namespace spc
{
    /// <summary> 
    /// A PhysicsObject which should use plane collision with other objects.
    /// </summary>
    class PhysicsPlane final : public PhysicsObject
    {
        public:

            /////////////////////////////////
            // Constructors and destructor //
            /////////////////////////////////

            PhysicsPlane()                                      = default;
            PhysicsPlane (const PhysicsPlane& copy)             = default;
            PhysicsPlane& operator= (const PhysicsPlane& copy)  = default;
            ~PhysicsPlane() override final                      = default;
        
            PhysicsPlane (PhysicsPlane&& move);
            PhysicsPlane& operator= (PhysicsPlane&& move);


            ///////////////////////
            // Object properties //
            ///////////////////////

            /// <summary> Obtains the castable type of the PhysicsObject. </summary>
            /// <returns> PhysicsObject::Type::Sphere. </returns>
            inline Type getType() const override final { return Type::Plane; }

            /// <summary> Calculates the normal vector of the plane from the actors transformation. </summary>
            /// <returns> The normal direction of the plane. </returns>
            tyga::Vector3 normal() const;
    };
}

#endif
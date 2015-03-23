#ifndef SPC_PHYSICS_SPHERE_ASP_HPP
#define SPC_PHYSICS_SPHERE_ASP_HPP


// Engine headers.
#include <Physics/PhysicsObject.hpp>


namespace spc
{
    /// <summary> 
    /// A PhysicsObject which should use sphere collision.
    /// </summary>
    class PhysicsSphere final : public PhysicsObject
    {
        public: 

            /////////////////////////////////
            // Constructors and destructor //
            /////////////////////////////////

            PhysicsSphere()                                         = default;
            PhysicsSphere (const PhysicsSphere& copy)               = default;
            PhysicsSphere& operator= (const PhysicsSphere& copy)    = default;
            ~PhysicsSphere() override final                         = default;
        
            PhysicsSphere (PhysicsSphere&& move);
            PhysicsSphere& operator= (PhysicsSphere&& move);


            ///////////////////////
            // Object properties //
            ///////////////////////

            /// <summary> Obtains the castable type of the PhysicsObject. </summary>
            /// <returns> PhysicsObject::Type::Sphere. </returns>
            Type getType() const override final { return Type::Sphere; }
            

            /////////////////
            // Public data //
            /////////////////

            float radius { 0.f }; //!< The radius of the sphere collider.
    };
}

#endif
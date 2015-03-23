#ifndef SPC_PHYSICS_BOX_ASP_HPP
#define SPC_PHYSICS_BOX_ASP_HPP


// Engine headers.
#include <Physics/PhysicsObject.hpp>


namespace spc
{
    /// <summary> 
    /// A PhysicsObject which should use box collision with other objects.
    /// </summary>
    class PhysicsBox final : public PhysicsObject
    {
        public:
        
            /////////////////////////////////
            // Constructors and destructor //
            /////////////////////////////////

            PhysicsBox()                                    = default;
            PhysicsBox (const PhysicsBox& copy)             = default;
            PhysicsBox& operator= (const PhysicsBox& copy)  = default;
            ~PhysicsBox() override final                    = default;
        
            PhysicsBox (PhysicsBox&& move);
            PhysicsBox& operator= (PhysicsBox&& move);


            ///////////////////////
            // Object properties //
            ///////////////////////

            /// <summary> Obtains the castable type of the PhysicsObject. </summary>
            /// <returns> PhysicsObject::Type::Sphere. </returns>
            Type getType() const override final { return Type::Box; }

            /// <summary> Obtains a vector containing the rotation on the X axis of the box. </summary>
            /// <returns> A rotation vector. </returns>
            tyga::Vector3 U() const;        

            /// <summary> Obtains a vector containing the rotation on the Y axis of the box. </summary>
            /// <returns> A rotation vector. </returns>
            tyga::Vector3 V() const;
        
            /// <summary> Obtains a vector containing the rotation on the Z axis of the box. </summary>
            /// <returns> A rotation vector. </returns>
            tyga::Vector3 W() const;
    };
}

#endif
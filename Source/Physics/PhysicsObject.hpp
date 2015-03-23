#ifndef SPC_PHYSICS_OBJECT_ASP_HPP
#define SPC_PHYSICS_OBJECT_ASP_HPP


// Engine headers.
#include <tyga/Actor.hpp>
#include <tyga/Math.hpp>


namespace spc
{
    /// <summary>
    /// A base class for every collidable type usable in the PhysicsSystem.
    /// </summary>
    class PhysicsObject : public tyga::ActorComponent
    {
        public:    

            /// <summary>
            /// An enumeration representing each collidable type, allows for safe downcasting.
            /// </summary>
            enum class Type : int
            {
                Box     = 0,    //!< Represents a PhysicsBox object.
                Plane   = 1,    //!< Represents a PhysicsPlane object.
                Sphere  = 2     //!< Represents a PhysicsSphere object.
            };


            /////////////////////////////////
            // Constructors and destructor //
            /////////////////////////////////

            PhysicsObject()                                         = default;
            PhysicsObject (const PhysicsObject& copy)               = default;
            PhysicsObject& operator= (const PhysicsObject& copy)    = default;
            virtual ~PhysicsObject()                                = default;
        
            PhysicsObject (PhysicsObject&& move);
            PhysicsObject& operator= (PhysicsObject&& move);


            ///////////////////////
            // Object properties //
            ///////////////////////

            /// <summary> Queries an object to determine a suitable type to downcast to. </summary>
            /// <returns> The castable type of the object. </returns>
            virtual Type getType() const = 0;

            /// <summary> Calculate the world position of the object from the Actors transform. </summary>
            /// <returns> The position of the object. </returns>
            tyga::Vector3 position() const;

            /// <summary> Gets the mass of the object. </summary>
            /// <returns> The mass of the object in kilograms. </returns>
            float getMass() const { return m_mass; }

            /// <summary> Sets the mass of the object. </summary>
            /// <param name="mass"> A new mass in kilograms, this cannot be set to 0. </param>
            void setMass (const float mass);

            
            /////////////////
            // Public data //
            /////////////////

            tyga::Vector3   velocity    { };    //!< The current velocity of the object.
            tyga::Vector3   force       { };    //!< The force to be applied to the object on the next physics update.

        protected:

            ///////////////////
            // Internal data //
            ///////////////////

            float   m_mass  { 1.f };    //!< A mass value for the object in kilograms (KG).
    };
}

#endif
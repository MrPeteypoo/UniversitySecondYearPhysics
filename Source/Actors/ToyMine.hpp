#ifndef SPC_TOY_MINE_ASP_HPP
#define SPC_TOY_MINE_ASP_HPP


// Engine headers.
#include <tyga/ActorDelegate.hpp>


// Forward declarations.
namespace tyga { class Vector3; }
class Badger;


namespace spc
{
    // Forward declarations.
    class PhysicsObject;
    class PhysicsSphere;


    /// <summary>
    /// A small sphere which emits an explosive upon collision with a Badger.
    /// </summary>
    class ToyMine final : public tyga::ActorDelegate
    {
        public:

            /////////////////////////////////
            // Constructors and destructor //
            /////////////////////////////////

            ToyMine()                                   = default;

            ToyMine (ToyMine&& move);
            ToyMine& operator= (ToyMine&& move);

            ToyMine (const ToyMine& copy)               = default;
            ToyMine& operator= (const ToyMine& copy)    = default;
            ~ToyMine()                                  = default;


            ////////////
            // Events //
            ////////////

            /// <summary> The function to be called upon collision with another object. </summary>
            /// <param name="other"> The object we are colliding with. </param>
            void onCollision (PhysicsObject& other);

            
            //////////////////////
            // Public interface //
            //////////////////////

            /// <summary> Reset the position and mass of the object. </summary>
            /// <param name="position"> The new position for the ToyMine. </param>
            /// <param name="mass"> The new mass of the ToyMine. </param>
            void reset (const tyga::Vector3& position, const float mass);

            /// <summary> Apply a force to the ToyMine. </summary>
            /// <param name="force"> The force to apply. </param>
            void applyForce (const tyga::Vector3& force);

            /// <summary> Trigger the explosion of the ToyMine. </summary>
            void trigger();

        private:

            ///////////////
            // Game loop //
            ///////////////

            /// <summary> Create the ToyMine in the scene. </summary>
            /// <param name="actor"> The Actor to attach to. </param>
            void actorDidEnterWorld (std::shared_ptr<tyga::Actor> actor) override;

            /// <summary> Clean up after ourselves. </summary>
            /// <param name="actor"> The Actor we're attached to. </param>
            void actorWillLeaveWorld (std::shared_ptr<tyga::Actor> actor) override;

            /// <summary> The update function, this is called every frame. </summary>
            /// <param name="actor"> The Actor we're attached to. </param>
            void actorClockTick (std::shared_ptr<tyga::Actor> actor) override;


            ///////////////////
            // Internal data //
            ///////////////////

            std::shared_ptr<spc::PhysicsSphere> m_collider  { nullptr };    //!< The collider of the mine.
    };
}

#endif
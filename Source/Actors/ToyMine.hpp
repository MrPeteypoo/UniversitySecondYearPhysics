#ifndef SPC_TOY_MINE_ASP_HPP
#define SPC_TOY_MINE_ASP_HPP


// Engine headers.
#include <tyga/ActorDelegate.hpp>


// Forward declarations.
namespace tyga { class Vector3; }


namespace spc
{
    // Forward declarations.
    class PhysicsSphere;


    class ToyMine final : public tyga::ActorDelegate
    {
        public:

            ToyMine();

            void reset(const tyga::Vector3& position, const float mass);

            void applyForce(const tyga::Vector3& force);

            void trigger();

        private:

            void actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor) override;

            void actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor) override;

            void actorClockTick(std::shared_ptr<tyga::Actor> actor) override;

            std::shared_ptr<spc::PhysicsSphere> physics_model_;

    };
}

#endif
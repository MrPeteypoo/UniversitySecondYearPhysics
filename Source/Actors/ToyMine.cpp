#include "ToyMine.hpp"
#include <tyga/Actor.hpp>
#include <tyga/ActorWorld.hpp>
#include <tyga/GraphicsCentre.hpp>
#include <tyga/Log.hpp>
#include <tyga/Math.hpp>
#include <Physics/PhysicsSystem.hpp>
#include <Physics/PhysicsSphere.hpp>
#include <Utility/Tyga.hpp>


namespace spc
{
    //////////////////
    // Constructors //
    //////////////////

    ToyMine::ToyMine (ToyMine&& move)
    {
        *this = std::move (move);
    }


    ToyMine& ToyMine::operator= (ToyMine&& move)
    {
        if (this != &move)
        {
            m_collider = std::move (move.m_collider);
        }

        return *this;
    }


    ////////////
    // Events //
    ////////////

    void ToyMine::onCollision (PhysicsObject& other)
    {
        // Because of the framework I have to have a retarded name property in the PhysicsObject class
        // which indicates that I've collided with a Badger........
        if (other.name == "Badger")
        {
            trigger();
        }
    }


    /////////////////////
    // Public inteface //
    /////////////////////

    void ToyMine::reset (const tyga::Vector3& position, const float mass)
    {
        // NB: this method should not need changing
        Actor()->setTransformation(util::translate (position));
        m_collider->setMass (mass);
    }


    void ToyMine::applyForce (const tyga::Vector3& force)
    {
        // NB: this method should not need changing
        m_collider->force += force;
        m_collider->velocity = tyga::Vector3(0,0,0);
    }


    void ToyMine::trigger()
    {
        // TODO: code to begin the explosion animation/simulation
        tyga::debugLog("ToyMine::trigger: toy should explode now");
        removeFromWorld();
    }


    ///////////////
    // Game loop //
    ///////////////

    void ToyMine::actorDidEnterWorld (std::shared_ptr<tyga::Actor> actor)
    {
        auto world = tyga::ActorWorld::defaultWorld();
        auto graphics = tyga::GraphicsCentre::defaultCentre();
        auto physics = spc::PhysicsSystem::defaultSystem();

        auto graphics_model = graphics->newModel();
        graphics_model->material = graphics->newMaterial();
        graphics_model->material->colour = tyga::Vector3(1, 0.33f, 0);
        graphics_model->mesh = graphics->newMeshWithIdentifier("sphere");
        graphics_model->xform = tyga::Matrix4x4( 0.5f,    0,    0,   0,
                                                    0, 0.5f,    0,   0,
                                                    0,    0, 0.5f,   0,
                                                    0,    0,    0,   1);

        auto physics_model = physics->createObject<spc::PhysicsSphere>();
        physics_model->radius = 0.25f;
        physics_model->setMass (1.f);
        m_collider = physics_model;
        m_collider->onCollide = [&] (PhysicsObject& object) { onCollision (object); };

        actor->attachComponent(graphics_model);
        actor->attachComponent(physics_model);
        world->addActor(actor);
    }


    void ToyMine::actorWillLeaveWorld (std::shared_ptr<tyga::Actor> actor)
    {
    }

    void ToyMine::actorClockTick (std::shared_ptr<tyga::Actor> actor)
    {
        // HINT: once the toy has exploded and there is no visible traces left
        //       then call this->removeFromWorld() to free the memory
    }
}
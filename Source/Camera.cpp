#include "Camera.hpp"
#include "MyUtils.hpp"
#include <tyga/Actor.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>
#include <tyga/ActorWorld.hpp>
#include <tyga/GraphicsCentre.hpp>
#include <algorithm>


Camera::
Camera()
{
    heading_angle_ = 2;
    heading_speed_ = 0;
    pan_distance_ = 5;
    pan_speed_ = 0;

    auto graphics = tyga::GraphicsCentre::defaultCentre();

    auto camera = graphics->newCamera();
    camera->vertical_field_of_view_radians = 0.8f;

    camera_actor_ = std::make_shared<tyga::Actor>();
    camera_actor_->attachComponent(camera);
}

void Camera::
setHeadingAngle(float radians)
{
    heading_angle_ = radians;
}

void Camera::
setHeadingSpeed(float spd)
{
    heading_speed_ = spd;
}

void Camera::
setPanDistance(float distance)
{
    pan_distance_ = std::max(0.f, distance);
}

void Camera::
setPanSpeed(float speed)
{
    pan_speed_ = speed;
}

void Camera::
actorDidEnterWorld(std::shared_ptr<tyga::Actor> actor)
{
    auto world = tyga::ActorWorld::defaultWorld();

    world->addActor(camera_actor_);
}

void Camera::
actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor)
{
    auto world = tyga::ActorWorld::defaultWorld();

    world->removeActor(camera_actor_);
}

void Camera::
actorClockTick(std::shared_ptr<tyga::Actor> actor)
{
    const float time = tyga::BasicWorldClock::CurrentTime();
    const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();

    setHeadingAngle(heading_angle_ + heading_speed_ * delta_time);
    const float PAN_SPEED_MULTIPLIER = 5;
    setPanDistance(pan_distance_ +
                   PAN_SPEED_MULTIPLIER * pan_speed_ * delta_time);

    const float a = std::cosf(heading_angle_);
    const float b = std::sinf(heading_angle_);
    const float elevation_angle = float(M_PI) / -6.f;
    const float c = std::cosf(elevation_angle);
    const float d = std::sinf(elevation_angle);
    const float e = pan_distance_;
    auto camera_xform = tyga::Matrix4x4(       a,       0,      -b,       0,
                                             d*b,       c,     d*a,       0,
                                             c*b,      -d,     c*a,       0,
                                           e*c*b,    -e*d,   e*c*a,       1);

    camera_actor_->setTransformation(camera_xform * actor->Transformation());
}

#include "MyDemo.hpp"
#include "Badger.hpp"
#include "Camera.hpp"
#include "ToyMine.hpp"
#include "MyPhysicsCentre.hpp"
#include <tyga/Application.hpp>
#include <tyga/ActorWorld.hpp>
#include <tyga/InputStateProtocol.hpp>
#include <tyga/BasicRenderer.hpp>
#include <tyga/GraphicsCentre.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>
#include <iostream>

const tyga::Vector3 MyDemo::MIN_BOUND = tyga::Vector3(-20, 0.3f, -10);
const tyga::Vector3 MyDemo::MAX_BOUND = tyga::Vector3(20, 1.5f, 10);

MyDemo::
MyDemo()
{
    camera_mode_ = kCameraStatic;
    trigger_time_ = std::numeric_limits<float>::max();
}

void MyDemo::
applicationWindowWillInit(int& width,
                          int& height,
                          int& sample_count,
                          bool& windowed)
{
    width = 1024;
    height = 576;

    std::cout << "Animation and Simulation Programming 2013" << std::endl;
    std::cout << "Badger Banging" << std::endl << std::endl;
    std::cout << "Use the gamepad thumbsticks to control the Badger vehicle." << std::endl;
    std::cout << "Hold the right shoulder button to control the camera." << std::endl;
    std::cout << "Press F2 to swap camera modes." << std::endl;
    std::cout << "Press F5 to reset the toys." << std::endl;
    std::cout << "Press spacebar to prematurely bang the toys." << std::endl << std::endl;
}

void MyDemo::
applicationDidStart()
{
    renderer_ = std::make_shared<tyga::BasicRenderer>();
    tyga::Application::setWindowViewDelegate(renderer_);

    tyga::Application::addRunloopTask(MyPhysicsCentre::defaultCentre());
    tyga::Application::addRunloopTask(tyga::GraphicsCentre::defaultCentre());
    tyga::Application::addRunloopTask(tyga::ActorWorld::defaultWorld());

    tyga::Application::setRunloopFrequency(60);


    auto world = tyga::ActorWorld::defaultWorld();
    auto graphics = tyga::GraphicsCentre::defaultCentre();
    auto physics = MyPhysicsCentre::defaultCentre();


    auto floor_mesh = graphics->newMeshWithIdentifier("cube");
    auto floor_material = graphics->newMaterial();
    floor_material->colour = tyga::Vector3(0.9f, 0.9f, 0.25f);

    auto floor_model = graphics->newModel();
    floor_model->material = floor_material;
    floor_model->mesh = floor_mesh;
    auto floor_actor = std::make_shared<tyga::Actor>();
    floor_actor->attachComponent(floor_model);
    auto floor_xform = tyga::Matrix4x4(      40,       0,       0,       0,
                                              0,    0.2f,       0,       0,
                                              0,       0,      20,       0,
                                              0,   -0.1f,       0,       1);
    floor_actor->setTransformation(floor_xform);
    world->addActor(floor_actor);


    camera_ = std::make_shared<Camera>();
    camera_->addToWorld(world);
    camera_->setHeadingAngle(0.2f);
    camera_->setPanDistance(30);


    badger_ = Badger::makeBadgerWithBloke(world);
    auto badger_box = physics->newBox();
    badger_->boundsActor()->attachComponent(badger_box);


    resetToys();

}

void MyDemo::
applicationRunloopWillBegin()
{
    tyga::BasicWorldClock::update();

    const float time = tyga::BasicWorldClock::CurrentTime();
    if (trigger_time_ < time) {
        for (auto toy : toys_) {
            toy->trigger();
        }
        trigger_time_ = std::numeric_limits<float>::max();
    }

    auto camera_xform = tyga::Matrix4x4(       1,       0,       0,       0,
                                               0,       1,       0,       0,
                                               0,       0,       1,       0,
                                               0,       1,       0,       1);
    switch (camera_mode_)
    {
    case MyDemo::kCameraStatic:
        camera_->Actor()->setTransformation(camera_xform);
        break;
    case MyDemo::kCameraTracking:
        camera_->Actor()->setTransformation(
            camera_xform * badger_->Actor()->Transformation());
        break;
    }

}

void MyDemo::
applicationRunloopDidEnd()
{
    renderer_->setGraphicsScene(tyga::GraphicsCentre::defaultCentre()->scene());
}

void MyDemo::
applicationWillStop()
{
}

void MyDemo::
applicationInputStateChanged(
    std::shared_ptr<tyga::InputStateProtocol> input_state)
{
    if (input_state->gamepadPresent(0))
    {
        if (input_state->gamepadButtonDownCount(
            0, tyga::kInputGamepadButtonRightShoulder))
        {
            float camera_heading_speed = input_state
                ->gamepadAxisPosition(0, tyga::kInputGamepadAxisRightThumbX);
            camera_->setHeadingSpeed(camera_heading_speed);
            float camera_pan_speed = -input_state
                ->gamepadAxisPosition(0, tyga::kInputGamepadAxisLeftThumbY);
            camera_->setPanSpeed(camera_pan_speed);
        }
        else
        {
            float badger_speed = input_state
                ->gamepadAxisPosition(0, tyga::kInputGamepadAxisLeftThumbY);
            badger_->setSpeed(badger_speed);
            float badger_turn = input_state
                ->gamepadAxisPosition(0, tyga::kInputGamepadAxisRightThumbX);
            badger_->setTurnAngle(badger_turn);
        }
    }
    else
    {
        float badger_speed = input_state
            ->keyboardAxisPosition(tyga::kInputKeyboardAxisUpDown);
        badger_->setSpeed(badger_speed);
        float badger_turn = input_state
            ->keyboardAxisPosition(tyga::kInputKeyboardAxisLeftRight);
        badger_->setTurnAngle(badger_turn);
    }

    if (input_state->keyboardKeyDownCount(tyga::kInputKeyF2) == 1) {
        camera_mode_ = CameraMode((camera_mode_+1) % kCameraMAX);
        switch (camera_mode_)
        {
        case MyDemo::kCameraStatic:
            camera_->setHeadingAngle(0.2f);
            camera_->setPanDistance(30);
            break;
        case MyDemo::kCameraTracking:
            camera_->setHeadingAngle(2);
            camera_->setPanDistance(5);
            break;
        }
    }

    if (input_state->keyboardKeyDownCount(tyga::kInputKeyF5) == 1) {
        resetToys();
    }

    if (input_state->keyboardKeyDownCount(tyga::kInputKeySpace) == 1) {
        triggerToys();
    }
}

void MyDemo::
resetToys()
{
    std::uniform_int_distribution<int> n_rand(10, 50);
    std::uniform_real_distribution<float> x_rand(MIN_BOUND.x, MAX_BOUND.x);
    std::uniform_real_distribution<float> y_rand(MIN_BOUND.y, MAX_BOUND.y);
    std::uniform_real_distribution<float> z_rand(MIN_BOUND.z, MAX_BOUND.z);
    std::uniform_real_distribution<float> m_rand(0.5f, 1.5f);

    auto world = tyga::ActorWorld::defaultWorld();

    toys_.resize(n_rand(rand));
    for (auto& toy : toys_) {
        toy = std::make_shared<ToyMine>();
        toy->addToWorld(world);
        auto position = tyga::Vector3(x_rand(rand), y_rand(rand), z_rand(rand));
        auto mass = m_rand(rand);
        toy->reset(position, mass);
    }
}

void MyDemo::
triggerToys()
{
    std::uniform_real_distribution<float> x_rand(-0.2f, 0.2f);
    std::uniform_real_distribution<float> z_rand(-0.2f, 0.2f);

    for (auto toy : toys_) {
        auto dir = tyga::unit(tyga::Vector3(x_rand(rand), 1, z_rand(rand)));
        auto force = 600 * dir;
        toy->applyForce(force);
    }

    std::uniform_real_distribution<float> t_rand(1, 3);
    trigger_time_ = tyga::BasicWorldClock::CurrentTime() + t_rand(rand);
}

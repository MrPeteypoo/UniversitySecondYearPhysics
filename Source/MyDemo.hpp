#pragma once

#include <tyga/Math.hpp>
#include <tyga/ApplicationDelegate.hpp>
#include <tyga/GraphicsRendererProtocol.hpp>
#include <random>
#include <vector>

class Badger;
class Camera;
class ToyMine;

class MyDemo : public tyga::ApplicationDelegate
{
public:

    MyDemo();

private:

    virtual void
    applicationWindowWillInit(int& width,
                              int& height,
                              int& sample_count,
                              bool& windowed);

    virtual void
    applicationDidStart() override;

    virtual void
    applicationRunloopWillBegin() override;

    virtual void
    applicationRunloopDidEnd() override;

    virtual void
    applicationWillStop() override;

    virtual void
    applicationInputStateChanged(
        std::shared_ptr<tyga::InputStateProtocol> input_state) override;

    void
    resetToys();

    void
    triggerToys();

    std::shared_ptr<tyga::GraphicsRendererProtocol> renderer_;

    enum CameraMode { kCameraStatic, kCameraTracking, kCameraMAX };
    CameraMode camera_mode_;

    std::shared_ptr<Camera> camera_;
    std::shared_ptr<Badger> badger_;

    std::minstd_rand rand;
    static const tyga::Vector3 MIN_BOUND;
    static const tyga::Vector3 MAX_BOUND;

    std::vector<std::shared_ptr<ToyMine>> toys_;

    float trigger_time_;
};

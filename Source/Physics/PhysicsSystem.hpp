#ifndef SPC_PHYSICS_SYSTEM_ASP_HPP
#define SPC_PHYSICS_SYSTEM_ASP_HPP


// STL headers.
#include <memory>
#include <type_traits>
#include <vector>


// Engine headers.
#include <tyga/Math.hpp>
#include <tyga/RunloopTaskProtocol.hpp>


namespace spc
{
    // Forward declarations.
    class PhysicsObject;

    
    /// <summary>
    /// A physics simulation system which aims to reproduce realistic looking physics with multiple types
    /// of collision detection available.
    /// </summary>
    class PhysicsSystem final : public tyga::RunloopTaskProtocol
    {
        public:           

            /////////////////////////////////
            // Constructors and destructor //
            /////////////////////////////////

            /// <summary> Construct a PhysicsSystem, reserving the desired amount of PhysicsObject's. </summary>
            /// <param name="reserve"> How many objects should be reserved at creation. </param>
            PhysicsSystem (const unsigned int reserve = 100);

            PhysicsSystem (PhysicsSystem&& move);
            PhysicsSystem& operator= (PhysicsSystem&& move);

            PhysicsSystem (const PhysicsSystem& copy)               = default;
            PhysicsSystem& operator= (const PhysicsSystem& copy)    = default;
            ~PhysicsSystem()                                        = default;


            //////////////////////
            // Public interface //
            //////////////////////

            /// <summary> Returns the default system. </summary>
            /// <returns> The default system. </returns>
            static std::shared_ptr<PhysicsSystem> defaultSystem();
            
            /// <summary> Make a request for a new PhysicsObject to be created an registered with the system. </summary>
            /// <param name="T"> The type of object to create, this will fail if it does not inherit from PhysicsObject. </param>
            /// <returns> A pointer to the specified descendant of PhysicsObject. </returns>
            template <typename T> 
            std::shared_ptr<typename std::enable_if<std::is_base_of<PhysicsObject, T>::value && !std::is_same<PhysicsObject, T>::value, T>::type> 
            createObject();

            /// <summary> Gets the vector containing the acceleration applied to every object each frame. <summary>
            /// <returns> The gravity to be applied. </returns>
            const tyga::Vector3& getGravity() const         { return m_gravity; }

            /// <summary> Sets the gravity value that will be applied to every object each frame. </summary>
            /// <param name="gravity"> The new gravity value. </param>
            void setGravity (const tyga::Vector3& gravity)  { m_gravity = gravity; }

        private:

            //////////////////////////////
            // Delegate implementations //
            //////////////////////////////

            /// <summary> Runs the collision detection algorithm for each registered object in the scene. </summary>
            void runloopWillBegin() override final;

            /// <summary> Moves all objects in the scene using a numerical integration algorithm. </summary>
            void runloopExecuteTask() override final;

            /// <summary> Removes all expired objects from the scene, increasing efficiency of future iterations through the std::vector. </summary>
            void runloopDidEnd() override final;


            ///////////////////
            // Internal data //
            ///////////////////

            static std::shared_ptr<PhysicsSystem>       m_defaultSystem;    //!< The default system to use be used by games.
            
            tyga::Vector3                               m_gravity   { };    //!< The gravity to apply to every PhysicsObject. Defaults to earths gravity.
            std::vector<std::weak_ptr<PhysicsObject>>   m_objects   { };    //!< A collection of every PhysicsObject in the scene.

    };


    /////////////////////
    // Implementations //
    /////////////////////

    template <typename T> 
    std::shared_ptr<typename std::enable_if<std::is_base_of<PhysicsObject, T>::value && !std::is_same<PhysicsObject, T>::value, T>::type>
    PhysicsSystem::createObject()
    {
        // Create the new object.
        const auto object = std::make_shared<T>();

        // Add the new object to the vector.
        m_objects.emplace_back (object);

        // Return the new object.
        return object;
    }
}

#endif
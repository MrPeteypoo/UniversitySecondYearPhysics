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
            
            /// <summary> Make a request for a new PhysicsObject to be created an registered with the system. </summary>
            /// <tparam name="T"> The type of object to create, this will fail if it does not inherit from PhysicsObject. </tparam>
            /// <returns> A new PhysicsPlane pointer. </returns>
            template <typename T> 
            std::shared_ptr<typename std::enable_if<std::is_base_of<PhysicsObject, T>::value, T>::type> 
            createObject();

            /// <summary> Returns the default system. </summary>
            /// <returns> The default system. </returns>
            static std::shared_ptr<PhysicsSystem> defaultSystem();

        private:

            //////////////////////////////
            // Delegate implementations //
            //////////////////////////////

            void runloopWillBegin() override final;

            void runloopExecuteTask() override final;

            void runloopDidEnd() override final;


            /////////////
            // Utility //
            /////////////


            ///////////////////
            // Internal data //
            ///////////////////
            
            tyga::Vector3                               m_gravity   { };    //!< The gravity to apply to every PhysicsObject.
            std::vector<std::weak_ptr<PhysicsObject>>   m_objects   { };    //!< A collection of every PhysicsObject in the scene.

            static std::shared_ptr<PhysicsSystem>       m_defaultSystem;    //!< The default system to use be used by games.

    };


    /////////////////////
    // Implementations //
    /////////////////////

    template <typename T> std::shared_ptr<typename std::enable_if<std::is_base_of<PhysicsObject, T>::value, T>::type>  
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
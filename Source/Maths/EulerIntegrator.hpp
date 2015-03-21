#ifndef EULER_INTEGRATOR_HPP
#define EULER_INTEGRATOR_HPP


/// <summary>
/// A simple physics integrator which makes use of the explicit Euler method for simulation.
/// </summary>
template <typename T, typename U> class EulerIntegrator
{
    public:

        /// <summary> 
        /// Uses explicit Euler to increment the position and velocity values appropriately. 
        /// </summary>
        /// <param name="position"> The position variable to be modified. </param>
        /// <param name="velocity"> The velocity variable to be modified. </param>
        /// <param name="acceleration"> How much the velocity is currently accelerating per second. </param>
        /// <param name="deltaTime"> The time incrementation to use. </param>
        static void integrate (T& position, T& velocity, const T& acceleration, const U deltaTime);
};

template <typename T, typename U> 
void EulerIntegrator<T, U>::integrate (T& position, T& velocity, const T& acceleration, const U deltaTime)
{
    /// Explicit Euler is an incredibly fast but inaccurate method of simulating physics. It should not
    /// be used unless the timestep is particularly small, the larger the timestep the higher the margin
    /// for error will be.
    position += velocity * deltaTime;
    velocity += acceleration * deltaTime;
}

#endif
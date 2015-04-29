#ifndef RUNGE_KUTTA_4_INTEGRATOR_HPP
#define RUNGE_KUTTA_4_INTEGRATOR_HPP


// STL headers.
#include <functional>


/// <summary>
/// A physics integrator which implements the Runge-Kutta method to provide pretty accurate simulation.
/// </summary>
/// <param name="T"> The type used when integrating values. </param>
/// <param name="U"> A type used for time values, typically a float or a double. </param>
template <typename T, typename U = float> class RK4Integrator
{
    public:
        
        /// <summary> 
        /// A const function which calculates acceleration when given a position, velocity and a time value.
        /// </summary>
        using AccelFunc = std::function<T (const T&, const T&, const U)>;

        /// <summary> 
        /// Using the RK4 method, calculate appropriate positon and velocity values.
        /// </summary>
        /// <param name="position"> The initial position value to be modified. </param>
        /// <param name="velocity"> The initial velocity value to be modified. </param>
        /// <param name="calcAcceleration"> A simulation-dependant function which calculates acceleration at a given time point. </param>
        /// <param name="time"> The initial time value to use for integration. </param>
        /// <param name="deltaTime"> The time incrementation to use. </param>
        static void integrate (T& position, T& velocity, const AccelFunc& calcAcceleration, const U time, const U deltaTime);

    private:

        /// <summary>
        /// A simple struct containing a velocity/acceleration pair, this represents a single evaluation of the RK method.
        /// </summary>
        struct Evaluation final
        {
            T velocity      { };    //!< An evaluated velocity value.
            T acceleration  { };    //!< An evaluated acceleration value.

            Evaluation() = default;
            Evaluation (const T& vel, const T& accel) : velocity (vel), acceleration (accel) { }
        };

        /// <summary> 
        /// Calculates a particular stage of RK4 method using Euler.
        /// </summary>
        /// <param name="pos"> Initial position. </param>
        /// <param name="vel"> Initial velocity. </param>
        /// <param name="prev"> The previous evalution to base the current evaluation off, this could be blank. </param>
        /// <param name="accel"> A function to be called to calculate the acceleration of the evaluation. </param>
        /// <param name="time"> A time value to base the evaluation off. </param>
        /// <param name="delta"> The delta value to use. </param>
        /// <returns> An evaluation of velocity and acceleration after the given time point. </returns>
        static Evaluation calculate (const T& pos, const T& vel, const Evaluation& prev, const AccelFunc& accel, const U time, const U delta);
};


/////////////////////
// Implementations //
/////////////////////

template <typename T, typename U> void 
RK4Integrator<T, U>::integrate (T& position, T& velocity, const AccelFunc& calcAcceleration, const U time, const U deltaTime)
{
    /// RK4 integration is a highly accurate algorithm which uses weightings to determine relatively accurate
    /// simulation values. It combines Euler calculations with Taylor series weighting. It could be 
    /// considered overkill for gaming applications but it isn't overly expensive if a high degree of 
    /// accuracy is preferred.
    
    /// This code is heavily influenced by an article from Glenn Fiedler.
    /// Fiedler, Glenn. (2006) Integration basics. 
    /// Available at: http://gafferongames.com/game-physics/integration-basics/ (Accessed: 21/03/2015).
    
    // Cache anything calculated multiple times.
    const auto halfDelta = deltaTime / 2;
    const auto sixth     = (U) 1 / 6;
    
    // RK4 uses four evaluations to create values to weight.
    Evaluation initial, first, second, third, fourth;

    first  = calculate (position, velocity, initial, calcAcceleration, time, (U) 0);
    second = calculate (position, velocity, first,   calcAcceleration, time, halfDelta);
    third  = calculate (position, velocity, second,  calcAcceleration, time, halfDelta);
    fourth = calculate (position, velocity, third,   calcAcceleration, time, deltaTime);

    // Now we use Taylor Series expansion to weight the values.
    // Formula = 1/6 * (dxdt1 + 2 * (dxdt2 + dxdt3) + dxdt4).
    const auto positionChange = sixth * (first.velocity + 2 * (second.velocity + third.velocity) + fourth.velocity);
    const auto velocityChange = sixth * (first.acceleration + 2 * (second.acceleration + third.acceleration) + fourth.acceleration);

    // Finally modify the position and velocity values.
    position += positionChange * deltaTime;
    velocity += velocityChange * deltaTime;
}


template <typename T, typename U> typename RK4Integrator<T, U>::Evaluation
RK4Integrator<T, U>::calculate (const T& pos, const T& vel, const Evaluation& prev, const AccelFunc& accel, const U time, const U delta)
{
    // Use Euler to calculate the new position and velocity.
    const auto position = pos + prev.velocity * delta;
    const auto velocity = vel + prev.acceleration * delta;

    // Use the given acceleration function to calculate the acceleration to return.
    return { velocity, accel (position, velocity, time + delta) };
}

#endif
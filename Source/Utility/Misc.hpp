#ifndef UTILITY_MISC_ASP_HPP
#define UTILITY_MISC_ASP_HPP


// STL headers.
#include <cassert>
#include <functional>
#include <vector>


namespace util
{
    /// <summary> Squares a value. </summary>
    /// <param name="value"> A value to square. </param>
    /// <returns> The squared value. </returns>
    template <typename T> inline T squared (const T value);

    /// <summary> 
    /// Removes any objects from the given vector provided the object meets the given condition. Removal of any object
    /// will leave the elements in an undefined order.
    /// </summary>
    /// <param name="data"> The vector of objects to check. </param>
    /// <param name="condition"> The predicate which indicates whether an object should be removed. </param>
    template <typename T> void unorderedRemove (std::vector<T>& data, const std::function<bool (T&)>& condition);
}


template <typename T> T util::squared (const T value)
{
    return value * value;
}


template <typename T> void util::unorderedRemove (std::vector<T>& data, const std::function<bool (T&)>& condition)
{
    // Pre-condition: Condition function is valid.
    assert (condition);

    // Loop through each element.
    for (auto i = 0U; i < data.size(); ++i)
    {
        // Cache the element.
        auto& element = data[i];

        // Swap and pop the element if the condition says so.
        if (condition (element))
        {
            std::swap (element, data.back());
            data.pop_back();

            // Ensure we don't skip an object.
            --i;
        }
    }
}

#endif
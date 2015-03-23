#ifndef UTILITY_MISC_ASP_HPP
#define UTILITY_MISC_ASP_HPP


// STL headers.
#include <functional>
#include <vector>


namespace util
{
    template <typename T> void unorderedRemove (std::vector<T>& data, const std::function<bool (T&)>& condition)
    {
        // Pre-condition: Condition function is valid.
        if (condition)
        {
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
    }
}


#endif
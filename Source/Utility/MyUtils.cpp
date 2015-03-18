#include "MyUtils.hpp"

/*
 * Tutorial: use this source and its associated header file to declare
 *           and define your own helper functions.
 */

namespace your_name_here
{

tyga::Matrix4x4 translate(float x, float y, float z)
{
    // TODO: this function doesn't work correctly
    return tyga::Matrix4x4(       1,       0,       0,       0,
                                  0,       1,       0,       0,
                                  0,       0,       1,       0,
                                  0,       0,       0,       1);
}

}

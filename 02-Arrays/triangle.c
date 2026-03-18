#include <cs50.h>
#include <stdio.h>

bool valid_triangle(float x, float y, float z);

int main(void)
{
    // Get 3 valid lengths
    float x;
    x = get_float("Please input the 1st number: ");

    float y;
    y = get_float("Please input the 2nd number: ");

    float z;
    z = get_float("Please input the 3rd number: ");

    if (valid_triangle(x,y,z))
    {
        printf("Valid triangle!\n");
    }
    else
    {
        printf("Invalid triangle!\n");
    }
}

bool valid_triangle(float x, float y, float z)
{
    // Check for all positive sides
    if (x <= 0 || y <= 0 || z <= 0)
    {
        return false;
    }

    // Check that sum of any two sides greater than the third
    else
    {
        if (x + y <= z || z + y <= x || x + z <= y)
        {
            return false;
        }
    }

    // If we passed both tests, we're good!
    return true;
}

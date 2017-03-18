#include <iostream>

#include "vector.h"

int main()
{
    Vector<int> vector;

    vector.push_back(1);
    vector.push_back(1);
    vector.push_back(1);
    vector.push_back(1);

    Vector<int> another_vector;
    another_vector = vector; // Copy assignment
}

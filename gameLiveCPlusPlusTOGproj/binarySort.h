#pragma once

#include"settings.h"

template < class t>
void quickSort(std::vector<t>& V, int low, int high, position pos)
{
    int i = low;
    int j = high;
    t pivot = V[(i + j) / 2];
    t temp = V[0];

    while (i <= j)
    {
        while ((abs(V[i].getPosition().i - pos.i) + abs(V[i].getPosition().j - pos.j)) < (abs(pivot.getPosition().i - pos.i) + abs(pivot.getPosition().j - pos.j))) {
            i++;
        }
        while ((abs(V[j].getPosition().i - pos.i) + abs(V[j].getPosition().j - pos.j)) > (abs(pivot.getPosition().i - pos.i) + abs(pivot.getPosition().j - pos.j))) {
            j--;
        }
        if (i <= j)
        {
            temp = V[i];
            V[i] = V[j];
            V[j] = temp;
            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(V, low, j, pos);
    if (i < high)
        quickSort(V, i, high, pos);
}

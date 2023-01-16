#pragma once

#include <vector>


/// std::vector<t>& V
/// int low - 0
/// int high V.size() -1
/// 
/// + V[].fun()
template < class t>
void quickSort(std::vector<t>& V, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = V[(i + j) / 2];
    int temp;

    while (i <= j)
    {
        while (V[i] < pivot)
            i++;
        while (V[j] > pivot)
            j--;
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
        quickSort(V, low, j);
    if (i < high)
        quickSort(V, i, high);
}

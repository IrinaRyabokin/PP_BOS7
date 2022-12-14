#include <iostream>

using namespace std;

void init_array(long long *array, int size)
{
    for (int i = 0; i < size; i++)
        array[i] = i + 1;
}

void task1()
{
    const int NumElements = 100000;
    long long array[NumElements];
    init_array(array, NumElements);

    long long sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < NumElements; i++)
        sum += array[i];

    cout << "task1 sum = " << sum << endl;
}

void task2()
{
    const int NumElements = 1000;
    long long array[NumElements];
    init_array(array, NumElements);

    int size = NumElements;

    while (size > 1)
    {
        #pragma omp parallel for num_threads(size/2)
        for (int i = 0; i < size/2; i++)
        {
            array[i] += array[size - i - 1];
        }

        size = size/2 + size%2;
    }

    cout << "task2 sum = " << array[0] << endl;
}

int main()
{
    task1();
    task2();
    return 0;
}

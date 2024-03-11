#include <iostream>
#include <cmath>
#include <thread>

using namespace std;

int main()
{
    unsigned int n;
    unsigned int count_threads;
    int count_hit_points = 0;
    double x, y;

    cout << "Введите число точек: ";
    if (!(cin >> n)){
        cout << "Недопустимое значение!" << endl;
        return -1;
    }
    cout << "Введите число потоков (0 для автоматического определения): ";
    if (!(cin >> count_threads)){
        cout << "Недопустимое значение!" << endl;
        return -1;
    }
    if (count_threads == 0){
        count_threads = thread::hardware_concurrency();
        if (count_threads == 0){
            cout << "Не удалось вычислить автоматически" << endl;
            return -2;
        }
    }

#pragma omp parallel num_threads(count_threads) reduction(+:count_hit_points)
    {
#pragma omp for
        for (int i = 0; i < n; i++){
            x = (double) rand() / RAND_MAX * 2 - 1;;
            y = (double) rand() / RAND_MAX * 2 - 1;;
            if (pow(x, 2) + pow(y, 2) <= 1){
                count_hit_points += 1;
            }
        }
    }

    cout << "Пи ~= " << (double) 4 * count_hit_points / n << endl;

    return 0;
}

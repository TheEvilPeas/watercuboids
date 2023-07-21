#include "unittests.h"
#include "watervolumesolver.h"

#include "vector"
#include <cassert>
#include <iostream>

using namespace std;
/**
 *Пример создания теста
 *vector<vector<int>> matrixN = {
 *    {3, 3, 3},
 *    {3, 1, 3},
 *    {2, 3, 3},
 *};
 *Создаем объект WaterVolumeSolver
 *WaterVolumeSolver solverN(3, 3, matrixN);
 *
 *Вызываем функцию solve и проверяем ожидаемый результат
 *ll resultN = solverN.solve();
 *if (resultN == 2) {
 *    cout << "Test N passed!" << endl;
 *} else {
 *    cout << "Test N failed!" << endl;
 *}
 */

unitTests::unitTests()
{
    vector<vector<int>> matrix1 = {
                                   {3, 3, 3},
                                   {3, 1, 3},
                                   {2, 3, 3},
                                   };

    // Создаем объект WaterVolumeSolver
    WaterVolumeSolver solver1(3, 3, matrix1);

    // Вызываем функцию solve и проверяем ожидаемый результат
    ll result1 = solver1.solve();
    if (result1 == 2) {
        cout << "Test 1 passed!" << std::endl;
    } else {
        cout << "Test 1 failed!" << std::endl;
    }

    vector<vector<int>> matrix2 = {
                                   {3, 3, 4, 4, 4, 2},
                                   {3, 1, 3, 2, 1, 4},
                                   {7, 3, 1, 6, 4, 1},
                                   };

    // Создаем объект WaterVolumeSolver
    WaterVolumeSolver solver2(3, 6, matrix2);

    // Вызываем функцию solve и проверяем ожидаемый результат
    ll result2 = solver2.solve();
    if (result2 == 5) {
        cout << "Test 2 passed!" << std::endl;
    } else {
        cout << "Test 2 failed!" << std::endl;
    }

}

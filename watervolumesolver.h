#ifndef WATERVOLUMESOLVER_H
#define WATERVOLUMESOLVER_H

#include <vector>
#include <queue>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

/**
 * @brief Класс WaterVolumeSolver решает задачу о объеме воды.
 */
class WaterVolumeSolver {
public:
    vector<vector<int>> getWorkingMatrix() const;
    /**
     * @brief Конструктор класса WaterVolumeSolver.
     * @param rows Количество строк в матрице.
     * @param cols Количество столбцов в матрице.
     * @param matrix Матрица с высотами столбцов.
     */
    WaterVolumeSolver(int rows, int cols, vector<vector<int>>& matrix);

    /**
     * @brief Решает задачу о объеме воды.
     * @return Объем воды, который можно собрать.
     */
    ll solve();

private:
    int rowsMatrix; /**< Количество строк в матрице. */
    int colsMatrix; /**< Количество столбцов в матрице. */
    ll sumWater; /**< Суммарный объем воды. */
    vector<vector<int>> matrixInput; /**< Матрица с высотами столбцов. */
    vector<vector<int>> matrixOutput;
    vector<vector<bool>> matrixVisited; /**< Матрица для отслеживания посещенных клеток. */
    priority_queue<pair<int, pii>, vector<pair<int, pii>>, greater<pair<int, pii>>> pq; /**< Очередь с приоритетом для обхода клеток. */

    const int fx[4] = {0, 0, 1, -1}; /**< Массив смещений по оси x для соседних клеток. */
    const int fy[4] = {1, -1, 0, 0}; /**< Массив смещений по оси y для соседних клеток. */

    /**
     * @brief Проверяет, является ли клетка с координатами (x, y) допустимой для посещения.
     * @param x Координата x клетки.
     * @param y Координата y клетки.
     * @param L Высота текущей клетки.
     * @return true, если клетка допустима, иначе false.
     */
    bool valid(int x, int y, int L);

    /**
     * @brief Выполняет поиск в глубину для сбора воды.
     * @param ux Координата x текущей клетки.
     * @param uy Координата y текущей клетки.
     * @param L Высота текущей клетки.
     */
    void DepthFirstSearch(int ux, int uy, int L);
};

#endif // WATERVOLUMESOLVER_H

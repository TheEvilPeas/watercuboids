#include "watervolumesolver.h"

/**
 * @brief Конструктор класса WaterVolumeSolver.
 * @param rows Количество строк в матрице.
 * @param cols Количество столбцов в матрице.
 * @param matrix Матрица с высотами столбцов.
 */
WaterVolumeSolver::WaterVolumeSolver(int rows, int cols, vector<vector<int>>& matrix)
    : rowsMatrix(rows), colsMatrix(cols), matrixInput(matrix), matrixOutput(matrix), matrixVisited(rows, vector<bool>(cols, false)) {
    for (int i = 0; i < rowsMatrix; i++) {
        for (int j = 0; j < colsMatrix; j++) {
            if (i == 0 || i == rowsMatrix - 1 || j == 0 || j == colsMatrix - 1)
                pq.push({matrixInput[i][j], {i, j}});
        }
    }
}

/**
 * @brief Решает задачу о объеме воды.
 * @return Объем воды, который можно собрать.
 */
ll WaterVolumeSolver::solve() {
    ll ans = 0;
    while (!pq.empty()) {
        auto x = pq.top();
        pq.pop();
        sumWater = 0;
        int i, j, val;
        val = x.first;
        i = x.second.first;
        j = x.second.second;
        if (!matrixVisited[i][j]) {
            DepthFirstSearch(i, j, val);
        }
        ans += sumWater;
    }
    return ans;
}

/**
 * @brief Проверяет, является ли клетка с координатами (x, y) допустимой для посещения.
 * @param x Координата x клетки.
 * @param y Координата y клетки.
 * @param L Высота текущей клетки.
 * @return true, если клетка допустима, иначе false.
 */
bool WaterVolumeSolver::valid(int x, int y, int L) {
    if (x >= 0 && x < rowsMatrix && y >= 0 && y < colsMatrix && !matrixVisited[x][y] && matrixInput[x][y] <= L)
        return true;
    else
        return false;
}


/**
 * @brief Выполняет поиск в глубину для сбора воды.
 * @param ux Координата x текущей клетки.
 * @param uy Координата y текущей клетки.
 * @param L Высота текущей клетки.
 */
void WaterVolumeSolver::DepthFirstSearch(int ux, int uy, int L) {
    matrixVisited[ux][uy] = true;

    for (int i = 0; i < 4; i++) {
        int vx = ux + fx[i];
        int vy = uy + fy[i];
        if (valid(vx, vy, L)) {
            sumWater += (ll)(L - matrixInput[vx][vy]);
            matrixOutput[vx][vy] = L;
            DepthFirstSearch(vx, vy, L);
        } else if (vx >= 0 && vx < rowsMatrix && vy >= 0 && vy < colsMatrix && matrixInput[vx][vy] > L && !matrixVisited[vx][vy]) {
            pq.push({matrixInput[vx][vy], {vx, vy}});

        }
    }
}

vector<vector<int>> WaterVolumeSolver::getWorkingMatrix() const {
    return matrixOutput;
}

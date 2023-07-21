#include "solverthread.h"

SolverThread::SolverThread(int rows, int cols, const vector<vector<int>>& matrix)
    : rows(rows), cols(cols), matrix(matrix)
{
}

void SolverThread::run() {
    // Создаем объект класса WaterVolumeSolver для выполнения вычислений
    WaterVolumeSolver solver(rows, cols, matrix);

    // Вычисляем результат
    ll result = solver.solve();

    // Получаем матрицу с промежуточными данными после вычислений
    vector<vector<int>> workingMatrix = solver.getWorkingMatrix();

    // Отправляем сигнал с результатом и матрицей в основной поток
    emit calculationComplete(result, workingMatrix);
}

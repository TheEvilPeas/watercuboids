#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "watervolumesolver.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QGridLayout>
#include <QMessageBox>
#include <QIntValidator>
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <vector>
#include <queue>
#include <QGraphicsProxyWidget>
#include <iostream>

using namespace std;

/**
 * @brief Класс MainWindow представляет главное окно приложения.
 */
class MainWindow : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса MainWindow.
     * @param parent Родительский виджет (по умолчанию nullptr).
     */
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    /**
     * @brief Обработчик события нажатия кнопки ввода (ручной или рандом).
     */
    void handleInputButtonClicked();
    void handleRandomButtonClicked();

    /**
     * @brief Обработчик события нажатия кнопки решения.
     */
    void handleSolveButtonClicked();
    void handleCalculationComplete(ll result, const vector<vector<int>>& workingMatrix);

protected:
    /**
     * @brief Обработчик события прокрутки колеса мыши.
     * @param event Событие прокрутки колеса мыши.
     */
    void wheelEvent(QWheelEvent *event) override;

private:
    /**
     * @brief Создает виджеты для ввода данных.
     */
    void createInputWidgets();

    /**
     * @brief Создает кнопки для управления приложением.
     */
    void createButtonWidgets();

    /**
     * @brief Создает графическое представление и сцену для матрицы.
     */
    void createGraphicsView();

    /**
     * @brief Создает виджеты для отображения результата.
     */
    void createResultWidgets();

    /**
     * @brief Создает элементы матрицы и размещает их на сцене.
     * @param rows Количество строк в матрице.
     * @param cols Количество столбцов в матрице.
     * @param randomFill Флаг, указывающий, нужно ли заполнить матрицу случайными значениями.
     */
    void createMatrixItems(int rows, int cols, bool randomFill = false);

    QVBoxLayout *mainLayout; /**< Основной вертикальный макет окна. */
    QHBoxLayout *inputLayout; /**< Горизонтальный макет для ввода размеров матрицы. */
    QLabel *rowsLabel; /**< Метка для отображения текста "Количество строк". */
    QLineEdit *rowsInput; /**< Поле ввода для количества строк. */
    QLabel *colsLabel; /**< Метка для отображения текста "Количество столбцов". */
    QLineEdit *colsInput; /**< Поле ввода для количества столбцов. */
    QPushButton *inputButton; /**< Кнопка для ручного ввода матрицы. */
    QPushButton *randomButton; /**< Кнопка для рандомного ввода матрицы. */
    QPushButton *solveButton; /**< Кнопка для решения задачи. */
    QLabel *resultLabel; /**< Метка для отображения текста "Результат". */
    QLineEdit *resultLineEdit; /**< Поле для отображения результата. */
    QWidget *matrixWidget; /**< Виджет для отображения матрицы. */
    QScrollArea *scrollArea; /**< Область прокрутки для матрицы. */
    QGridLayout *matrixLayout; /**< Макет для размещения элементов матрицы. */
    QGraphicsScene *graphicsScene; /**< Графическая сцена для отображения матрицы. */
    QGraphicsView *graphicsView; /**< Представление для графической сцены. */
    vector<QGraphicsTextItem*> textItems; /**< Вектор элементов для хранения текстовых элементов матрицы. */
};

#endif // MAINWINDOW_H

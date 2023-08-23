#include "mainwindow.h"
#include "watervolumesolver.h"
#include "solverthread.h"

/**
 * @brief Конструктор класса MainWindow.
 * @param parent Родительский виджет.
 */
MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setMinimumSize(500, 500);

    mainLayout = new QVBoxLayout(this);

    // Создание элементов интерфейса
    createInputWidgets();
    createButtonWidgets();
    createGraphicsView();
    createResultWidgets();

    // Соединяем сигналы со слотами
    connect(inputButton, &QPushButton::clicked, this, &MainWindow::handleInputButtonClicked);
    connect(randomButton, &QPushButton::clicked, this, &MainWindow::handleRandomButtonClicked);
    connect(solveButton, &QPushButton::clicked, this, &MainWindow::handleSolveButtonClicked);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::handleSaveButtonClicked);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::handleLoadButtonClicked);
}

/**
 * @brief Создает виджеты для ввода данных.
 */
void MainWindow::createInputWidgets() {
    inputLayout = new QHBoxLayout;
    rowsLabel = new QLabel("Кол-во строк:");
    rowsInput = new QLineEdit;
    // Валидатор ввода для строк (от 1 до 999)
    rowsInput->setValidator(new QRegularExpressionValidator(QRegularExpression("^(?!0$)(?!1000$)\\d{1,3}$"), this));
    colsLabel = new QLabel("Кол-во столбцов:");
    colsInput = new QLineEdit;
    // Валидатор ввода для столбцов (от 1 до 999)
    colsInput->setValidator(new QRegularExpressionValidator(QRegularExpression("^(?!0$)(?!1000$)\\d{1,3}$"), this));

    inputLayout->addWidget(rowsLabel);
    inputLayout->addWidget(rowsInput);
    inputLayout->addWidget(colsLabel);
    inputLayout->addWidget(colsInput);
    mainLayout->addLayout(inputLayout);
}

/**
 * @brief Создает кнопки для управления приложением.
 */
void MainWindow::createButtonWidgets() {
    inputButton = new QPushButton("Ввод");
    randomButton = new QPushButton("Рандом");
    solveButton = new QPushButton("Решить");
    loadButton = new QPushButton("Загрузить");
    solveButton->setEnabled(false);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(inputButton);
    buttonLayout->addWidget(randomButton);
    buttonLayout->addWidget(loadButton);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(solveButton);
}

/**
 * @brief Создает графическое представление и сцену для матрицы.
 */
void MainWindow::createGraphicsView() {
    graphicsScene = new QGraphicsScene;
    graphicsView = new QGraphicsView(graphicsScene);
    graphicsView->setRenderHint(QPainter::Antialiasing);
    graphicsView->setInteractive(true);
    graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    graphicsView->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainLayout->addWidget(graphicsView);
}

/**
 * @brief Создает виджеты для отображения результата.
 */
void MainWindow::createResultWidgets() {
    resultLabel = new QLabel("Результат:");
    resultLineEdit = new QLineEdit;
    resultLineEdit->setFixedWidth(100);
    resultLineEdit->setReadOnly(true);

    QHBoxLayout *resultLayout = new QHBoxLayout;
    resultLayout->addWidget(resultLabel);
    resultLayout->addWidget(resultLineEdit);
    resultLayout->addStretch();
    saveButton = new QPushButton("Сохранить");
    resultLayout->addWidget(saveButton);

    mainLayout->addLayout(resultLayout);


}

/**
 * @brief Создает элементы матрицы и размещает их на сцене.
 * @param rows Количество строк в матрице.
 * @param cols Количество столбцов в матрице.
 * @param randomFill Флаг, указывающий, нужно ли заполнить матрицу случайными значениями.
 */
void MainWindow::createMatrixItems(int rows, int cols, bool randomFill) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QGraphicsRectItem *matrixItem = new QGraphicsRectItem;
            QBrush greenBrush(Qt::green);
            matrixItem->setRect(j * 50, i * 50, 50, 50);
            matrixItem->setBrush(greenBrush);
            matrixItem->setAcceptHoverEvents(true);
            matrixItem->setData(0, "");
            graphicsScene->addItem(matrixItem);

            QGraphicsTextItem *textItem = new QGraphicsTextItem;
            QString text = randomFill ? QString::number(QRandomGenerator::global()->bounded(0, 11)) : "";
            textItem->setPlainText(text);
            textItem->setPos(j * 50 + 15, i * 50 + 15);
            textItem->setTextWidth(25);
            textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            graphicsScene->addItem(textItem);
        }
    }
}

/**
 * @brief Обработчик события прокрутки колеса мыши.
 * @param event Событие прокрутки колеса мыши.
 */
void MainWindow::wheelEvent(QWheelEvent *event) {
    // Получаем состояние клавиши Ctrl
    bool ctrlPressed = event->modifiers().testFlag(Qt::ControlModifier);

    if (ctrlPressed) {
        // Масштабирование сцены
        int delta = event->angleDelta().y();
        double scaleFactor = qPow(2, delta / 240.0);

        if (scaleFactor != 1.0) {
            graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
            graphicsView->scale(scaleFactor, scaleFactor);
        }

        event->accept();
    } else {
        event->ignore();
    }
}

/**
 * @brief Обработчик нажатия на кнопку "Ввод".
 * Создает матрицу элементов на основе введенных пользователем данных.
 */
void MainWindow::handleInputButtonClicked() {
    int rows = rowsInput->text().toInt();
    int cols = colsInput->text().toInt();

    if (rows <= 0 || cols <= 0) {
        QMessageBox::warning(this, "Ошибка", "Кол-во строк и столбцов должно быть больше 0.");
        return;
    }

    // Очистить предыдущее содержимое сцены
    graphicsScene->clear();

    // Создание матрицы элементов
    createMatrixItems(rows, cols);

    solveButton->setEnabled(true);
}

/**
 * @brief Обработчик нажатия на кнопку "Рандом".
 * Создает матрицу элементов и заполняет ее случайными значениями.
 */
void MainWindow::handleRandomButtonClicked() {
    int rows = rowsInput->text().toInt();
    int cols = colsInput->text().toInt();

    if (rows <= 0 || cols <= 0) {
        QMessageBox::warning(this, "Ошибка", "Кол-во строк и столбцов должно быть больше 0.");
        return;
    }

    // Очистить предыдущее содержимое сцены
    graphicsScene->clear();

    // Создание матрицы элементов и заполнение случайными значениями
    createMatrixItems(rows, cols, true);

    solveButton->setEnabled(true);
}

/**
 * @brief Обработчик нажатия на кнопку "Решить".
 * Извлекает значения матрицы из графической сцены и запускает вычисления в рабочем потоке.
 */
void MainWindow::handleSolveButtonClicked() {
    int rows = rowsInput->text().toInt();
    int cols = colsInput->text().toInt();
    vector<vector<int>> matrix(rows, vector<int>(cols));

    // Получение значений матрицы из графической сцены
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QGraphicsTextItem *textItem = qgraphicsitem_cast<QGraphicsTextItem*>(graphicsScene->itemAt(j * 50 + 15, i * 50 + 15, QTransform()));
            QString text = textItem->toPlainText();
            matrix[i][j] = text.toInt();
        }
    }

    // Создаем объект рабочего потока и передаем ему матрицу
    SolverThread* solverThread = new SolverThread(rows, cols, matrix);
    // Соединяем сигнал завершения расчета из потока с соответствующим слотом в MainWindow
    connect(solverThread, &SolverThread::calculationComplete, this, &MainWindow::handleCalculationComplete);

    // Запускаем поток
    solverThread->start();
}

void MainWindow::handleSaveButtonClicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "BIN файлы (*.bin)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);

        if (file.open(QIODevice::WriteOnly)) {
            QDataStream out(&file);
            out << rowsInput->text().toInt();
            out << colsInput->text().toInt();

            for (int i = 0; i < rowsInput->text().toInt(); ++i) {
                for (int j = 0; j < colsInput->text().toInt(); ++j) {
                    QGraphicsTextItem *textItem = qgraphicsitem_cast<QGraphicsTextItem*>(graphicsScene->itemAt(j * 50 + 15, i * 50 + 15, QTransform()));
                    QString text = textItem->toPlainText();
                    out << text.toInt();
                }
            }

            file.close();
        }
    }
}

void MainWindow::handleLoadButtonClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Загрузить файл", "", "BIN файлы (*.bin)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);

        if (file.open(QIODevice::ReadOnly)) {
            QDataStream in(&file);
            int rows, cols;
            in >> rows;
            in >> cols;

            rowsInput->setText(QString::number(rows));
            colsInput->setText(QString::number(cols));

            graphicsScene->clear();

            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    int value;
                    in >> value;

                    QGraphicsRectItem *matrixItem = new QGraphicsRectItem;
                    QBrush greenBrush(Qt::green);
                    matrixItem->setRect(j * 50, i * 50, 50, 50);
                    matrixItem->setBrush(greenBrush);
                    matrixItem->setAcceptHoverEvents(true);
                    matrixItem->setData(0, "");
                    graphicsScene->addItem(matrixItem);

                    QGraphicsTextItem *textItem = new QGraphicsTextItem;
                    textItem->setPlainText(QString::number(value));
                    textItem->setPos(j * 50 + 15, i * 50 + 15);
                    textItem->setTextWidth(25);
                    textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
                    graphicsScene->addItem(textItem);
                }
            }

            file.close();
        }
    }
}

/**
 * @brief Обработчик завершения вычислений в рабочем потоке.
 * Обновляет текст в элементах QGraphicsTextItem на основе значений из рабочей матрицы.
 * @param result Результат вычислений.
 * @param workingMatrix Рабочая матрица с промежуточными значениями.
 */
void MainWindow::handleCalculationComplete(ll result, const vector<vector<int>>& workingMatrix) {
    // Обновляем текст в элементах QGraphicsTextItem на основе значений из рабочей матрицы
    int rows = workingMatrix.size();
    int cols = workingMatrix[0].size();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QGraphicsTextItem *textItem = qgraphicsitem_cast<QGraphicsTextItem*>(graphicsScene->itemAt(j * 50 + 15, i * 50 + 15, QTransform()));
            QString newText = QString::number(workingMatrix[i][j]);
            QString oldText = textItem->toPlainText();

            if (oldText != newText) {
                QString displayText = newText;
                textItem->setPlainText(displayText);

                // Окрасить клетку в синий
                QBrush blueBrush(Qt::blue);
                QGraphicsRectItem *matrixItem = qgraphicsitem_cast<QGraphicsRectItem*>(graphicsScene->itemAt(j * 50, i * 50, QTransform()));
                matrixItem->setBrush(blueBrush);
            } else {
                // Окрасить клетку в зеленый
                QBrush greenBrush(Qt::green);
                QGraphicsRectItem *matrixItem = qgraphicsitem_cast<QGraphicsRectItem*>(graphicsScene->itemAt(j * 50, i * 50, QTransform()));
                matrixItem->setBrush(greenBrush);
            }
        }
    }

    // Установить результат в LineEdit
    resultLineEdit->setText(QString::number(result));
}

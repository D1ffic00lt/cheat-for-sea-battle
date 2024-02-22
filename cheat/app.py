from PyQt5.QtCore import pyqtSignal
from PyQt5.QtWidgets import (
    QMainWindow, QWidget, QVBoxLayout,
    QHBoxLayout, QPushButton, QLabel,
    QGridLayout, QSpinBox
)

from gamecalculator import calculator


class Cell(QWidget):
    clicked = pyqtSignal(int, int)

    def __init__(self, row, col, parent=None):
        super(Cell, self).__init__(parent)
        self.row = row
        self.col = col
        self.code = 0
        self.number = 0
        self.setFixedSize(50, 50)
        self.number_label = QLabel('0')
        self.layout = QVBoxLayout()
        self.layout.addWidget(self.number_label)
        self.setLayout(self.layout)
        self.is_blocked = False
        self.is_marked = False
        self.is_killed = False

    def mousePressEvent(self, event):
        if not self.is_blocked:
            self.clicked.emit(self.row, self.col)

    def update_style(self, max_prob: int = 0):
        style = ""

        if max_prob == self.number:
            style += "background-color: red;"
        elif self.code == 0:
            style += "background-color: gray;"
        elif self.code == 1:
            style += "background-color: purple"
        elif self.code == 2:
            style += "background-color: green;"
        else:
            style += "background-color: blue;"
        self.setStyleSheet(style)


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()

        self.probs = []
        self.calculator = calculator.PyCalculator()
        self.setWindowTitle("My Application")
        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)
        self.layout = QHBoxLayout(self.centralWidget())

        self.left_layout = QGridLayout()
        self.cells = []
        for i in range(10):
            row = []
            for j in range(10):
                cell = Cell(i, j)
                cell.clicked.connect(self.handle_cell_clicked)
                row.append(cell)
                self.left_layout.addWidget(cell, i, j)
            self.cells.append(row)
        left_widget = QWidget()
        left_widget.setLayout(self.left_layout)

        self.right_layout = QVBoxLayout()
        self.objects = []
        self.object_spinboxes = []
        objects_data = [("Однопалубные", 0), ("Двухпалубные", 3), ("Трёхпалубные", 2), ("Четырёхпалубные", 1)]
        for name, count in objects_data:
            obj = Object(name, count)
            self.objects.append(obj)
            self.right_layout.addWidget(obj)
            spinbox = QSpinBox()
            spinbox.setMinimum(0)
            spinbox.setMaximum(100)
            spinbox.valueChanged.connect(self.handle_spinbox_value_changed)
            self.object_spinboxes.append(spinbox)
            self.right_layout.addWidget(spinbox)

        self.reset_button = QPushButton("Сброс")
        self.reset_button.clicked.connect(self.handle_reset_button_clicked)
        self.end_session_button = QPushButton("Завершить сессию")
        self.end_session_button.clicked.connect(self.handle_end_session_button_clicked)
        self.buttons_layout = QHBoxLayout()
        self.buttons_layout.addWidget(self.reset_button)
        self.buttons_layout.addWidget(self.end_session_button)

        self.layout.addWidget(left_widget)
        self.layout.addLayout(self.right_layout)
        self.layout.addLayout(self.buttons_layout)

        self.update_cells()

    def handle_reset_button_clicked(self):
        self.calculator = calculator.PyCalculator()
        self.update_cells()

        for i in range(len(self.cells)):
            for j in range(len(self.cells[i])):
                self.cells[i][j].code = 0
        self.update_styles()

    def handle_end_session_button_clicked(self):
        self.close()

    def get_probs(self):
        self.probs = self.calculator.calculate()

    def update_cells(self):
        self.get_probs()

        for i in range(len(self.cells)):
            for j in range(len(self.cells[i])):
                self.cells[i][j].number = int(self.probs[i][j])
                self.cells[i][j].number_label.setText(str(self.probs[i][j]))

        self.update_styles()

    def update_styles(self):
        self.get_probs()
        for i in range(len(self.cells)):
            for j in range(len(self.cells[i])):
                self.cells[i][j].update_style(int(max(map(max, self.probs))))

    def handle_cell_clicked(self, row, col):
        cell = self.cells[row][col]
        # 0 - status=True (gray); 1 - status=False (purple); 2 - ship (green); 3 - shooted (blue)
        cell.code = 0 if cell.code == 3 else cell.code + 1

        if cell.code == 0:
            self.calculator.set_status(col, row, True)
            self.calculator.set_shooted(col, row, False)
        elif cell.code == 1:
            self.calculator.set_status(col, row, False, clicked=True)
        elif cell.code == 2:
            self.calculator.set_status(col, row, False, clicked=True)
            self.calculator.set_ship(col, row, True)
        else:
            self.calculator.set_ship(col, row, False)
            self.calculator.set_shooted(col, row, True)
        self.update_cells()
        self.update_styles()

    def handle_spinbox_value_changed(self):
        single_decker_ships_count = 0
        double_decker_ships_count = 0
        three_decker_ships_count = 0
        four_decker_ships_count = 0

        for spinbox, obj in zip(self.object_spinboxes, self.objects):
            if obj.name_label.text() == "Однопалубные":
                single_decker_ships_count = int(spinbox.value())
            elif obj.name_label.text() == "Двухпалубные":
                double_decker_ships_count = int(spinbox.value())
            elif obj.name_label.text() == "Трёхпалубные":
                three_decker_ships_count = int(spinbox.value())
            elif obj.name_label.text() == "Четырёхпалубные":
                four_decker_ships_count = int(spinbox.value())
            obj.count_label.setText(str(spinbox.value()))
        self.calculator.set_single_decker_ship(single_decker_ships_count)
        self.calculator.set_double_decker_ship(double_decker_ships_count)
        self.calculator.set_three_decker_ship(three_decker_ships_count)
        self.calculator.set_four_decker_ship(four_decker_ships_count)
        self.update_cells()
        self.update_styles()


class Object(QWidget):
    def __init__(self, name, count, parent=None):
        super(Object, self).__init__(parent)
        self.name_label = QLabel(name)
        self.count_label = QLabel(str(count))
        self.layout = QVBoxLayout()
        self.layout.addWidget(self.name_label)
        self.layout.addWidget(self.count_label)
        self.setLayout(self.layout)

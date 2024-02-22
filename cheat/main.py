import sys

from PyQt5.QtWidgets import QApplication

from cheat.app import MainWindow

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())

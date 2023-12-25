

class Field(object):
    def __init__(self, status=True, shoot=False, ship=False):
        self.status = status
        self.shoot = shoot
        self.ship = ship

    def __str__(self):
        return self.__repr__()

    def __repr__(self):
        return f"{self.__class__.__name__}({self.status}, {self.shoot}, {self.ship})"
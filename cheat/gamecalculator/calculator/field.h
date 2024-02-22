#ifndef GAMECALCULATOR_FIELD_H
#define GAMECALCULATOR_FIELD_H


class Field {

public:
    bool ship, status, shooted, clicked = false;
    explicit Field(bool status = true, bool shooted = false, bool ship = false) {
        this->status = status;
        this->shooted = shooted;
        this->ship = ship;
    }
};

#endif //GAMECALCULATOR_FIELD_H

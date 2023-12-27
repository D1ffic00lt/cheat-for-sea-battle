#ifndef GAMECALCULATOR_FIELD_H
#define GAMECALCULATOR_FIELD_H


class Field {

public:
    bool ship, status, shooted;

    explicit Field(bool status = true, bool shooted = false, bool ship = false);
};

Field::Field(bool status, bool shooted, bool ship) {
    this->status = status;
    this->shooted = shooted;
    this->ship = ship;
}



#endif //GAMECALCULATOR_FIELD_H

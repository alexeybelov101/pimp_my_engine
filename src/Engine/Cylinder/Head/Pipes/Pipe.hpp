#pragma once
#include <vector>

class Pipe {
    public:
        // Свойства
        int id;
        double length;
        double radius;
        double pressure;
        std::vector<Pipe*> parents;
        std::vector<Pipe*> children;

        // Конструкторы
        Pipe(int id = 0);
        Pipe(int id, double length, double radius, double pressure);
        ~Pipe();

        // Методы доступа
        size_t getParentCount() const;
        size_t getChildCount() const;
        bool hasParent(Pipe* parent) const;
        bool hasChild(Pipe* child) const;

        // Распространение давления
        void propagateForward(double inputPressure);
        void propagateBackward(double inputPressure);

        // Полный цикл: один forward + один backward
        void fire(double chargePressure);

        // Расчет падения давления на трубе
        double calculatePressureDrop(double flowRate) const;
};

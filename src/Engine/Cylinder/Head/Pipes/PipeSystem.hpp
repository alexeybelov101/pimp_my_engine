#pragma once
#include "Pipe.hpp"
#include <vector>
#include <unordered_map>

class PipeSystem {
private:
    std::unordered_map<int, Pipe*> pipes;
    std::vector<int> inletIds;
    std::vector<int> outletIds;

public:
    PipeSystem();
    ~PipeSystem();

    // Создание труб
    PipeSystem& addPipe(int id);
    PipeSystem& addPipe(int id, double length, double radius, double pressure);

    // Соединение
    PipeSystem& connect(int parentId, int childId);
    PipeSystem& disconnect(int parentId, int childId);

    // Настройка впусков/выпусков
    PipeSystem& setInlet(int id);
    PipeSystem& setOutlet(int id);
    PipeSystem& clearInlets();
    PipeSystem& clearOutlets();

    // Получение данных
    Pipe* getPipe(int id) const;
    std::vector<Pipe*> getInlets() const;
    std::vector<Pipe*> getOutlets() const;
    std::vector<Pipe*> getAllPipes() const;
    const std::unordered_map<int, Pipe*>& getPipesMap() const;

    // Очистка
    void clear();
    void reset();

    // Проверка структуры
    bool pipeExists(int id) const;
    bool isInlet(int id) const;
    bool isOutlet(int id) const;
    bool isBranchPoint(int id) const;
    bool isMergePoint(int id) const;
    size_t getPipeCount() const;
};

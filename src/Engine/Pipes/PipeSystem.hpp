#pragma once
#include <memory>
#include <vector>

class Atmosphere;
class Pipe;
class IJunction;

class PipeSystem {
public:
    PipeSystem(
        std::unique_ptr<Atmosphere> atmosphere,
        std::vector<std::unique_ptr<Pipe>> pipes,
        std::vector<std::unique_ptr<IJunction>> junctions
    );

    PipeSystem(PipeSystem&&) noexcept;
    PipeSystem& operator=(PipeSystem&&) noexcept;

    PipeSystem(const PipeSystem&) = delete;
    PipeSystem& operator=(const PipeSystem&) = delete;

    ~PipeSystem();

    void step(double dt);

    const Atmosphere& atmosphere() const { return *atmosphere_; }
    const std::vector<std::unique_ptr<Pipe>>& pipes() const { return pipes_; }
    const std::vector<std::unique_ptr<IJunction>>& junctions() const { return junctions_; }

private:
    std::unique_ptr<Atmosphere> atmosphere_;
    std::vector<std::unique_ptr<Pipe>> pipes_;
    std::vector<std::unique_ptr<IJunction>> junctions_;
};

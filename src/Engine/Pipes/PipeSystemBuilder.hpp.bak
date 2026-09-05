#pragma once
#include <nlohmann/json_fwd.hpp>

class Pipe;
class PipeSystem;

class PipeSystemBuilder {
public:
    static PipeSystem build(const nlohmann::json& config);
private:
    static std::vector<Pipe> createPipes(const nlohmann::json& config);
    static void appendChildPipe(Pipe& parentPipe, Pipe* childPipe);
};

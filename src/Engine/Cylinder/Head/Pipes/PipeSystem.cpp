#include "PipeSystem.hpp"
#include <stdexcept>
#include <algorithm>

PipeSystem::PipeSystem() {}

PipeSystem::~PipeSystem() {
    clear();
}

PipeSystem& PipeSystem::addPipe(int id) {
    if (pipes.find(id) != pipes.end()) {
        throw std::runtime_error("Pipe with this id already exists");
    }
    pipes[id] = new Pipe(id);
    return *this;
}

PipeSystem& PipeSystem::addPipe(int id, double length, double radius, double pressure) {
    if (pipes.find(id) != pipes.end()) {
        throw std::runtime_error("Pipe with this id already exists");
    }
    pipes[id] = new Pipe(id, length, radius, pressure);
    return *this;
}

PipeSystem& PipeSystem::connect(int parentId, int childId) {
    auto parentIt = pipes.find(parentId);
    auto childIt = pipes.find(childId);

    if (parentIt == pipes.end() || childIt == pipes.end()) {
        throw std::runtime_error("Pipe not found");
    }

    Pipe* parent = parentIt->second;
    Pipe* child = childIt->second;

    if (!parent->hasChild(child)) {
        parent->children.push_back(child);
    }
    if (!child->hasParent(parent)) {
        child->parents.push_back(parent);
    }

    return *this;
}

PipeSystem& PipeSystem::disconnect(int parentId, int childId) {
    auto parentIt = pipes.find(parentId);
    auto childIt = pipes.find(childId);

    if (parentIt == pipes.end() || childIt == pipes.end()) {
        throw std::runtime_error("Pipe not found");
    }

    Pipe* parent = parentIt->second;
    Pipe* child = childIt->second;

    parent->children.erase(
        std::remove(parent->children.begin(), parent->children.end(), child),
        parent->children.end()
    );

    child->parents.erase(
        std::remove(child->parents.begin(), child->parents.end(), parent),
        child->parents.end()
    );

    return *this;
}

PipeSystem& PipeSystem::setInlet(int id) {
    if (pipes.find(id) == pipes.end()) {
        throw std::runtime_error("Pipe not found");
    }
    if (std::find(inletIds.begin(), inletIds.end(), id) == inletIds.end()) {
        inletIds.push_back(id);
    }
    return *this;
}

PipeSystem& PipeSystem::setOutlet(int id) {
    if (pipes.find(id) == pipes.end()) {
        throw std::runtime_error("Pipe not found");
    }
    if (std::find(outletIds.begin(), outletIds.end(), id) == outletIds.end()) {
        outletIds.push_back(id);
    }
    return *this;
}

PipeSystem& PipeSystem::clearInlets() {
    inletIds.clear();
    return *this;
}

PipeSystem& PipeSystem::clearOutlets() {
    outletIds.clear();
    return *this;
}

Pipe* PipeSystem::getPipe(int id) const {
    auto it = pipes.find(id);
    return (it != pipes.end()) ? it->second : nullptr;
}

std::vector<Pipe*> PipeSystem::getInlets() const {
    std::vector<Pipe*> inlets;
    for (int id : inletIds) {
        auto it = pipes.find(id);
        if (it != pipes.end()) {
            inlets.push_back(it->second);
        }
    }
    return inlets;
}

std::vector<Pipe*> PipeSystem::getOutlets() const {
    std::vector<Pipe*> outlets;
    for (int id : outletIds) {
        auto it = pipes.find(id);
        if (it != pipes.end()) {
            outlets.push_back(it->second);
        }
    }
    return outlets;
}

std::vector<Pipe*> PipeSystem::getAllPipes() const {
    std::vector<Pipe*> result;
    result.reserve(pipes.size());
    for (const auto& pair : pipes) {
        result.push_back(pair.second);
    }
    return result;
}

const std::unordered_map<int, Pipe*>& PipeSystem::getPipesMap() const {
    return pipes;
}

void PipeSystem::clear() {
    for (auto& pair : pipes) {
        delete pair.second;
    }
    pipes.clear();
    inletIds.clear();
    outletIds.clear();
}

void PipeSystem::reset() {
    clear();
}

bool PipeSystem::pipeExists(int id) const {
    return pipes.find(id) != pipes.end();
}

bool PipeSystem::isInlet(int id) const {
    return std::find(inletIds.begin(), inletIds.end(), id) != inletIds.end();
}

bool PipeSystem::isOutlet(int id) const {
    return std::find(outletIds.begin(), outletIds.end(), id) != outletIds.end();
}

bool PipeSystem::isBranchPoint(int id) const {
    Pipe* pipe = getPipe(id);
    if (!pipe) return false;
    return pipe->children.size() > 1;
}

bool PipeSystem::isMergePoint(int id) const {
    Pipe* pipe = getPipe(id);
    if (!pipe) return false;
    return pipe->parents.size() > 1;
}

size_t PipeSystem::getPipeCount() const {
    return pipes.size();
}

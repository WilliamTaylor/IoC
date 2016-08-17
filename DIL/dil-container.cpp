#include "dil-container.h"

dil::container::container()
    : state(Unlocked)
{
}

dil::container::container(dil::container&& container)
    : state(Unlocked)
{
    for(auto& e : container.mappings)
    {
        this->mappings[e.first] = move(e.second);
    }

    container.state = Locked;
    container.mappings.clear();
}

dil::container::~container()
{
    using container_pair = std::pair<size_t, std::unique_ptr<entry>>;
    std::vector<container_pair> entries;
    
    for (auto& e : mappings) 
    {
        entries.push_back(container_pair(e.first, move(e.second)));
    }

    sort(entries.begin(), entries.end(), [&](container_pair& a, container_pair& b)
    {
        return a.second->getTimeRegisted() < b.second->getTimeRegisted();
    });

    mappings.clear();
    entries.clear();
}

void dil::container::unlock()
{
    state = Unlocked;
}

void dil::container::lock()
{
    state = Locked;
}

size_t dil::container::size() const
{
    return mappings.size();
}

size_t dil::container::hash(const std::string& v) const
{
    return std::hash<std::string>()(v);
}

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

void dil::container::unlock()
{
    state = Unlocked;
}

void dil::container::lock()
{
    state = Locked;
}

dil::container::~container()
{
    using pair = std::pair<size_t, std::unique_ptr<dil::entry>>;

    std::vector<pair> entries;
    for(auto& e : mappings) {
        entries.push_back(pair(e.first, move(e.second)));
    }

    sort(entries.begin(), entries.end(), [](pair& a, pair& b) {
        return a.second->getID() < b.second->getID();
    });

    mappings.clear();
    entries.clear();
}

size_t dil::container::size() const
{
    return mappings.size();
}

size_t dil::container::hash(const std::string& v) const
{
    return std::hash<std::string>()(v);
}

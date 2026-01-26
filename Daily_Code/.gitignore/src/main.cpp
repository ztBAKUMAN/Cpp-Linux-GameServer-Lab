#include "Monster.h"
#include <memory>
#include <vector>

int main()
{
    std::vector<std::unique_ptr<Monster>> monsterGroup;
    std::unique_ptr<Monster> goblin = std::make_unique<Goblin>("goblin");
    std::unique_ptr<Monster> boss   = std::make_unique<Boss>("boss");
    monsterGroup.push_back(std::move(goblin));
    monsterGroup.push_back(std::move(boss));

    for(const auto& it : monsterGroup)
    {
        it->attack();
    }
    return 0;
}
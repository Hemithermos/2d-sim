#include "SystemManager.h"
void removeEntity(std::vector<Entity>& v, Entity e)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i] == e)
        {
            v[i] = v.back();
            v.pop_back();
            return;
        }
    }
}


void SystemManager::entityDestroyed(Entity entity)
{
    // erase the destroyed entity from the listOfEntities of each system
    // iterate over a map so we get a {typename, System} pair
    for (auto const &pair : systems)
    {
        auto const &system = pair.second;
        removeEntity(system->listOfEntities, entity);
    }
}

void SystemManager::entitySignatureChanged(Entity entity, Signature signature)
{
    // notify the systems that the signature changed
    // iterate over a map so we get a {typename, System} pair
    for (auto const &pair : systems)
    {
        auto const &type = pair.first;
        auto const &system = pair.second;
        auto const &systemSignature = signatures[type];

        // if the entity signature matches at least the system signature
        // we insert the entity to the system
        // this way we dont exclude entities that have extra components

        // for this we use the bitwise and between the two signatures
        if ((systemSignature & signature) == systemSignature)
        {
            system->listOfEntities.push_back(entity);
        }
        // if it doesnt match we erase the entity from the system
        else
        {
            removeEntity(system->listOfEntities, entity);
        }
    }
}


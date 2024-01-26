#pragma once

// Includes
//------------------------------------------------------------------------------
// Game
#include "Group.h"

// Third party
#include <SFML/Graphics.hpp>

//------------------------------------------------------------------------------
class GameObject : public sf::Drawable, public sf::Transformable
{
public:
    virtual ~GameObject() = default;
    virtual sf::FloatRect GetGlobalBounds() const = 0;
    virtual sf::FloatRect GetHitbox() const = 0;
    virtual void Update(const sf::Time& timeslice) = 0;

    void AddToGroup(Group* group);
    void RemoveFromGroup(Group* group);
    void Kill();   
    void SyncGameObjectChanges();
    bool IsKilled() { return mIsKilled; }

private:
    std::unordered_set<Group*> mGroups;
    bool mIsKilled = false;
};
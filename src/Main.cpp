// Includes
//------------------------------------------------------------------------------
// Third party
#include <SFML/Graphics.hpp>

// Core
#include "Core/GameObjectManager.h"
#include "Core/Resources.h"
#include "Core/RectUtils.h"
#include "Core/RandomUtils.h"

//------------------------------------------------------------------------------
constexpr uint32_t WINDOW_WIDTH = 800;
constexpr uint32_t WINDOW_HEIGHT = 600;

//------------------------------------------------------------------------------
namespace Resources
{    
    constexpr char SFMLLogo[] = "1200px-SFML2.png";
}

//------------------------------------------------------------------------------
class SMFLLogo : public GameObject
{
public:
    SMFLLogo(const sf::Vector2f& position)
        : mSprite(LoadTexture(Resources::SFMLLogo))
        , mSpeed(200.0f)
    {
        mSprite.setOrigin(GetRectCenter(mSprite.getLocalBounds()));
        mSprite.scale({ 0.25f, 0.25f });
        setPosition(position);
        mHitbox = GetGlobalBounds();

        float dirX = GetRandomIntegerFromList({ -1.0f, 1.0f });
        float dirY = GetRandomIntegerFromList({ -1.0f, 1.0f });
        mDirection = { dirX, dirY };
    }

    virtual sf::FloatRect GetGlobalBounds() const override
    {
        return getTransform().transformRect(mSprite.getGlobalBounds());
    }

    virtual sf::FloatRect GetHitbox() const override
    {
        return mHitbox;
    }

    virtual void Update(const sf::Time& timeslice) override
    {
        sf::Vector2f delta = mDirection * mSpeed * timeslice.asSeconds();
        mHitbox.left += delta.x;
        mHitbox.top += delta.y;

        if (mHitbox.left < 0)
        {
            mDirection.x = -mDirection.x;
        }
        else if (mHitbox.left + mHitbox.width > WINDOW_WIDTH)
        {
            mDirection.x = -mDirection.x;
        }
        else if (mHitbox.top < 0)
        {
            mDirection.y = -mDirection.y;
        }
        else if (mHitbox.top + mHitbox.height > WINDOW_HEIGHT)
        {
            mDirection.y = -mDirection.y;
        }

        sf::Vector2f center = GetRectCenter(mHitbox);
        setPosition({ center.x, center.y });
    }

    virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override
    {
        sf::RenderStates statesCopy(states);
        statesCopy.transform *= getTransform();
        target.draw(mSprite, statesCopy);
    }

private:
    sf::Sprite mSprite;
    sf::FloatRect mHitbox;
    sf::Vector2f mDirection;
    float mSpeed;
};

//------------------------------------------------------------------------------
int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "SFML Template Project");
    window.setVerticalSyncEnabled(true);

    sf::Clock clock;
    const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    GameObjectManager& manager = GameObjectManager::Instance();
    Group allSprites;

    SMFLLogo* logo = manager.CreateGameObject<SMFLLogo>(sf::Vector2f(window.getSize()) / 2.0f);
    logo->AddToGroup(&allSprites);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate >= timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            for (GameObject* obj : allSprites)
            {                
                obj->Update(timePerFrame);                
            }
            manager.SyncGameObjectChanges();
        }

        window.clear();
        for (const GameObject* obj : allSprites)
        {
            window.draw(*obj);
        }        
        window.display();
    }

    return 0;
}
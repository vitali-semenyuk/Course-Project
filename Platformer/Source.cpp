#include "Global.h"
#include "Player.h"
#include "Enemy.h"
#include "AnimationManager.h"
#include "Entity.h"
#include "Bullet.h"
#include "Level.h"

#include <list>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(600, 400), "Test");

    View view(FloatRect(0, 0, 600, 400));

    Texture texture;
    texture.loadFromFile("res/fang.png");

    AnimationManager animationManager;
    animationManager.create("walk", texture, 0, 244, 40, 50, 6, 0.005, 40);
    animationManager.create("jump", texture, 0, 528, 29, 30, 4, 0.005, 38);
    animationManager.create("duck", texture, 0, 436, 80, 20, 1, 0.005, 0);
    animationManager.create("stay", texture, 0, 187, 42, 52, 3, 0.002, 42);
    animationManager.create("shoot", texture, 0, 572, 45, 52, 5, 0.005, 45);
    animationManager.set("stay");

    Texture bulletTexture;
    bulletTexture.loadFromFile("res/bullet.png");

    AnimationManager bulletAnimation;
    bulletAnimation.create("move", bulletTexture, 7, 10, 8, 8, 1, 0, 0);
    bulletAnimation.create("explode", bulletTexture, 27, 7, 18, 18, 4, 0.01, 29);
    
    std::list<Entity*> entities;

    Level level;
    level.loadFromFile("res/level.tmx");

    std::vector<Object> enemies = level.getObjects("enemy");
    for (size_t i = 0; i < enemies.size(); ++i) {
        entities.push_back(new Enemy(animationManager, enemies[i].rect.left, enemies[i].rect.top));
    }

    Object playerObject = level.getObject("player");
    Player player(animationManager, playerObject.rect.left, playerObject.rect.top, level);

     
    Clock clock;
    double time;
    
    while (window.isOpen()) {
        Event event;

        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 800;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Space) {
                    entities.push_back(new Bullet(bulletAnimation, player.x, player.y + 10/**/, player.direction));
                }
            }
        }

        
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            player.keys[Player::Key::Left] = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            player.keys[Player::Key::Right] = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            player.keys[Player::Key::Up] = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            player.keys[Player::Key::Down] = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            player.keys[Player::Key::Space] = true;
        }

        animationManager.tick(time);

        player.update(time);

        for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); ) {
            Entity *bullet = *it;

            if (!bullet->isAlive) {
                it = entities.erase(it);
                delete bullet;
            }
            else {
                it++;
            }
        }

        for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
            (*it)->update(time);
        }

        for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
            if ((*it)->name == "Enemy") {
                Entity *enemy = *it;
                if (!enemy->isAlive) {
                    continue;
                }
                if (player.getRect().intersects(enemy->getRect())) {
                    if (player.dy > 0) {
                        enemy->dx = 0;
                        player.dy = -0.2;
                        enemy->isAlive = false;
                    }
                    else {
                        // kill player
                    }
                }

                for (std::list<Entity*>::iterator _it = entities.begin(); _it != entities.end(); ++_it) {
                    if ((*_it)->name == "Bullet") {
                        Entity *bullet = *_it;
                        if (bullet->isAlive) {
                            if (bullet->getRect().intersects(enemy->getRect())) {
                                bullet->isAlive = false;
                                enemy->isAlive = false;
                            }
                        }
                    }
                }
            }
        }
            
        window.clear(Color::White);

        view.setCenter(player.x, player.y);
        window.setView(view);

        level.draw(window);

        for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
            (*it)->draw(window);
        }

        player.draw(window);

        window.display();
    }

    return 0;
}

#include "Application.h"

int Application::onExecute()
{
    if (!onInit()) {
        return -1;
    }

    stateManager.changeState(IntroState::getInstance(&stateManager, 15));
    //stateManager.changeState(PlayState::getInstance(&stateManager));

    while (window.isOpen()) {
        sf::Event event;       

        while (window.pollEvent(event)) {            
            stateManager.onEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        stateManager.onLoop();

        window.clear(sf::Color::White);

        stateManager.onRender(window);

        window.display();
    }

    onCleanup();

    return 0;
}

bool Application::onInit()
{
    std::locale::global(std::locale("Russian_Russia"));
    unsigned int style;
    if (stateManager.settings.isFullscreen())
        style = sf::Style::Fullscreen;
    else
        style = sf::Style::Close;
    window.create(sf::VideoMode(stateManager.settings.getResolution().x, stateManager.settings.getResolution().y), APPLICATION_TITLE, style);
    window.setFramerateLimit(60);
    //window.setVerticalSyncEnabled(true);

    return true;
}

void Application::onCleanup()
{
    
}

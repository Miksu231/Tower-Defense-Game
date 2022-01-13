#ifndef MAIN_MENU
#define MAIN_MENU

class MainMenu {
public:
    int Run() {

        sf::RenderWindow window(sf::VideoMode(1175, 975), "Tower Defense Game");
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(10);

        sf::Texture background_image;
        background_image.loadFromFile("menu_background.png");

        sf::Sprite BG_sprite;
        BG_sprite.setTexture(background_image);
        BG_sprite.setPosition(0, 0);
    
        sf::Font font;
        if(!font.loadFromFile("Outfit-Light.ttf")) {
            //Throw error
        }

        auto dark_blue = sf::Color(19,19,244);
        auto light_blue = sf::Color(19,132,244);

        sf::Text title;
        title.setFont(font);
        title.setStyle(sf::Text::Bold);
        title.setString("Tower defense");
        title.setFillColor(sf::Color::Black);
        title.setCharacterSize(110);
        title.setPosition(200, 120);

        sf::RectangleShape play_background;
        play_background.setSize(sf::Vector2f(400, 120));
        play_background.setFillColor(light_blue);
        play_background.setOutlineColor(dark_blue);
        play_background.setOutlineThickness(5);
        play_background.setPosition(387, 340);

        sf::Text play;
        play.setFont(font);
        play.setStyle(sf::Text::Bold);
        play.setString("Play");
        play.setFillColor(sf::Color::White);
        play.setCharacterSize(80);
        play.setPosition(500, 345);


        sf::RectangleShape about_background;
        about_background.setSize(sf::Vector2f(400, 120));
        about_background.setFillColor(light_blue);
        about_background.setOutlineColor(dark_blue);
        about_background.setOutlineThickness(5);
        about_background.setPosition(387, 490);

        sf::Text about;
        about.setFont(font);
        about.setStyle(sf::Text::Bold);
        about.setString("About");
        about.setFillColor(sf::Color::White);
        about.setCharacterSize(80);
        about.setPosition(475, 500);


        sf::RectangleShape quit_background;
        quit_background.setSize(sf::Vector2f(400, 120));
        quit_background.setFillColor(light_blue);
        quit_background.setOutlineColor(dark_blue);
        quit_background.setOutlineThickness(5);
        quit_background.setPosition(387, 640);

        sf::Text quit;
        quit.setFont(font);
        quit.setStyle(sf::Text::Bold);
        quit.setString("Quit");
        quit.setFillColor(sf::Color::White);
        quit.setCharacterSize(80);
        quit.setPosition(500, 645);

        bool mouse_released = false;

        while (window.isOpen()){
            mouse_released = false;

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonReleased){
                    mouse_released = true;
                }
            }

            auto mouse_pos = sf::Mouse::getPosition(window);
            auto translated_pos = window.mapPixelToCoords(mouse_pos);    

            window.clear();
            window.draw(BG_sprite);
            window.draw(title);
            window.draw(play_background);
            window.draw(play);
            window.draw(about_background);
            window.draw(about);
            window.draw(quit_background);
            window.draw(quit);
            window.display();

            if(play_background.getGlobalBounds().contains(translated_pos) && mouse_released) {
                window.close();
                return 2;
            }
            if(about_background.getGlobalBounds().contains(translated_pos) && mouse_released) {
                window.close();
                return 8;
            }
            if(quit_background.getGlobalBounds().contains(translated_pos) && mouse_released) {
                window.close();
                return 0;
            }
        }
        return 0;
    }
};

#endif
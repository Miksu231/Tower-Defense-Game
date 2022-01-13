#ifndef MAP_MENU
#define MAP_MENU

class MapMenu {
public:
    int Run() {
        sf::RenderWindow window(sf::VideoMode(1175, 975), "Tower Defense Game");
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(10);

        auto dark_blue = sf::Color(19,19,244);
        auto light_blue = sf::Color(19,132,244);

        sf::Font font;
        if(!font.loadFromFile("Outfit-Light.ttf")) {
            //Throw error
        }
        std::vector<sf::RectangleShape> buttons;
        std::vector<sf::Text> texts;

        sf::Texture background_image;
        background_image.loadFromFile("menu_background.png");

        sf::Sprite BG_sprite;
        BG_sprite.setTexture(background_image);
        BG_sprite.setPosition(0, 0);

        //Map 1 button

        sf::RectangleShape map1_button;
        map1_button.setSize(sf::Vector2f(675, 100));
        map1_button.setFillColor(light_blue);
        map1_button.setOutlineColor(dark_blue);
        map1_button.setOutlineThickness(5);
        map1_button.setPosition(250, 150);
        buttons.push_back(map1_button);

        sf::Text map1;
        map1.setFont(font);
        map1.setStyle(sf::Text::Bold);
        map1.setString("Map 1");
        map1.setFillColor(sf::Color::White);
        map1.setCharacterSize(75);
        map1.setPosition(270, 145);
        texts.push_back(map1);

        //Map 2 button

        sf::RectangleShape map2_button;
        map2_button.setSize(sf::Vector2f(675, 100));
        map2_button.setFillColor(light_blue);
        map2_button.setOutlineColor(dark_blue);
        map2_button.setOutlineThickness(5);
        map2_button.setPosition(250, 270);
        buttons.push_back(map2_button);

        sf::Text map2;
        map2.setFont(font);
        map2.setStyle(sf::Text::Bold);
        map2.setString("Map 2");
        map2.setFillColor(sf::Color::White);
        map2.setCharacterSize(75);
        map2.setPosition(270, 265);
        texts.push_back(map2);

        //Map 3 button

        sf::RectangleShape map3_button;
        map3_button.setSize(sf::Vector2f(675, 100));
        map3_button.setFillColor(light_blue);
        map3_button.setOutlineColor(dark_blue);
        map3_button.setOutlineThickness(5);
        map3_button.setPosition(250, 390);
        buttons.push_back(map3_button);

        sf::Text map3;
        map3.setFont(font);
        map3.setStyle(sf::Text::Bold);
        map3.setString("Map 3");
        map3.setFillColor(sf::Color::White);
        map3.setCharacterSize(75);
        map3.setPosition(270, 385);
        texts.push_back(map3);

        //Map 4 button

        sf::RectangleShape map4_button;
        map4_button.setSize(sf::Vector2f(675, 100));
        map4_button.setFillColor(light_blue);
        map4_button.setOutlineColor(dark_blue);
        map4_button.setOutlineThickness(5);
        map4_button.setPosition(250, 510);
        buttons.push_back(map4_button);

        sf::Text map4;
        map4.setFont(font);
        map4.setStyle(sf::Text::Bold);
        map4.setString("Map 4");
        map4.setFillColor(sf::Color::White);
        map4.setCharacterSize(75);
        map4.setPosition(270, 505);
        texts.push_back(map4);

        //Map 5 button

        sf::RectangleShape map5_button;
        map5_button.setSize(sf::Vector2f(675, 100));
        map5_button.setFillColor(light_blue);
        map5_button.setOutlineColor(dark_blue);
        map5_button.setOutlineThickness(5);
        map5_button.setPosition(250, 630);
        buttons.push_back(map5_button);

        sf::Text map5;
        map5.setFont(font);
        map5.setStyle(sf::Text::Bold);
        map5.setString("Map 5");
        map5.setFillColor(sf::Color::White);
        map5.setCharacterSize(75);
        map5.setPosition(270, 625);
        texts.push_back(map5);

        //Back button

        sf::RectangleShape back_button;
        back_button.setSize(sf::Vector2f(200, 100));
        back_button.setFillColor(light_blue);
        back_button.setOutlineColor(dark_blue);
        back_button.setOutlineThickness(5);
        back_button.setPosition(487, 755);
        buttons.push_back(back_button);

        sf::Text back;
        back.setFont(font);
        back.setStyle(sf::Text::Bold);
        back.setString("Back");
        back.setFillColor(sf::Color::White);
        back.setCharacterSize(75);
        back.setPosition(500, 755);
        texts.push_back(back);

        bool mouse_released = false;

        while (window.isOpen())
        {   
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

            //Check mouse poition and button presses
            auto mouse_pos = sf::Mouse::getPosition(window);
            auto translated_pos = window.mapPixelToCoords(mouse_pos);

            if(map1_button.getGlobalBounds().contains(translated_pos) && mouse_released) {
                window.close();
                return 3;
            }
            if(map2_button.getGlobalBounds().contains(translated_pos) && mouse_released) {
                window.close();
                return 4;
            }
            if(map3_button.getGlobalBounds().contains(translated_pos) && mouse_released) {
                window.close();
                return 5;
            }
            if(map4_button.getGlobalBounds().contains(translated_pos) && mouse_released) {
                window.close();
                return 6;
            }
            if(map5_button.getGlobalBounds().contains(translated_pos) && mouse_released) {
                window.close();
                return 7;
            }
            if(back_button.getGlobalBounds().contains(translated_pos) && mouse_released) {
                window.close();
                return 1;
            }

            window.clear();
            window.draw(BG_sprite);
            
            for (size_t i = 0; i < buttons.size(); i++){
                window.draw(buttons[i]);
                window.draw(texts[i]);
            }

            window.display();
        }
        return 0;
    }
};

#endif
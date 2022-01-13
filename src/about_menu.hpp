#ifndef ABOUT_MENU
#define ABOUT_MENU

class AboutMenu {
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

        //Texts

        sf::RectangleShape about_background;
        about_background.setSize(sf::Vector2f(800, 500));
        about_background.setFillColor(light_blue);
        about_background.setOutlineColor(dark_blue);
        about_background.setOutlineThickness(5);
        about_background.setPosition(187, 175);

        sf::Text title;
        title.setFont(font);
        title.setStyle(sf::Text::Bold);
        title.setString("Tower defense game");
        title.setFillColor(sf::Color::White);
        title.setCharacterSize(50);

        auto title_bounds = title.getLocalBounds();
        title.setOrigin(title_bounds.left + title_bounds.width/2.0, title_bounds.top + title_bounds.height/2.0);
        title.setPosition(sf::Vector2f(1175/2.0f, 230));

        sf::Text by;
        by.setFont(font);
        by.setStyle(sf::Text::Bold);
        by.setString("made by");
        by.setFillColor(sf::Color::White);
        by.setCharacterSize(32);

        auto by_bounds = by.getLocalBounds();
        by.setOrigin(by_bounds.left + by_bounds.width/2.0, by_bounds.top + by_bounds.height/2.0);
        by.setPosition(sf::Vector2f(1175/2.0f, 290));

        sf::Text names;
        names.setFont(font);
        names.setStyle(sf::Text::Bold);
        names.setString("Mikael Laine, Joonas Savola and Niklas Pigg");
        names.setFillColor(sf::Color::White);
        names.setCharacterSize(32);

        auto names_bounds = names.getLocalBounds();
        names.setOrigin(names_bounds.left + names_bounds.width/2.0, names_bounds.top + names_bounds.height/2.0);
        names.setPosition(sf::Vector2f(1175/2.0f, 340));

        sf::Text date;
        date.setFont(font);
        date.setStyle(sf::Text::Bold);
        date.setString("Autumn 2021");
        date.setFillColor(sf::Color::White);
        date.setCharacterSize(32);

        auto date_bounds = date.getLocalBounds();
        date.setOrigin(date_bounds.left + date_bounds.width/2.0, date_bounds.top + date_bounds.height/2.0);
        date.setPosition(sf::Vector2f(1175/2.0f, 390));

        sf::Text project;
        project.setFont(font);
        project.setStyle(sf::Text::Bold);
        project.setString("Software project for Aalto University course");
        project.setFillColor(sf::Color::White);
        project.setCharacterSize(28);

        auto project_bounds = project.getLocalBounds();
        project.setOrigin(project_bounds.left + project_bounds.width/2.0, project_bounds.top + project_bounds.height/2.0);
        project.setPosition(sf::Vector2f(1175/2.0f, 550));

        sf::Text course;
        course.setFont(font);
        course.setStyle(sf::Text::Bold);
        course.setString("ELEC-A7151 - Object oriented programming with C++");
        course.setFillColor(sf::Color::White);
        course.setCharacterSize(28);

        auto course_bounds = course.getLocalBounds();
        course.setOrigin(course_bounds.left + course_bounds.width/2.0, course_bounds.top + course_bounds.height/2.0);
        course.setPosition(sf::Vector2f(1175/2.0f, 600));


        //Back button

        sf::RectangleShape back_button;
        back_button.setSize(sf::Vector2f(200, 100));
        back_button.setFillColor(light_blue);
        back_button.setOutlineColor(dark_blue);
        back_button.setOutlineThickness(5);
        back_button.setPosition(487, 695);

        sf::Text back;
        back.setFont(font);
        back.setStyle(sf::Text::Bold);
        back.setString("Back");
        back.setFillColor(sf::Color::White);
        back.setCharacterSize(75);
        back.setPosition(500, 695);

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
            window.draw(about_background);
            window.draw(title);
            window.draw(by);
            window.draw(names);
            window.draw(date);
            window.draw(project);
            window.draw(course);
            window.draw(back_button);
            window.draw(back);
            window.display();

            if(back_button.getGlobalBounds().contains(translated_pos) && mouse_released) {
                window.close();
                return 1;
            }
        }
        return 0;
    }
};

#endif
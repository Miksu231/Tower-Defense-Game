#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "game.hpp"
#include "constants.hpp"

/* The GUI class consists of the game interface running while playing a map. This GUI can only simulate one map at a time.*/
class GUI {
public:
    int Run(std::string map_name) { // The main function for starting the GUI. Takes the map's filename as a parameter.

        Game game = Game(map_name);      // Our instance of game being rendered in the GUI
        auto route = game.GetMap().GetRoute(); // The enemy route, a vector of pairs, stored for checking enemy locations for drawing.

        std::pair<int, int> markedTile = std::make_pair(0, 0); // This is the tile that has a red outline on the GUI when clicking. I.e. the tile of a selected tower.
        std::pair<int ,int> destinationTile = std::make_pair(0, 0); // This is the tile that has a blue outline on the GUI when clicking. I.e. where towers will be moved / built to.
        int towerRange = 0;

        std::vector<sf::RectangleShape> shapes; // This stores all rectangular shapes of the GUI, besides the markers
        std::vector<sf::CircleShape> circleshapes; //This stores all circular shapes of the GUI
        std::vector<sf::Sprite> sprites; // This stores all images of the GUI
        std::vector<sf::Text> textStrings; // This stores all texts of the GUI
        std::vector<sf::RectangleShape> markers; // This stores the red and blue outline markers of the GUI

      
        // create the window
        sf::RenderWindow window(sf::VideoMode((game.GetMap().GetHeight()*TILE_SIZE)+200, (game.GetMap().GetWidth()*TILE_SIZE)), "Tower Defense Game"); // Create a window for the game
        window.setVerticalSyncEnabled(true); // Enable Vsync to prevent screen tearing
        window.setFramerateLimit(30); // The game runs at 30 fps 

        for(auto i: game.GetMap().GetTiles()) {
            for(auto j: i) {

                sf::RectangleShape TileShape(sf::Vector2f(TILE_SIZE, TILE_SIZE)); // Create a rectangle for each tile

                if(j.GetType() == Grass) {  // Grass tiles are green with a light gray outline for usability
                    TileShape.setFillColor(sf::Color(0, 153, 0));
                    TileShape.setOutlineColor(sf::Color(128, 128, 128));
                    TileShape.setOutlineThickness(1);
                } else if (j.GetType() == Wall){ // Walls and other types have different colours as well
                    TileShape.setFillColor(sf::Color(156, 121, 103));
                } else {
                    TileShape.setFillColor(sf::Color(223, 212, 181));
                }

                TileShape.setPosition(j.GetCornerPixel().second, j.GetCornerPixel().first); // Set the shape of the rectangle to the tile's location (upper left corner)
                shapes.push_back(TileShape);
            }
        }

        //Draw a sidebar for the buttons
        int edgeLocation = (game.GetMap().GetWidth()*TILE_SIZE); // The horizontal (x) coordinate of the right side of the tiles, i.e. the starting x-coordinate for the sidebar.
        sf::RectangleShape sidebar(sf::Vector2f(200.0, game.GetMap().GetHeight()*TILE_SIZE)); // Make the sidebar grey, and the 200 pixels wide and the height of the entire window
        sidebar.setPosition(edgeLocation, 0);
        sidebar.setFillColor(sf::Color(192, 192, 192));
        shapes.push_back(sidebar);

        sf::RectangleShape moneyCounter(sf::Vector2f(75.0, 75.0)); // Load the icon for money
        moneyCounter.setPosition(edgeLocation+20, 20);
        sf::Texture money;
        if(!money.loadFromFile("Coinstack.png")) { // If we wail to load the image from the file, throw an error
            throw LoadingError();
        }
        moneyCounter.setTexture(&money);
        shapes.push_back(moneyCounter);


        sf::Font font; //Load our font
        if(!font.loadFromFile("Outfit-Light.ttf")) {
            throw LoadingError();
        }

        // Load all the different buttons for our game. Each one is a sprite, which then has a texture laid on top of it. If it fails to load, throw an error.
        sf::Sprite start;
        sf::Texture StartButtonIcon;
        if(!StartButtonIcon.loadFromFile("PlayButton.png")) {
            throw LoadingError();
        }
        sf::Sprite pause;
        sf::Texture PauseButtonIcon;
        if(!PauseButtonIcon.loadFromFile("PauseButton.png")) {
            throw LoadingError();
        }
        sf::Sprite end;
        sf::Texture EndButtonIcon;
        if(!EndButtonIcon.loadFromFile("EndButton.png")) {
            throw LoadingError();
        }
        sf::Sprite restart;
        sf::Texture RestartButtonIcon;
        if(!RestartButtonIcon.loadFromFile("RestartButton.png")) {
            throw LoadingError();
        }
        sf::Sprite TrashBin;
        sf::Texture TrashBinIcon;
        if(!TrashBinIcon.loadFromFile("TrashBin.png")) {
            throw LoadingError();
        }
        sf::Sprite MoveCross;
        sf::Texture MoveIcon;
        if(!MoveIcon.loadFromFile("Move.png")) {
            throw LoadingError();
        }
        sf::Sprite Upgrade;
        sf::Texture UpgradeIcon;
        if(!UpgradeIcon.loadFromFile("Upgrade.png")) {
            throw LoadingError();
        }

        //Colours, locations, and other attributes for the towers in the sidebar as well as the associated texts.
        sf::CircleShape pulse(50);
        sf::CircleShape basic(50);
        sf::CircleShape cannon(50);
        sf::CircleShape freeze(50);
        sf::Text PulseText;
        sf::Text BasicText;
        sf::Text CannonText;
        sf::Text FreezeText;
        pulse.setFillColor(sf::Color(255, 153, 255));
        basic.setFillColor(sf::Color(255, 102, 102));
        cannon.setFillColor(sf::Color(51, 0, 0));
        freeze.setFillColor(sf::Color(0, 255, 255));
        basic.setPosition(edgeLocation, 400);
        cannon.setPosition(edgeLocation, 500);
        pulse.setPosition(edgeLocation, 600);
        freeze.setPosition(edgeLocation, 700);
        PulseText.setFont(font);
        BasicText.setFont(font);
        CannonText.setFont(font);
        FreezeText.setFont(font);
        PulseText.setOutlineColor(sf::Color::Black);
        BasicText.setOutlineColor(sf::Color::Black);
        CannonText.setOutlineColor(sf::Color::Black);
        FreezeText.setOutlineColor(sf::Color::Black);
        PulseText.setString("Pulse\nCost: 350");
        BasicText.setString("Guard\nCost: 150");
        CannonText.setString("Cannon\nCost: 250");
        FreezeText.setString("Freezer\nCost: 100");
        PulseText.setOutlineThickness(1);
        BasicText.setOutlineThickness(1);
        CannonText.setOutlineThickness(1);
        FreezeText.setOutlineThickness(1);
        PulseText.setPosition(edgeLocation+10, 615);
        BasicText.setPosition(edgeLocation+10, 415);
        CannonText.setPosition(edgeLocation+10, 515);
        FreezeText.setPosition(edgeLocation+10, 715);
        BasicText.setFillColor(sf::Color::White);
        CannonText.setFillColor(sf::Color::White);
        FreezeText.setFillColor(sf::Color::White);
        PulseText.setFillColor(sf::Color::White);
        BasicText.setCharacterSize(21);
        PulseText.setCharacterSize(21);
        CannonText.setCharacterSize(21);
        FreezeText.setCharacterSize(21);


        //Set the textures, locations and other attributes for all the buttons
        start.setPosition(edgeLocation, 200);
        start.setTexture(StartButtonIcon);
        pause.setPosition(edgeLocation+100, 200);
        pause.setTexture(PauseButtonIcon);
        end.setPosition(edgeLocation, 300);
        end.setTexture(EndButtonIcon);
        restart.setPosition(edgeLocation+100, 300);
        restart.setTexture(RestartButtonIcon);
        TrashBin.setPosition(edgeLocation+100, 400);
        TrashBin.setTexture(TrashBinIcon);
        MoveCross.setPosition(edgeLocation+100, 500);
        MoveCross.setTexture(MoveIcon);
        Upgrade.setPosition(edgeLocation+100, 600);
        Upgrade.setTexture(UpgradeIcon);
        sprites.push_back(TrashBin);
        sprites.push_back(MoveCross);
        sprites.push_back(start);
        sprites.push_back(pause);
        sprites.push_back(end);
        sprites.push_back(restart);
        sprites.push_back(Upgrade);
    

        //Load sounds from files
        sf::SoundBuffer error;
        if(!error.loadFromFile("error.wav")) {
            throw LoadingError();
        }
        sf::Sound errorSound;
        errorSound.setBuffer(error);

        sf::SoundBuffer saw;
        if(!saw.loadFromFile("saw.wav")) {
            throw LoadingError();
        }
        sf::Sound upgradeSound;
        upgradeSound.setBuffer(saw);

        sf::SoundBuffer hammer;
        if(!hammer.loadFromFile("hammer.wav")) {
            throw LoadingError();
        }
        sf::Sound buildSound;
        buildSound.setBuffer(hammer);

        sf::SoundBuffer moving;
        if(!moving.loadFromFile("move.wav")) {
            throw LoadingError();
        }
        sf::Sound moveSound;
        moveSound.setBuffer(moving);

        bool mouse_released = false; //Boolean for checking mouse clicks

        // run the program as long as the window is open
        while (window.isOpen())
        {
            circleshapes.clear(); //First empty all the changing shapes (towers, enemies, markers, money amount)
            textStrings.clear();
            markers.clear();
            mouse_released = false;

            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                
                if (event.type == sf::Event::MouseButtonReleased){
                    mouse_released = true;
                }
            }

            // clear the window with black color
            window.clear(sf::Color::Black);


            sf::Text moneyAmount; // show the amount of money, and set its attributes
            moneyAmount.setFont(font);
            moneyAmount.setString(std::to_string(game.GetMoney()));
            moneyAmount.setPosition(edgeLocation+100, 25);
            moneyAmount.setCharacterSize(40);
            moneyAmount.setFillColor(sf::Color(0, 0,0));
            textStrings.push_back(moneyAmount);

            // show the current wave in text and set its attributes
            sf::Text waveText;
            waveText.setFont(font);
            waveText.setString("Wave: " + std::to_string(game.GetWaveNumber()) + "/" + std::to_string(game.GetNumberOfWaves()));
            waveText.setPosition(edgeLocation+11, 100);
            waveText.setCharacterSize(33);
            waveText.setFillColor(sf::Color::White);
            waveText.setOutlineColor(sf::Color::Black);
            waveText.setOutlineThickness(1);
            textStrings.push_back(waveText);

            // Show the status of the game i.e. whether it is running, paused, ended, won and so on.
            sf::Text status;
            status.setFont(font);
            if(!game.IsFinished() && game.GetEndPausedStatus()) {
                status.setString("Edit mode");
                status.setFillColor(sf::Color::Yellow);
            }
            else if(!game.GetEndPausedStatus() && !game.IsFinished() && game.GetPausedStatus()) {
                status.setString("Paused");
                status.setFillColor(sf::Color::Red);
            }
            else if(game.IsFinished()) {
                if (game.GetWinningCondition()) {
                    status.setString("You won!!!");
                    status.setFillColor(sf::Color::Blue);
                } else {
                    status.setString("You lost");
                    status.setFillColor(sf::Color::Red);
                }
                    
                
            }
            else {
                status.setString("Running");
                status.setFillColor(sf::Color(0, 255, 0));
            }

            status.setPosition(edgeLocation+25, 150); // All of the texts above have a black outline.
            status.setOutlineColor(sf::Color::Black);
            status.setOutlineThickness(1);
            textStrings.push_back(status);

            for(auto s: game.GetTowers()) { // Draw the towers and set their colours properly
                sf::CircleShape tower(TILE_SIZE/2);
                tower.setPosition(s->GetPosition().first, s->GetPosition().second); // Set the position, top left corner of the tile the tower is in.
                if(s->GetType()=="basic") tower.setFillColor(sf::Color(255, 102, 102)); // Set the colour according to the type of tower.
                else if(s->GetType()=="freeze") tower.setFillColor(sf::Color(0, 255, 255));
                else if(s->GetType()=="cannon") tower.setFillColor(sf::Color(51, 0, 0));
                else tower.setFillColor(sf::Color(255, 153, 255));
                tower.setOutlineColor(sf::Color(128, 128, 128)); 
                tower.setOutlineThickness(1);
                circleshapes.push_back(tower);

                //The text associated with showing the level of a tower.
                sf::Text towerLevel;
                towerLevel.setFont(font);
                towerLevel.setString(std::to_string(s->GetLevel()));
                towerLevel.setPosition(s->GetPosition().first + TILE_SIZE /2 -5, s->GetPosition().second + TILE_SIZE /2 -15);
                towerLevel.setCharacterSize(20);
                towerLevel.setStyle(sf::Text::Bold);
                towerLevel.setFillColor(sf::Color::White);
                towerLevel.setOutlineThickness(1);
                towerLevel.setOutlineColor(sf::Color::Black);
                textStrings.push_back(towerLevel);
            }
            

            for(auto i: game.GetEnemies()) {   // Draw enemies as circles and their colour is set to their type and the colour of the outline indicates their health
                int radius = i->GetRadius(); // The radius of the enemy, because it is a circle.
                auto position = route[i->GetRouteIndex()]; // its location along the route
                sf::CircleShape EnemyShape(radius);

                if (i->Freezed()){   // Set the color depending on the type of enemy.
                    EnemyShape.setFillColor(sf::Color(0, 255, 255));
                } else if(i->GetType()=="Infantry") {
                    EnemyShape.setFillColor(sf::Color(0, 0, 255));
                }
                else if(i->GetType()=="Tank") {
                    EnemyShape.setFillColor(sf::Color(178, 102, 255));
                }
                else if(i->GetType()=="Scout") {
                    EnemyShape.setFillColor(sf::Color(255, 128, 0));
                }
                else if(i->GetType()=="Container") {
                    EnemyShape.setFillColor(sf::Color(255, 128, 0));
                }

                EnemyShape.setOrigin(radius, radius); // Set the origin of the enemy, i.e. the location around which it can be scaled, turned, rotated, etc.
                EnemyShape.setPosition(position.second, position.first); // Set the enemy's position
    
                EnemyShape.setOutlineThickness(round(i->GetRadius()/5)); //Set the outline thickness to 1/5 of the enemy's total radius.
                if(i->GetHealth()<=EnemyLowHP) { // Color of the outline according to the health of the enemy, green for a lot, yellow for some and red for very little
                    EnemyShape.setOutlineColor(sf::Color(255,0,0));
                } else if(i->GetHealth()<=EnemyMidHP) {
                    EnemyShape.setOutlineColor(sf::Color(255, 255, 0));
                } else {
                    EnemyShape.setOutlineColor(sf::Color(0, 255, 0));
                }
                circleshapes.push_back(EnemyShape);
            }   

            for(auto t: game.GetProjectiles()) { //Draw projectiles
                sf::CircleShape projectile(t->GetRadius());
                projectile.setFillColor(sf::Color(64, 64, 64)); // All projectiles are dark gray.
                projectile.setPosition(t->GetPosition().first-t->GetRadius(), t->GetPosition().second-t->GetRadius()); // Set the location of the projectile
                circleshapes.push_back(projectile);
            }
            //Draws a blue shallow rectangle around marked selected grass-tile and red shallow rectangle around selected tower-tile.
            sf::RectangleShape marker(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            marker.setFillColor(sf::Color::Transparent);
            marker.setOutlineColor(sf::Color(0,0,255));
            marker.setOutlineThickness(3);
            marker.setPosition(destinationTile.second*TILE_SIZE, destinationTile.first*TILE_SIZE);
            if (destinationTile != std::make_pair(0, 0) && game.GetMap().GetTile(destinationTile).GetCanPlace()) {
                markers.push_back(marker);
            } // Blue rectangle for the destination

            marker.setFillColor(sf::Color::Transparent);
            marker.setOutlineColor(sf::Color(255, 0, 0)); // Red rectangle for the starting point, i.e. the selected tower
            marker.setOutlineThickness(3);
            marker.setPosition(markedTile.second*TILE_SIZE, markedTile.first*TILE_SIZE); 


            sf::CircleShape rangeForTower(towerRange); // Draw the range of the tower, a transparent circle around the marked tile which contains a tower.
            rangeForTower.setFillColor(sf::Color::Transparent);
            rangeForTower.setOutlineColor(sf::Color(255,255,255));
            rangeForTower.setOutlineThickness(1);
            rangeForTower.setPosition(markedTile.second*TILE_SIZE + (TILE_SIZE-1)/2 + 1 - towerRange, markedTile.first*TILE_SIZE  + (TILE_SIZE-1)/2 + 1 - towerRange);


            if (markedTile != std::make_pair(0,0) && !game.GetMap().GetTile(markedTile).GetCanPlace() && towerRange > 0) { // If marked tile and range is not on the default unselected tile (0, 0), push it to the drawing vector
                markers.push_back(marker);
                circleshapes.push_back(rangeForTower);
            }

            for(auto i: shapes) { // Draw all the rectangles on the screen
                window.draw(i);
            } 
            for(auto s: sprites) { //Draw all the images
                window.draw(s);
            }

            for(auto j: circleshapes) { // Draw all the circular shapes
                window.draw(j);
            }
            for(auto t: textStrings) { // Draw all the text
                window.draw(t);
            }
            for (auto m: markers) { //Draw the selection markers
                window.draw(m);
            }


            // Draw the tower selections
            window.draw(basic);
            window.draw(cannon);
            window.draw(pulse);
            window.draw(freeze);
            window.draw(BasicText);
            window.draw(PulseText);
            window.draw(CannonText);
            window.draw(FreezeText);

            // Detect clicking on tiles
            auto mouse_pos = sf::Mouse::getPosition(window); // The location of the mouse
            auto translated_pos = window.mapPixelToCoords(mouse_pos); // the location of the mouse in window x and y coordinates
            
            if(translated_pos.x>=0 && translated_pos.x<=TILE_SIZE*game.GetMap().GetWidth() && translated_pos.y>=0 && 
            translated_pos.y<=TILE_SIZE*game.GetMap().GetHeight() && mouse_released) { //Check if we clicked a tile on the screen
        
                std::pair<int, int> placeholder = std::make_pair(floor(translated_pos.y/TILE_SIZE), floor(translated_pos.x/TILE_SIZE)); // placeholder for remembering which tile was clicked

                if(!game.GetMap().GetTile(placeholder).GetCanPlace()) { // If it's not an empty tile, check if there's a tower in said tile.

                    std::pair<int, int> tileUpLeft = std::make_pair(game.GetMap().GetTile(placeholder).GetCornerPixel().second, game.GetMap().GetTile(placeholder).GetCornerPixel().first); // The upper left pixel of the pressed tile

                    for(auto tower: game.GetTowers()) { // Iterate through all the towers
                        std::pair<int, int> towerPos = (*tower).GetPosition();
                        if(towerPos.first==tileUpLeft.first && towerPos.second==tileUpLeft.second) { // If there is a tower in the tile we have clicked
                            if (markedTile.first == placeholder.first && markedTile.second == placeholder.second){ // if we clicked on a tower tile we have already marked, deselect it.
                                markedTile = std::make_pair(0 ,0);
                            } else { // otherwise mark the tile
                                markedTile = placeholder;
                                towerRange = tower->GetRange();
                            }
                        }
                    }
                } else { // If we clicked on an empty tile we have already selected, deselect it
                    if (destinationTile == placeholder){
                        destinationTile = std::make_pair(0 ,0);
                    } else {
                        destinationTile = placeholder;
                    }
                }
            }
            //Click detection for all the buttons of the game
            //Detect start button
            if(start.getGlobalBounds().contains(translated_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if(game.GetPausedStatus()) { // If the game is paused, resume, instead of starting
                game.Resume();
                }
                else game.Start();
            }
            //Detect pause button
            if(pause.getGlobalBounds().contains(translated_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if(!game.GetPausedStatus()) game.Pause();
            }
            //Detect quit button
            if(end.getGlobalBounds().contains(translated_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                game.End();
                return 2;
            }
            //Detect restart button
            if(restart.getGlobalBounds().contains(translated_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                game.Restart();
            }
            //Detect the trashcan icon to remove towers
            if(TrashBin.getGlobalBounds().contains(translated_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && game.GetEndPausedStatus() && markedTile.first!=0 && markedTile.second != 0) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // Stop the mouse being pressed twice, i.e. only detect clicking when the mouse button is released
                    mouse_pos = sf::Mouse::getPosition(window);
                    translated_pos = window.mapPixelToCoords(mouse_pos); 
                    if(TrashBin.getGlobalBounds().contains(translated_pos) && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if(!game.RemoveTower(markedTile)) errorSound.play();
                        }
                }
            }
            //Detect the moving cross being clicked
            if(MoveCross.getGlobalBounds().contains(translated_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && destinationTile.first!=0 && destinationTile.second != 0) { //Stop a tower from being moved to 0, 0
                while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // Stop the mouse being pressed twice, i.e. only detect clicking when the mouse button is released
                    mouse_pos = sf::Mouse::getPosition(window);
                    translated_pos = window.mapPixelToCoords(mouse_pos); 
                    if(MoveCross.getGlobalBounds().contains(translated_pos) && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if(game.MoveTower(destinationTile, markedTile)) moveSound.play(); // If we can move a tower, play the moving sound, otherwise error sound
                        else errorSound.play();
                        }
                }
            }
            //Detect tower upgrading
            if(Upgrade.getGlobalBounds().contains(translated_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && game.GetEndPausedStatus() && markedTile.first!=0 && markedTile.second != 0) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    mouse_pos = sf::Mouse::getPosition(window);
                    translated_pos = window.mapPixelToCoords(mouse_pos); 
                    if(Upgrade.getGlobalBounds().contains(translated_pos) && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if(game.UpgradeTower(markedTile)) upgradeSound.play(); //If there is a tower to be upgraded, play a sawing sound, otherwise error sound
                        else errorSound.play();
                        }
                }
            }
            //Detect the guard tower icon of the sidebar being clicked, i.e. guard building button
            if(basic.getGlobalBounds().contains(translated_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)&& game.GetEndPausedStatus()) {
                if(game.GetMap().GetTile(destinationTile).GetCanPlace()) {
                    if(game.BuildTower(destinationTile, "basic")) buildSound.play();
                    else errorSound.play();
                }

            }
            //Detect the cannon tower icon of the sidebar being clicked, i.e. cannon building button
            if(cannon.getGlobalBounds().contains(translated_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && game.GetEndPausedStatus()) {
                if(game.GetMap().GetTile(destinationTile).GetCanPlace()) {
                    if(game.BuildTower(destinationTile, "cannon")) buildSound.play();
                    else errorSound.play();
                }
            }
            //Detect the pulse tower icon of the sidebar being clicked, i.e. pulse building button
            if(pulse.getGlobalBounds().contains(translated_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && game.GetEndPausedStatus()) {
                // Build pulse
                if(game.GetMap().GetTile(destinationTile).GetCanPlace()) {
                    if(game.BuildTower(destinationTile, "pulse")) buildSound.play();
                    else errorSound.play();
                }

            }
            //Detect the freeze tower icon of the sidebar being clicked, i.e. freeze building button
            if(freeze.getGlobalBounds().contains(translated_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && game.GetEndPausedStatus()) {
                if(game.GetMap().GetTile(destinationTile).GetCanPlace()) {
                    if(game.BuildTower(destinationTile, "freeze")) buildSound.play();
                    else errorSound.play();
                }
            }

 
            // end the current frame
            window.display();
            
            //If we haven't finished or paused the game, update the game's logic.
            if (!game.GetPausedStatus() && !game.GetEndPausedStatus()) {
                game.Advance();
            }

        }

        return 0;
    }
};

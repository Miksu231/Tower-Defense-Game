#include "gui.hpp"
#include "main_menu.hpp"
#include "map_menu.hpp"
#include "about_menu.hpp"

int main() {

    MainMenu menu;
    MapMenu map_menu;
    AboutMenu about_menu;
    GUI game_gui;
    
    //We keep track of the program state with this variable to control the execution flow
    //between all GUI components
    int state = 1;
    while (state != 0){
        switch (state){
        case 1:
            state = menu.Run();
            break;
        case 2:
            state = map_menu.Run();
            break;
        case 3:
            state = game_gui.Run("map1.txt");
            break;
        case 4:
            state = game_gui.Run("map2.txt");
            break;
        case 5:
            state = game_gui.Run("map3.txt");
            break;
        case 6:
            state = game_gui.Run("map4.txt");
            break;
        case 7:
            state = game_gui.Run("map5.txt");
            break;
        case 8:
            state = about_menu.Run();
            break;
        }
    }
    
    return 0; 
}
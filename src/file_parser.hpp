#ifndef FILE_PARSER
#define FILE_PARSER

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>

#include "map.hpp"
#include "tile.hpp"
#include "enemy.hpp"

//Exception that is thrown if there occurs any errors while reading the file
class CorruptedSaveFile : public std::exception {
    virtual const char* what() const noexcept {
        return "Corrupted save file";
    }
};

//Function that reads map from file and returns Map instance
std::pair<Map, std::vector<std::vector<std::shared_ptr<Enemy>>>> MapFromFile(std::string& filename) {
    //Try-catch to catch any errors that are not CorruptedSaveFile exceptions
    //that might occur during the file reading
    try {
        //variables for each data field in the map save fromat
        std::string name;
        std::string version;
        std::string width;
        std::string height;
        std::vector<std::vector<TileType>> tile_types;
        std::vector<std::vector<std::shared_ptr<Enemy>>> waves;

        //Open file stream
        std::ifstream file_stream(filename);

        //Temporary variable to hold the line read from the stream
        std::string line;
        std::getline(file_stream, line);

        //Check if the file is correct type (first line indicates that the file is map save)
        if (line != "td_game savefile"){
            throw CorruptedSaveFile();
        }
        
        //Read all data fields from the stream
        std::getline(file_stream, name);
        std::getline(file_stream, version);
        std::getline(file_stream, width);
        std::getline(file_stream, height);

        if (width.front() != 'w' || height.front() != 'h') {
            throw CorruptedSaveFile();
        }

        //Check that the file includes the map structure
        std::getline(file_stream, line);
        if (line != "structure"){
            throw CorruptedSaveFile();
        }

        //Read each line from the structure, loop through each line and add the type of each 
        //tile to the vector
        size_t index = 0;
        while (!file_stream.eof()) {
            std::getline(file_stream, line);

            if (line == "waves"){
                break;
            }

            tile_types.push_back(std::vector<TileType>());
            for (auto c : line){
                int type = c - '0';
                tile_types[index].push_back(static_cast<TileType>(type));
            }
            index++;
        }

        //Add waves
        while (!file_stream.eof()) {
            std::getline(file_stream, line);

            std::vector<std::shared_ptr<Enemy>> wave;

            auto it = line.begin();
            while (it != line.end()){
                int number = *(it)- '0';
                it++;
                char enemy_type = *(it);
                it++;

                for (int i = 0; i < number; i++){
                    switch (enemy_type){
                    case 'I':              
                        wave.push_back(std::make_shared<Infantry>());
                        break;     
                    case 'T':
                        wave.push_back(std::make_shared<Tank>());
                        break;
                    case 'S':
                        wave.push_back(std::make_shared<Scout>());
                        break;
                    case 'C':
                        wave.push_back(std::make_shared<Container>());
                        break;
                    }  
                }
            }
            if (!wave.empty()){
                waves.push_back(wave);
            }   
        }


        //If all tests above have passed and file is read entirely,
        //construct new Map instance. eturn it.
        return std::make_pair(Map(tile_types), waves);
        
    //Catch possible errors and throw them down on the stack    
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        throw e;
    }  
}


#endif
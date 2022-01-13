#include "game.hpp"
#include "file_parser.hpp"


Game::Game(std::string map_filename) {
    std::pair<Map, std::vector<std::vector<std::shared_ptr<Enemy>>>> parser_return;
    parser_return = MapFromFile(map_filename);
    map_ = parser_return.first;
    route_ = map_.GetRoute();
    waves_ = parser_return.second;
    number_of_waves = waves_.size();
    is_finished_ = false;
    endPaused_ = true;
    money_ = 1200;
    count_ = 0;
    wave_number_ = 0;
    map_name_ = map_filename;
    if(!pop.loadFromFile("pop.wav")) {
        throw LoadingError();
    }
    popSound.setBuffer(pop);
}

Map& Game::GetMap() {
    return map_;
}

std::vector< std::shared_ptr<Tower> >& Game::GetTowers() {
    return towers_;
}

std::vector< std::shared_ptr<Enemy> >& Game::GetEnemies() {
    return enemies_;
}

std::vector< std::shared_ptr<Projectile> >& Game::GetProjectiles() {
    return projectiles_;
}

bool Game::IsFinished() const {
    return is_finished_;
}

int Game::GetMoney() const {
    return money_;
}

std::pair<int, int> Game::GetEnemyPositionIn(Enemy& enemy, int turns) const {
    return route_.at(enemy.GetRouteIndex() + turns*enemy.GetSpeed());
}


std::pair<std::pair<int, int>,int> Game::FindTarget(std::shared_ptr<Tower> tower) const {
    for (auto it : enemies_ ) {
        if (GetDistance(tower->GetCenterPixel(), std::make_pair(route_[it->GetRouteIndex()].second, route_[it->GetRouteIndex()].first)) <= tower->GetRange()) { 

            long unsigned int k = it->GetRouteIndex() + tower->GetRange();  // this limits finding targets.

            for (long unsigned int i = it->GetRouteIndex(); i < route_.size() -10 && i < k ; i = i + it->GetSpeed() ) {

                if(GetDistance(tower->GetCenterPixel(), std::make_pair(route_[i].second, route_[i].first)) <= tower->GetRange() 
                && round(GetDistance(tower->GetCenterPixel(), std::make_pair(route_[i].second, route_[i].first)) / tower->GetProjectileSpeed()) == i - it->GetRouteIndex() ) {

                    return std::make_pair(std::make_pair(route_[i].second, route_[i].first),i - it->GetRouteIndex());
                }
            }
        }
    }
    return  std::make_pair(std::make_pair(-1, -1), -100);
}

void Game::Advance () {
    
    if(is_finished_) End();
    else {
        AdvanceEnemies();
        AdvanceTowers();
        AdvanceProjectiles();
        DetectCollision();
        UpdateCount();
        SpawnEnemies();
        RemoveDeadEnemies();
        sort(enemies_.begin(), enemies_.end(), ComparePosition);

        //If wave is empty and there is no more enemies in the map, clear all projectiles from the map
        //and change endPaused_ to true (edit mode)
        if (wave_.empty() && enemies_.empty()){
            endPaused_ = true;
            ClearProjectiles();
            //If waves is empty, the player has won the game
            if (waves_.empty()){
                is_finished_ = true;
                winningCondition_ = true;
            }
        }
    }
}

int Game::GetDistance(std::pair<int, int> a,std::pair<int, int> b) const {
    return round(sqrt((a.first - b.first)*(a.first - b.first) +  (a.second - b.second)*(a.second - b.second)));
}

void Game::Start() {
    paused_ = false;
    
    if (!waves_.empty() && endPaused_){
        wave_number_++;
        wave_ = waves_.back();
        waves_.pop_back();
        endPaused_ = false;
    }
}

void Game::Pause() {
    paused_=true;
}

void Game::End() {
    projectiles_.clear();
    is_finished_ = true;
}

void Game::Resume() {
    paused_= false;
    endPaused_ = false;
}

void Game::Restart() {
    enemies_.clear();
    towers_.clear();
    projectiles_.clear();
    //Since we use shared pointers with enemies, we can't save the waves to temporary variable
    //and use that to reset the waves. We need to reload the game again from savefile to reset
    //all enemies and their positions
    std::pair<Map, std::vector<std::vector<std::shared_ptr<Enemy>>>> parser_return;
    parser_return = MapFromFile(map_name_);
    map_ = parser_return.first;
    route_ = map_.GetRoute();
    waves_ = parser_return.second;
    paused_= false;
    is_finished_ = false;
    endPaused_ = true;
    winningCondition_ = false;
    money_ = 1200;
    count_ = 0;
    wave_number_ = 0;
}


//Uses index position (!!! NOT PIXEL POSITION)
bool Game::BuildTower(std::pair<int, int> index, const std::string& name) {
    if(map_.GetTile(index).GetCanPlace()) {
        if(name == "basic" && GetMoney() >= 150) {
            towers_.push_back(std::make_shared<BasicTower>(map_.GetPixel(index))); 
            map_.GetTile(index).Place();
            money_ = money_ - 150;
            return true;
        } else if(name == "cannon" && GetMoney() >= 250) {
            towers_.push_back(std::make_shared<CannonTower>(map_.GetPixel(index))); 
            map_.GetTile(index).Place();
            money_ = money_ - 250;
            return true;
        } else if(name == "freeze" && GetMoney() >= 100) {
            towers_.push_back(std::make_shared<FreezeTower>(map_.GetPixel(index))); 
            map_.GetTile(index).Place();
            money_ = money_ - 100;
            return true;
        } else if(name == "pulse" && GetMoney() >= 350) {
            towers_.push_back(std::make_shared<PulseTower>(map_.GetPixel(index))); 
            map_.GetTile(index).Place();
            money_ = money_ - 350;
            return true;
        }
    }
    return false; 
}

//Uses index position
bool Game::MoveTower(std::pair<int, int> newIndex, std::pair<int, int> oldIndex) {
    for (auto it : towers_) {
        if(it->GetPosition() == map_.GetPixel(oldIndex) && map_.GetTile(newIndex).GetCanPlace()) {
            it->Move(map_.GetPixel(newIndex));
            map_.GetTile(newIndex).Place();
            map_.GetTile(oldIndex).UnassignTower();
            return true;
        }
    }
    return false;
}

//Uses index position
bool Game::RemoveTower(std::pair<int, int> index) {
    for (auto it = towers_.begin(); it != towers_.end(); it++) {
        if((*it)->GetPosition() == (map_.GetPixel(index))) {
            money_ = money_ + (*it)->GetCost();
            towers_.erase(it);
            map_.GetTile(std::make_pair(index.first, index.second)).UnassignTower();
            return true;
        }
    }
    return false;
} 

void Game::DetectCollision() {
    for (auto enemy = enemies_.begin(); enemy != enemies_.end(); enemy++) {
        for (auto projectile = projectiles_.begin(); projectile != projectiles_.end(); projectile++) {
            auto enemy_pos = route_[(*enemy)->GetRouteIndex()];
            auto projectile_pos = (*projectile)->GetCenterPixel();

            //Check if the distance on x- or y-axle is greater than the maximum possible radiuses combined 
            //If the distance on one of the axels is greater, the projectile cannot hit and more precise
            //distance calculation is not needed. If not, the exact distance is calculated for the 
            //collision detection
            if (abs(enemy_pos.second-projectile_pos.first) > 50 || abs(enemy_pos.first-projectile_pos.second) > 50) {
                continue;
            } else if ( GetDistance(std::make_pair(enemy_pos.second, enemy_pos.first), projectile_pos) 
            < ((*enemy)->GetRadius() + (*projectile)->GetRadius()) && (*enemy)->GetHealth() > 0) {
                (*enemy)->ReduceHealth((*projectile)->GetDamage());

                //If projectile is freeze type, slow enemies and delete projectile
                if((*projectile)->GetType() == ((ProjectileType)2) ) {
                    (*enemy)->Freeze((*projectile)->GetDamage());
                    projectiles_.erase(projectile);
                    projectile--;
                } else if((*projectile)->GetType() == ((ProjectileType)0)) {
                    projectiles_.erase(projectile);  //deletes basic projectile immediately
                    projectile--; //this is needed not skip element during erase.
                }
            }
        }
    }
} 

void Game::UpdateCount() {
    if (count_ > 44999) {
        count_ = 0;
    } else {
        count_++;
    }
}

bool Game::ComparePosition(std::shared_ptr<Enemy>& a, std::shared_ptr<Enemy>& b) {
    return (a->GetRouteIndex() > b->GetRouteIndex());
}

void Game::AdvanceProjectiles() {
    for(auto projectile = projectiles_.begin(); projectile != projectiles_.end(); projectile++) {
        //If projectile has reached its maximum range, delete it
        if (((*projectile)->GetDistance() >=  (*projectile)->GetRange() || (*projectile)->GetStatus())) {
            projectiles_.erase(projectile);
            projectile--;
        } else {
            (*projectile)->Move();
        }
    }
}

void Game::AdvanceTowers() {
    for(auto tower : towers_) {
        //If tower is ready to shoot, find target and fire new projectiles
        if (tower.get()->GetFireStatus()){
            std::pair<std::pair<int, int>, int> target = FindTarget(tower);
            //If target is found, fire 
            if (target.second != -100) {
                std::vector< std::shared_ptr<Projectile> > newProjectiles = tower->Fire(target);
                projectiles_.insert(projectiles_.end(), newProjectiles.begin(), newProjectiles.end());
                newProjectiles.clear();
            }
        }
    }
}

void Game::AdvanceEnemies() {
    int routeSize = map_.GetRoute().size();
    int upperLimit = std::max(routeSize-10 , 0);
    for (auto enemy : enemies_){
        //Check if enemy has reached the end of the path
        if (enemy.get()->Move() > upperLimit){
            is_finished_ = 1;
            paused_ = 1;
            break;
        }
    }
}

int Game::GetWaveNumber() const {
    return wave_number_;
}

void Game::SpawnEnemies() {
    //Time interval for enemy spawning, 30 = 1 second (fps 30)
    //Currently the interval is 20 = 0.6667 seconds
    if (count_%20 == 0){
        //Check if wave is empty. If not, add new enemy from current wave to enemies vector
        if (!wave_.empty()){
            enemies_.push_back(wave_.back());
            wave_.pop_back();
        } 
    }
}

void Game::RemoveDeadEnemies() {
    //Temporary vector to hold new enemies that spawn when container enemy is destroyed
    std::vector<std::shared_ptr<Enemy>> tmp;

    for(auto enemy = enemies_.begin(); enemy != enemies_.end(); enemy++) {
        if((*enemy)->GetHealth() <= 0 ) {
            //If enemy is container, make 3 new enemies that spawn close to the container's position
            if ((*enemy)->GetType() == "Container"){
                int route_index = (*enemy)->GetRouteIndex();
                //Bounds to check to prevent index out of bounds
                int lowerBound = std::max(0 , route_index -40);
                int routeSize = map_.GetRoute().size() - 1;
                int upperBound = std::min(std::max(routeSize, 0), route_index + 40 ); 
                tmp.push_back(std::make_shared<Infantry>(lowerBound));
                tmp.push_back(std::make_shared<Infantry>(route_index));
                tmp.push_back(std::make_shared<Infantry>(upperBound));
            }
            money_ += (*enemy)->GetValue();
            enemies_.erase(enemy); //deletes enemy if healt drops to zero or below
            popSound.play();
            enemy--;
        }
    }
    //Push back the enemies to the enemies vector that were created when container enemy was destroyed
    for (auto e : tmp){
        enemies_.push_back(e);
    }
}

bool Game::GetEndPausedStatus() { 
    return endPaused_;
}

bool Game::GetPausedStatus() {
    return paused_;
}

void Game::SetEndPaused(bool status) {
    endPaused_ = status;
}

void Game::SetPaused(bool status) {
    paused_ = status;
}

void Game::ClearProjectiles() {
    projectiles_.clear();
}

bool Game::UpgradeTower(std::pair<int, int> index) {
    for (auto it = towers_.begin(); it != towers_.end(); it++) {
        if((*it)->GetPosition() == (map_.GetPixel(index)) && money_>=round((*it)->GetCost()*0.5)) {
            money_= money_ - round((*it)->GetCost()*0.5);
            (*it)->Upgrade();
            return true;
        }
    }
    return false;
}

bool Game::GetWinningCondition() {
    return winningCondition_;
}

int Game::GetNumberOfWaves() const {
    return number_of_waves;
}

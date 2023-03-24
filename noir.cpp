//include all relevant libraries
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class Player {
    public:
    string name;
    string location;
    vector<string> inventory;
};

class Location {
    public:
    string name;
    string intro;
    vector<string> talk;
    vector<string> fight;
    vector<string> investigate;
    vector<string> take;
    vector<string> exits;
};


void display(Player player, map<string, Location> locations) {
    Location location = locations[player.location];
    cout << "Location: " << location.name << endl;
    cout << location.intro << endl;
    cout << "Inventory: ";
    for (string item : player.inventory) {
        cout << item << " ";
    }
    cout << endl;
    cout << "Exits: ";
    for (string exit : location.exits) {
        cout << exit << " ";
    }
    cout << endl;
}


int main() {
    
    bool running = true;
    //initiate a player
    Player player;
    //initiate the map

    Location alley;
    alley.name = "alley";
    alley.intro = "You are in a rainy alley with a cigeratte. An unconsious man has propped himself against a wall for the night.";
    alley.talk[0] = "You lean over the homeless man. You shout at the man to scare him awake, but the man just grunts, rolls over.";
    alley.fight[0] = "You cannot fight the homeless man. He is homeless.";
    alley.investigate[0] = "You are in an alley behind a greasy bar called Rubber Moses. The homeless man is sleeping on a flattened cardboard box, he smells of urine. A drunk most likely. A lone street lamp flickers overhead. The light is poor, but you can see the patch under your feet is dried blood.";
    alley.take[0] = "There is nothing to take. He is homeless.";
    alley.exits[0] = "bar street";

    Location bar;
    bar.name = "bar";
    bar.intro = "The dingy bar";
    bar.talk[0] = "You lean over the homeless man. You shout at the man to scare him awake, but the man just grunts, rolls over.";
    bar.fight[0] = "You cannot fight the homeless man. He is homeless.";
    bar.investigate[0] = "You are in an alley behind a greasy bar called Rubber Moses. The homeless man is sleeping on a flattened cardboard box, he smells of urine. A drunk most likely. A lone street lamp flickers overhead. The light is poor, but you can see the patch under your feet is dried blood.";
    bar.take[0] = "There is nothing to take. He is homeless.";
    bar.exits[0] = "alley street";

    Location street;
    street.name = "street";
    street.intro = "The street is dark and wet. The rain is coming down in sheets. You can see a bar and an alley.";
    street.talk[0] = "You lean over the homeless man. You shout at the man to scare him awake, but the man just grunts, rolls over.";
    street.fight[0] = "You cannot fight the homeless man. He is homeless.";
    street.investigate[0] = "You are in an alley behind a greasy bar called Rubber Moses. The homeless man is sleeping on a flattened cardboard box, he smells of urine. A drunk most likely. A lone street lamp flickers overhead. The light is poor, but you can see the patch under your feet is dried blood.";
    street.take[0] = "There is nothing to take. He is homeless.";
    street.exits[0] = "bar alley";

    //make a player map
    map<string, Location> locations { {"alley", alley}, {"bar", bar}, {"street", street}};

    //intro
    cout << "You can talk, fight, investigate, take, or go" << endl;
    cout << "You can also quit" << endl;
    cout << "What is your name?" << endl;
    getline(cin, player.name);
    cout << "Welcome " << player.name << endl;
    //assign the player the alley location
    player.location = "alley";
    while(running) {
        cout << "\n";
        cout << locations[player.location].intro << endl;
        cout << "What do you want to do?" << endl;
        //menus
        display(player,locations);
        //take an action
        string action;
        getline(cin, action);
        if(action == "quit") {
            running = false;
        }
        if(action == "talk"){
            if(player.location == "alley"){
                cout << alley.talk[0] << endl;
            }
        }
        if(action == "fight"){
            if(player.location == "alley"){
                cout << alley.fight[0] << endl;
            }
        }
        if(action == "investigate"){
            if(player.location == "alley"){
                cout << alley.investigate[0] << endl;
            }
        }
        if(action == "take"){
            if(player.location == "alley"){
                cout << alley.take[0] << endl;
            }
        }
        if(action == "go"){
            string _exits = locations[player.location].exits[0];
            cout << _exits << endl;
            string choice;
            getline(cin, choice);
            cout << _exits.find(choice) << "\n";
            if(_exits.find(choice) >= 0 && _exits.find(choice) < 100){
                player.location = choice;
            } else {
                cout << "You cannot go there" << "\n";
            }
        }
        
    }
    return 0;
}


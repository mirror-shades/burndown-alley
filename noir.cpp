#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

enum class Action
{
    Talk,
    Fight,
    Investigate,
    Take,
    Go,
    Invalid
};

Action stringToAction(const string &str)
{
    if (str == "talk")
        return Action::Talk;
    else if (str == "fight")
        return Action::Fight;
    else if (str == "investigate")
        return Action::Investigate;
    else if (str == "take")
        return Action::Take;
    else if (str == "go")
        return Action::Go;
    return Action::Invalid;
}

class Player
{
public:
    string name;
    string location;
    vector<string> inventory;

    void addToInventory(const string &item)
    {
        inventory.push_back(item);
    }

    void displayInventory() const
    {
        cout << "Inventory: ";
        for (const auto &item : inventory)
        {
            cout << item << " ";
        }
        cout << endl;
    }
};

class Location
{
public:
    string name;
    string intro;
    map<Action, vector<string>> actions;
    map<string, string> exits;

    void addExit(const string &exit, const string &target)
    {
        exits[exit] = target;
    }

    bool isValidExit(const string &exit, string &newLocation)
    {
        auto it = exits.find(exit);
        if (it != exits.end())
        {
            newLocation = it->second;
            return true;
        }
        return false;
    }

    void displayActionOutcome(Action action)
    {
        if (actions.find(action) != actions.end() && !actions[action].empty())
        {
            cout << actions[action][0] << endl;
        }
    }
};

void display(const Player &player, const map<string, Location> &locations)
{
    const Location &location = locations.at(player.location);
    cout << "Location: " << location.name << endl
         << location.intro << endl;
    player.displayInventory();
    cout << "Exits: ";
    for (const auto &exit : location.exits)
    {
        cout << exit.first << " ";
    }
    cout << endl;
}

void processAction(const string &actionStr, Player &player, map<string, Location> &locations)
{
    Action action = stringToAction(actionStr);
    auto &currentLocation = locations[player.location];
    switch (action)
    {
    case Action::Talk:
    case Action::Fight:
    case Action::Investigate:
    case Action::Take:
        currentLocation.displayActionOutcome(action);
        break;
    case Action::Go:
    {
        cout << "Available exits: ";
        for (const auto &exit : currentLocation.exits)
        {
            cout << exit.first << " ";
        }
        cout << "\nWhere do you want to go? ";
        string newLocationKey;
        getline(cin, newLocationKey);
        string newLocation;
        if (currentLocation.isValidExit(newLocationKey, newLocation))
        {
            player.location = newLocation;
        }
        else
        {
            cout << "You cannot go there.\n";
        }
    }
    break;
    default:
        cout << "Invalid action. Please try again." << endl;
        break;
    }
}

Location createLocation(const string &name, const string &intro, const initializer_list<pair<Action, vector<string>>> &actions)
{
    Location loc;
    loc.name = name;
    loc.intro = intro;
    for (const auto &action : actions)
    {
        loc.actions[action.first] = action.second;
    }
    return loc;
}

int main()
{
    bool running = true;
    Player player;

    map<string, Location> locations{
        {"bar", createLocation("Bar", "You are at the bustling night bar.", {
                                                                                {Action::Talk, {"You talk to the bartender."}},
                                                                                {Action::Fight, {"A brawl breaks out at the bar."}},
                                                                                {Action::Investigate, {"You notice a shady figure at the corner table."}},
                                                                                {Action::Take, {"You grab a forgotten umbrella from a bar stool."}},
                                                                            })},
        {"alley", createLocation("Alley", "You are in a rainy alley, dimly lit and desolate.", {
                                                                                                   {Action::Talk, {"No one here to talk to."}},
                                                                                                   {Action::Fight, {"Fighting shadows, are we?"}},
                                                                                                   {Action::Investigate, {"It's just garbage bins and a stray cat."}},
                                                                                                   {Action::Take, {"You found a rusty coin. Great."}},
                                                                                               })},
        {"library", createLocation("Library", "Books from floor to ceiling. The scent of wisdom fills the air.", {
                                                                                                                     {Action::Talk, {"You ask the librarian for a book recommendation."}},
                                                                                                                     {Action::Fight, {"This is a place of peace. No fighting here."}},
                                                                                                                     {Action::Investigate, {"Amongst the old books, you find a rare first edition."}},
                                                                                                                     {Action::Take, {"You borrow a book on ancient civilizations."}},
                                                                                                                 })},
        {"Helen's Apartment", createLocation("Helen's Apartment", "Modern, chic, but with a personal touch.", {
                                                                                                                  {Action::Talk, {"Helen isn't here right now."}},
                                                                                                                  {Action::Fight, {"You wouldn't dare."}},
                                                                                                                  {Action::Investigate, {"You find a photo of Helen in Paris."}},
                                                                                                                  {Action::Take, {"You take a moment to appreciate the vibe."}},
                                                                                                              })},
        {"bowling alley", createLocation("Bowling Alley", "Loud music plays as pins crash. A perfect strike.", {
                                                                                                                   {Action::Talk, {"You chat with a group celebrating a birthday."}},
                                                                                                                   {Action::Fight, {"A playful scuffle over the score."}},
                                                                                                                   {Action::Investigate, {"You find a lost wallet under a seat."}},
                                                                                                                   {Action::Take, {"You grab a pair of shoes size 9."}},
                                                                                                               })}};

    // Add exits manually to each location
    locations["bar"].addExit("alley", "alley");
    locations["alley"].addExit("bar", "bar");
    locations["alley"].addExit("library", "library");
    locations["library"].addExit("alley", "alley");
    locations["library"].addExit("Helen's Apartment", "Helen's Apartment");
    locations["Helen's Apartment"].addExit("library", "library");
    locations["Helen's Apartment"].addExit("bowling alley", "bowling alley");
    locations["bowling alley"].addExit("Helen's Apartment", "Helen's Apartment");

    cout << "You can talk, fight, investigate, take, or go" << endl
         << "You can also quit" << endl;
    cout << "What is your name?" << endl;
    getline(cin, player.name);
    cout << "Welcome " << player.name << endl;
    player.location = "alley";

    while (running)
    {
        cout << "\n---------------------------------------\n";
        display(player, locations);
        cout << "What do you want to do?" << endl;
        cout << "talk, fight, investigate, take, or go" << endl;
        string action;
        getline(cin, action);

        if (action == "quit")
        {
            cout << "Quitting game. Goodbye!\n";
            break;
        }

        processAction(action, player, locations);
    }

    return 0;
}
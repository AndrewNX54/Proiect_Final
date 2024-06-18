#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <mmsystem.h>

#pragma comment (lib, "winmm.lib")

class Player
{
    std::string player_name = "";
    int playerClass = 1;
    int hp = 1;
    int attack = 1;
    std::vector<std::string> inventory;

public:
    int getPlayerClass()
    {
        return playerClass;
    }
    void HPdamage(int damageTaken)
    {
        hp -= damageTaken;
    }
    int getPlayerHP()
    {
        return hp;
    }
    int getPlayerAttack()
    {
        return attack;
    }
    void addInventory(std::string item)
    {
        inventory.push_back(item);
    }

    Player(std::string player_name, int playerClass, int hp, int attack)
    {
        this->player_name = player_name;
        this->playerClass = playerClass;
        this->hp = hp;
        this->attack = attack;
    }
};

void intro()
{
    std::cout << "Hello Player, welcome to my game ! \n Do you want to play ? YES/NO" << std::endl;
}

Player setup()
{
    std::string name;
    int player_class;
    std::cout << "Enter player's name : ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << std::endl;

    std::cout << "Choose your class : \n 1) Wizard \n 2) Warrior \n 3) Rogue \n ";
    std::cout << "Your choice : ";
    std::cin >> player_class;
    std::cout << std::endl;
    if (player_class == 1)
    {
        std::cout << "You became a wizard" << std::endl;
        return Player(name, player_class, 90, 40);
    }
    else if (player_class == 2)
    {
        std::cout << "You became a warrior" << std::endl;
        return Player(name, player_class, 150, 55);
    }
    else if (player_class == 3)
    {
        std::cout << "You became a rogue" << std::endl;
        return Player(name, player_class, 250, 75);
    }
    else
    {
        std::cout << "Invalid choice, you became a wizard by default" << std::endl;
        return Player(name, 1, 90, 40);
    }
}

void crossroads()
{
    std::cout << "You can choose between these 3 paths : \n";
    std::cout << " 1. Forest \n 2. Cave \n 3. Village \n";
    std::cout << "Your choice : ";
    int path;
    std::cin >> path;
    switch (path)
    {
    case 1:
        std::cout << "You will explore the forest \n";
        break;
    case 2:
        std::cout << "You will explore the cave \n";
        break;
    case 3:
        std::cout << "You will explore the village \n";
        break;
    default:
        std::cout << "Invalid choice, you will automatically go to the forest\n";
        path = 1;
        break;
    }
}

void chest(Player& player)
{
    std::string a;
    std::cout << "You found a chest, do you want to open it ? YES / NO \n";
    std::cin >> a;
    std::cout << std::endl;
    if (a == "YES")
    {
        if (player.getPlayerClass() == 1)
        {
            player.addInventory("Staff");
            std::cout << "The following item has been added to your inventory :  Staff"<< std::endl;
        }
        else if (player.getPlayerClass() == 2)
        {
            player.addInventory("Greatsword");
            std::cout << "The following item has been added to your inventory :  Greatsword" << std::endl;
        }
        else if (player.getPlayerClass() == 3)
        {
            player.addInventory("Dual Daggers");
            std::cout << "The following item has been added to your inventory :  Dual Daggers" << std::endl;
        }
    }
}

void battle(Player& player)
{
    int x = time(0);
    srand(x);
    std::string enemy[3];
    enemy[0] = "Orc";
    enemy[1] = "Goblin";
    enemy[2] = "Troll";
    std::string chosen_enemy = enemy[rand() % 3];
    int enemyHP=1;
    int enemyAttack=1;
    if (chosen_enemy == "Orc")
    {
        enemyHP = 150;
        enemyAttack = 75;
    }
    else if (chosen_enemy == "Goblin")
    {
        enemyHP = 60;
        enemyAttack = 40;
    }
    if (chosen_enemy == "Troll")
    {
        enemyHP = 200;
        enemyAttack = 100;
    }

    std::cout << "You've found a hostile " << chosen_enemy <<std::endl;
    std::cout << "The battle begins\n";

    while (player.getPlayerHP() > 0 && enemyHP > 0)
    {
        std::cout << "You dealt " << player.getPlayerAttack() << " damage to " << chosen_enemy<<std::endl;
        system("pause");
        enemyHP -= player.getPlayerAttack();
        if (enemyHP <= 0)
        {
            std::cout << "You've slain " << chosen_enemy <<std::endl;
            return;
        }
        std::cout << "The enemy has " << enemyHP << " health left" << std::endl;
        system("pause");
        std::cout <<chosen_enemy << " dealt " << enemyAttack << " damage to you"<<std::endl;
        system("pause");
        player.HPdamage(enemyAttack);
        if (player.getPlayerHP() <= 0)
        {
            std::cout << " You've lost the battle ! \n GAME OVER";
            exit(0);
        }
        std::cout << "You have " << player.getPlayerHP() << " health left" << std::endl;
        system("pause");
    }
}

int main()
{
    PlaySound(TEXT("Main_Menu.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    std::string play_game;
    intro();
    std::cin >> play_game;
    std::cout << std::endl;
    if (play_game != "YES")
    {
        std::cout << "You've quit the game\n";
        return 0;
    }
    PlaySound(TEXT("Exploring.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    Player player = setup();
    crossroads();
    
    chest(player);
    PlaySound(TEXT("BattleFinal.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    battle(player);

    std::cout << "Congratulations, you won the game !\n";
    return 0;
}


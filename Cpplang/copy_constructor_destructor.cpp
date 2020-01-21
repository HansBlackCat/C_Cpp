#include <iostream>
#include <string.h>

class Marine {
    int hp;
    int coord_x, coord_y;
    int damage;
    int atk_speed;
    bool is_dead;
    bool is_steam_pack;
    char* name;

    public:  
        Marine();
        Marine(int x, int y);
        Marine(int x, int y, const char* marine_name);

        int atk();
        void be_attacked(int damaged_earn);
        void move(int x, int y);
        void steam_pack();

        void show_status();
};

Marine::Marine() {
    hp = 40;
    coord_x = coord_y = 0;
    damage = 6;
    atk_speed = 15;
    is_dead = false;
    is_steam_pack = false;
    name = NULL;
}
Marine::Marine(int x, int y) {
    coord_x = x;
    coord_y = y;
    hp = 40;
    damage = 6;
    atk_speed = 15;
    is_dead = false;
    is_steam_pack = false;
}
Marine::Marine(int x, int y, const char* marine_name) {
    coord_x = x;
    coord_y = y;
    hp = 40;
    damage = 6;
    atk_speed = 15;
    is_dead = false;
    is_steam_pack = false;

    name = new char[strlen(marine_name)+1];
    strcpy(name, marine_name);
}
void Marine::move(int x, int y) {
    coord_x += x;
    coord_y += y;
}
int Marine::atk() { return damage; }
void Marine::be_attacked(int damage_earn) {
    hp -= damage_earn;
    if (hp <= 0) { Marine::is_dead = true; }
}
void Marine::steam_pack() {
    atk_speed = 9;
    be_attacked(10);
    is_steam_pack = true;
}
void Marine::show_status() {
    std::cout << "-- Marine --" << std::endl;
    std::cout << "Tag: " <<  name << std::endl;
    std::cout << "Loc: (" << coord_x << ", " << coord_y << ")" <<std::endl;
    std::cout << "Hp : " << hp << std::endl;
    std::cout << "Pak: " << is_steam_pack << std::endl;
}

int main() {
    /*
    Marine marine1(2,3);
    Marine marine2;

    marine1.show_status();
    marine2.show_status();

    marine1.steam_pack();
    marine2.move(10,8);
    marine2.move(-5,-3);

    marine1.be_attacked(10);
    marine2.be_attacked(marine1.atk());

    marine1.show_status();
    marine2.show_status();

    */
    /*
    Marine *marines[100];

    marines[0] = new Marine(2, 3);
    marines[1] = new Marine(3, 9);

    marines[0]->show_status();
    */
    Marine* marines[100];
    marines[0] = new Marine(2, 3, "Marine 2");
    marines[1] = new Marine(1, 5, "Marine 1");

    marines[0] -> show_status();
    marines[1] -> show_status();

    delete marines[0];
    delete marines[1];

    return 0;
   
}
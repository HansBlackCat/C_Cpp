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
        // Destructor
        ~Marine();
        // Copy Constructor
        Marine(const Marine& ma);

        int atk();
        //void be_attacked(int damaged_earn);
        Marine& be_attacked(int damage_earn); 
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
    name = NULL;
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
/*
void Marine::be_attacked(int damage_earn) {
    hp -= damage_earn;
    if (hp <= 0) { Marine::is_dead = true; }
}
*/
Marine& Marine::be_attacked(int d) {
    this -> hp -= d;
    if (hp <= 0) {
        hp = 0;
        is_dead = true;
    }
    return* this;
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
// Destructor
Marine::~Marine() {
    std::cout << "Destruction Active!: " << name << std::endl;
    if (name != NULL) { delete[] name; }
}
// Cpy Constructor
Marine::Marine(const Marine& ma) {
    std::cout << "<< Copy Protocol! >>" << std::endl;
    hp = ma.hp;
    damage = ma.damage;
    atk_speed = ma.atk_speed;
    is_dead = ma.is_dead;
    is_steam_pack = ma.is_steam_pack;
    coord_x = ma.coord_x * 0;
    coord_y = ma.coord_y * 0;

    name = new char[strlen(ma.name)+1];
    std::cout << "What is 'name': " << name << std::endl;
    strcpy(name, ma.name);
    std::cout << "What is 'name': " << name << std::endl;
}

class Cons_and_Des {
    char c;
    public: 
        Cons_and_Des(char _c) {
            c = _c;
            std::cout << "Cons " << c << std::endl;
        }
        ~Cons_and_Des() {
            std::cout << "Des " << c << std::endl;
        }
};
void simple_function() { Cons_and_Des dnc('d'); }

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
    Marine* marines[100];
    
    marines[0] = new Marine(2, 3, "Marine 2");
    marines[1] = new Marine(1, 5, "Marine 1");
    marines[2] = marines[1];

    marines[0] -> show_status();
    marines[1] -> show_status();

    marines[0] -> be_attacked(marines[1] -> atk());
    marines[1] -> steam_pack();

    marines[0] -> show_status();
    marines[1] -> show_status();
    marines[2] -> show_status();
    
    marines[3] = new Marine(*marines[1]);
    marines[3] -> show_status();

    delete marines[0];
    delete marines[1];
    // Shallow cpy
    // delete marines[2];
    // Deep cpy
    delete marines[3];

    /*
    Marine uarines[100];
    uarines[0] = Marine{2, 3, "Uarine 1"};
    uarines[0].show_status();
    */

    Marine marine1(0, 0, "KIM");
    Marine marine2(10, 10, "PARK");

    marine2.be_attacked(marine1.atk()).be_attacked(marine1.atk());

    marine1.show_status();
    marine2.show_status();

    Cons_and_Des cnd('c');
    simple_function();

    std::cout << "END_PROCESS" <<std::endl;
    return 0;
   
}
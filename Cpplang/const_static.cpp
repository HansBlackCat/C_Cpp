#include <iostream>

class Marine {
    static int TOTAL_MARINE_NUMBER;

    int hp;
    int coord_x, coord_y;
    const int damage;
    bool is_dead;


    public:  
        Marine();
        Marine(int x, int y);

        int attack();
        // void be_attacked(int damage_earn);
        Marine& be_attacked(int damage_earn);
        void move(int x, int y);
        void show_status();

        ~Marine() { TOTAL_MARINE_NUMBER--; }
};
int Marine::TOTAL_MARINE_NUMBER = 0;
Marine::Marine() : hp(45), coord_x(0), coord_y(0), damage(6), is_dead(false) { TOTAL_MARINE_NUMBER++; }
Marine::Marine(int x, int y) : hp(45), coord_x(x), coord_y(y), damage(6), is_dead(false) { TOTAL_MARINE_NUMBER++; }

void Marine::move(int x, int y) {
    coord_x += x;
    coord_y += y;
}
int Marine::attack() {
    return damage;
}
/*
void Marine::be_attacked(int t) {
    hp -= t;
    if (hp < 0) { 
        hp = 0;
        is_dead = true;
    }
}
*/
Marine& Marine::be_attacked(int damaged_earn) {
    hp -= damaged_earn;
    if (hp <= 0) is_dead = true;
    return *this;
}
void Marine::show_status() {
    std::cout << "-- Status --" << std::endl;
    std::cout << "hp  : " << hp << std::endl;
    std::cout << "loc : (" << coord_x << ", " << coord_y << ")" << std::endl;
    std::cout << "dmg : " << damage << std::endl;
    std::cout << "NUM : " << TOTAL_MARINE_NUMBER << std::endl;
}

int main() {
    Marine marine1(2, 3);
    marine1.show_status();
    
    Marine marine2(3, 5);
    marine2.show_status();

    marine1.be_attacked(marine2.attack());
    marine1.move(-10, -10);
    marine2.move(5, 20);

    marine1.show_status();
    marine2.show_status();

    marine2.be_attacked(100);
    
    marine1.show_status();
    marine2.show_status();
    return 0;
}
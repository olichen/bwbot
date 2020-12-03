#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

class ResourceHandler {
public:
    ResourceHandler();
    void next_frame();
    void add_worker() { mineral_workers.push_back(get_mineral_frames()); }
    void use_supply(int supply = 1) { s += supply; }
    void use_minerals(int minerals) { m -= minerals; }
    int minerals() const { return m; }
    int gas() const { return g; }
    int supply() const { return s; }
    int supply_max() const { return s_m; }
private:
    int mineral_patches = 9;
    int m = 50, g = 0;
    int s = 4, s_m = 10;
    const int MINERAL_FRAMES = 176;
    const int GAS_FRAMES = 111;
    vector <int> mineral_workers;
    vector <int> gas_workers;
    int get_mineral_frames() {
        int worker_count = mineral_workers.size();
        if (worker_count <= mineral_patches) return MINERAL_FRAMES;
        if (worker_count <= mineral_patches * 3) {
            return 144 + 32 * worker_count / mineral_patches;
        }
        return (240 * worker_count / mineral_patches * 3);
    }
};

std::ostream& operator<<(std::ostream& os, ResourceHandler& rh);

ResourceHandler::ResourceHandler() {
    mineral_workers.push_back(175);
    mineral_workers.push_back(176);
    mineral_workers.push_back(177);
}

void ResourceHandler::next_frame() {
    for (int &w : mineral_workers) {
        w--;
        if (w == 0) {
            m += 8;
            w = get_mineral_frames();
        }
    }
}

std::ostream& operator<<(std::ostream& os, ResourceHandler& rh) {
    os << "M" << setw(5) << rh.minerals() << " | G" << setw(5) << rh.gas();
    os << " | S" << setw(3) << rh.supply() << "/" << setw(3) << rh.supply_max() << endl;
    return os;
}

int main() {
    ResourceHandler rh;
    for (int i = 0; i < 1000; i++) {
        int s = i * 42 / 1000;
        cout << setw(4) << i << setw(4) << s << " : ";
        cout << rh;
        rh.next_frame();
        if (i % 300 == 0) {
            rh.add_worker();
            rh.use_supply();
            rh.use_minerals(50);
        }
    }
}

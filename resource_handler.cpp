#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

class ResourceHandler {
    int mineral_patches = 9;
    int minerals = 50, gas = 0;
    int supply = 4, supply_max = 10;
    const int MINERAL_FRAMES = 176;
    const int GAS_FRAMES = 111;
    vector <int> mineral_workers;
    vector <int> gas_workers;
public:
    ResourceHandler() {
        mineral_workers.push_back(173);
        mineral_workers.push_back(175);
        mineral_workers.push_back(177);
        mineral_workers.push_back(179);
    }
    void print() {
        cout << "M" << setw(5) << minerals << " | G" << setw(5) << gas;
        cout << " | S" << setw(3) << supply << "/" << setw(3) << supply_max << endl;
    }
    void next_frame() {
        for (int &w : mineral_workers) {
            w--;
            if (w == 0) {
                minerals += 8;
                w = get_mineral_frames();
            }
        }
    }
private:
    int get_mineral_frames() {
        int worker_count = mineral_workers.size();
        if (worker_count <= mineral_patches) return MINERAL_FRAMES;
        if (worker_count <= mineral_patches * 3) {
            return 144 + 32 * worker_count / mineral_patches;
        }
        return (240 * worker_count / mineral_patches * 3);
    }
};

int main() {
    ResourceHandler rh;
    for (int i = 0; i < 200; i++) {
        int s = i * 42 / 1000;
        cout << setw(4) << i << setw(4) << s << " : ";
        rh.print();
        rh.next_frame();
    }
}

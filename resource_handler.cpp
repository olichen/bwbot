#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

class ResourceHandler {
public:
    ResourceHandler();
    void next_frame();
    void add_worker() { mineral_workers.push_back(get_mineral_frames()); }
    void add_sup_max(int s = 8) { sup_max += s; }
    void use_sup(int s = 1) { sup += s; }
    void use_min(int m) { min -= m; } // check
    void use_gas(int g) { gas -= g; }
    int get_min() const { return min; }
    int get_gas() const { return gas; }
    int get_sup() const { return sup; }
    int get_sup_max() const { return sup_max; }
private:
    int min_count = 9;
    int min = 50, gas = 0;
    int sup = 4, sup_max = 10;
    const int MINERAL_FRAMES = 176;
    const int GAS_FRAMES = 111;
    vector <int> mineral_workers;
    vector <int> gas_workers;
    int get_mineral_frames() {
        int worker_count = mineral_workers.size();
        if (worker_count <= min_count) return MINERAL_FRAMES;
        if (worker_count <= min_count * 3) {
            return 144 + 32 * worker_count / min_count;
        }
        return (240 * worker_count / min_count * 3);
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
            min += 8;
            w = get_mineral_frames();
        }
    }
}

std::ostream& operator<<(std::ostream& os, ResourceHandler& rh) {
    os << "M" << setw(5) << rh.get_min() << " | G" << setw(5) << rh.get_gas();
    os << " | S" << setw(3) << rh.get_sup() << "/" << setw(3) << rh.get_sup_max();
    return os;
}

int main() {
    ResourceHandler rh;
    for (int i = 0; i < 1000; i++) {
        int s = i * 42 / 1000;
        cout << setw(4) << i << setw(4) << s << " : ";
        cout << rh << endl;
        rh.next_frame();
        if (i % 300 == 0) {
            rh.add_worker();
            rh.use_sup();
            rh.use_min(50);
        }
    }
}

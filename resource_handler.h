#include <vector>
#include "unit_stats.h"
#include "unit_name.h"
using namespace std;

// invariant: always positive?
class Resources {
public:
    int get_min() const { return min; }
    void use_min(int m) { min -= m; }
    void add_min(int m = 8) { min += m; }

    int get_gas() const { return gas; }
    void use_gas(int g) { gas -= g; }
    void add_gas(int g = 8) { gas += g; }

    int get_sup() const { return sup; }
    void use_sup(int s = 1) { sup += s; }

    int get_sup_max() const { return sup_max; }
    void add_sup_max(int s = 8) { sup_max += s; }
private:
    int min = 50, gas = 0;
    int sup = 4, sup_max = 10;
};

class ResourceHandler {
public:
    ResourceHandler();
    void next_frame();
    void add_worker() { min_workers.push_back(get_mineral_frames()); }
    void remove_worker();
    void print();

    bool can_build(UnitName un);
    void build_unit(UnitName un);
private:
    UnitStats unit_stats;
    Resources resources;
    int min_count = 9;
    vector <int> min_workers;
    vector <int> gas_workers;
    int get_mineral_frames();
};

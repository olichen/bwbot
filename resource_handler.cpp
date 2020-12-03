#include <iostream>
using namespace std;

class ResourceHandler {
    int mineral_patches = 0;
    int minerals = 50, gas = 0;
    int supply = 4, supply_max = 10;
public:
    ResourceHandler() {}
    void print() {
        cout << "M " << minerals << " G " << gas;
        cout << " S " << supply << "/" << supply_max << endl;
    }
};

int main() {
    ResourceHandler rh();
    rh.print();
}

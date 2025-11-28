#include <random>
#include <vector>
#include <cmath> // For sqrtf
using std::vector;

struct particles {
    vector<float> x, y, z;      // position
    vector<float> vx, vy, vz;   // velocity
    vector<float> ax, ay, az;   // acceleration
};

// Initial conditions
void ic(struct particles &plist, int n) {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<float> dis(0.0, 1.0);

    // Replace clear/reserve/push_back with resize on all vectors
    plist.x.resize(n);
    plist.y.resize(n);
    plist.z.resize(n);
    plist.vx.resize(n, 0.0f); // Resize and initialize to 0
    plist.vy.resize(n, 0.0f);
    plist.vz.resize(n, 0.0f);
    plist.ax.resize(n, 0.0f);
    plist.ay.resize(n, 0.0f);
    plist.az.resize(n, 0.0f);
    
    for( auto i=0; i<n; ++i) {
        // Use index access for initial positions
        plist.x[i] = dis(gen);
        plist.y[i] = dis(gen);
        plist.z[i] = dis(gen);
        // vx, vy, vz, ax, ay, az are initialized to 0.0f by the resize call
    }
}

void forces(struct particles &plist) {
    int n = plist.x.size(); // Use size of any vector
    for(int i=0; i<n; ++i) {
        float ax=0, ay=0, az=0;
        for(int j=0; j<n; ++j) {
            if (i==j) continue;
            
            // CRITICAL BUG FIX: must calculate distance between i and j
            auto dx = plist.x[j] - plist.x[i]; 
            auto dy = plist.y[j] - plist.y[i];
            auto dz = plist.z[j] - plist.z[i];
            
            auto r = sqrtf(dx*dx + dy*dy + dz*dz);
            auto ir3 = 1.0f / (r*r*r);
            ax += dx * ir3;
            ay += dy * ir3;
            az += dz * ir3;
        }
        plist.ax[i] = ax;
        plist.ay[i] = ay;
        plist.az[i] = az;
    }
}

int main(int argc, char *argv[]) {
    int N=50'000;
    struct particles plist;
    ic(plist,N);
    forces(plist);
    return 0;
}

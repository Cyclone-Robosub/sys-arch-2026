#include <chrono>
using namespace BT;
class WayptAbs : public RosActionNode<WayptAbs> {
    public:

    private:
        float64[6] currentPos;
        float64 startTime;
        float64 currentTime;
        bool isInTolerance = false;
}
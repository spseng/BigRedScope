#include <chrono>
#include <thread>
#include <fmt/format.h>
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>
#include <networktables/DoubleTopic.h>

int main() {
    auto inst = nt::NetworkTableInstance::GetDefault();
    auto table = inst.GetTable("datatable");
    auto xSub = table->GetDoubleTopic("DeltaTime").Subscribe(0.0);
    inst.StartClient4("example client");
    inst.SetServer("127.0.0.1");

    while (true) {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
        double x = xSub.Get();
        fmt::print("X: {}\n", x);
    }
}

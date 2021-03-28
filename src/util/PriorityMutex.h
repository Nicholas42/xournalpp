#pragma once

#include <mutex>
#include <thread>
#include <utility>

namespace Util {
struct PriorityMutex {

    using double_lock = std::pair<std::unique_lock<std::mutex>, std::unique_lock<std::mutex>>; 

    auto seniorLock() -> std::unique_lock<std::mutex>;
    auto juniorLock() -> std::unique_lock<std::mutex>;
    auto lowPriorityLock() -> double_lock;
private:
    std::mutex lowPriority;
    std::mutex nextAccess;
    std::mutex inner;
};
}  // namespace Util

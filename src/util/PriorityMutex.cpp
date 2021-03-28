#include "PriorityMutex.h"

namespace Util {
auto PriorityMutex::seniorLock() -> std::unique_lock<std::mutex> {
    std::lock_guard<std::mutex> lg{nextAccess};
    return std::unique_lock<std::mutex>{inner};
}

auto PriorityMutex::juniorLock() -> std::unique_lock<std::mutex> { return std::unique_lock<std::mutex>{lowPriority}; }


auto PriorityMutex::lowPriorityLock() -> double_lock {
    auto lowPriorityLock = juniorLock();
    return std::make_pair(std::move(lowPriorityLock), seniorLock());
}
}  // namespace Util

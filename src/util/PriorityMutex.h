/*
 * Xournal++
 *
 * Mutex implementing locking on two different priority levels.
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */
#pragma once

#include <mutex>
#include <thread>
#include <utility>

namespace Util {
struct PriorityMutex {

    using DoubleLock = std::pair<std::unique_lock<std::mutex>, std::unique_lock<std::mutex>>;

    /// Acquire a lock with priority. Guaranteed to by-pass all low-priority locking attempts except for maybe one. Will
    /// block until the lock can be acquired. Order of lock acquisitions of multiple prioritised locking attempts is
    /// unspecified.
    /// @return Lock protecting the shared resource.
    auto seniorLock() -> std::unique_lock<std::mutex>;

    /// Acquire a lock that blocks all other low-priority locking attempts. Blocks until this is possible. Prefer
    /// lowPriorityLock() to directly make a low-priority locking attempt. This method can be used to make a
    /// high-priority locking attempt low-priority by calling it before seniorLock().
    /// @return Lock blocking low-priority locking attempts. Should be held until the inner lock is released.
    auto juniorLock() -> std::unique_lock<std::mutex>;

    /// Make a low-priority locking attempt. Block until success.
    /// @return A pair of locks, the first blocking low-priority attempts and the second protecting the shared resource.
    auto lowPriorityLock() -> DoubleLock;

private:
    std::mutex lowPriority;
    std::mutex nextAccess;
    std::mutex inner;
};
}  // namespace Util

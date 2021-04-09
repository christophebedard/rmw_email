// Copyright 2020 Christophe Bedard
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef EMAIL__SAFE_QUEUE_HPP_
#define EMAIL__SAFE_QUEUE_HPP_

#include <mutex>
#include <queue>
#include <utility>

namespace email
{

/// Simple thread-safe queue.
/**
 * Note: probably not ideal.
 *
 * \tparam T the queue element type
 */
template<class T>
class SafeQueue
{
public:
  /// Constructor.
  SafeQueue()
  : queue_mutex_(),
    queue_()
  {}
  SafeQueue(const SafeQueue &) = delete;
  SafeQueue & operator=(const SafeQueue &) = delete;
  ~SafeQueue() {}

  bool
  empty() const
  {
    std::scoped_lock<std::mutex> lock(queue_mutex_);
    return queue_.empty();
  }

  void
  push(const T & element)
  {
    std::scoped_lock<std::mutex> lock(queue_mutex_);
    queue_.push(std::move(element));
  }

  void
  pop()
  {
    std::scoped_lock<std::mutex> lock(queue_mutex_);
    queue_.pop();
  }

  const T &
  front() const
  {
    std::scoped_lock<std::mutex> lock(queue_mutex_);
    return queue_.front();
  }

  const T
  dequeue()
  {
    const T message = front();
    pop();
    return message;
  }

private:
  mutable std::mutex queue_mutex_;
  std::queue<T> queue_;
};

}  // namespace email

#endif  // EMAIL__SAFE_QUEUE_HPP_

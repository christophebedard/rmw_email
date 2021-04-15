// Copyright 2021 Christophe Bedard
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

#ifndef EMAIL__SAFE_MAP_HPP_
#define EMAIL__SAFE_MAP_HPP_

#include <map>
#include <mutex>
#include <utility>

#include "email/macros.hpp"

namespace email
{

/// Simple thread-safe map.
/**
 * Note: probably not ideal.
 *
 * \tparam K the key element type
 * \tparam T the mapped element type
 */
template<class K, class T>
class SafeMap
{
public:
  /// Constructor.
  SafeMap()
  : map_mutex_(),
    map_()
  {}
  EMAIL_SHARED_PTR(SafeMap)

  ~SafeMap() {}

  void
  insert(std::pair<const K, T> && p)
  {
    std::scoped_lock<std::mutex> lock(map_mutex_);
    (void)map_.insert(std::move(p));
  }

  void
  erase(typename std::map<K, T>::const_iterator & it)
  {
    std::scoped_lock<std::mutex> lock(map_mutex_);
    (void)map_.erase(it);
  }

  typename std::map<K, T>::const_iterator
  find(const K & k) const
  {
    std::scoped_lock<std::mutex> lock(map_mutex_);
    return map_.find(k);
  }

  bool
  contains(const K & k) const
  {
    std::scoped_lock<std::mutex> lock(map_mutex_);
    return map_.find(k) != map_.cend();
  }

  std::pair<typename std::map<K, T>::const_iterator, typename std::map<K, T>::const_iterator>
  equal_range(const K & k) const
  {
    std::scoped_lock<std::mutex> lock(map_mutex_);
    return map_.equal_range(k);
  }

  typename std::map<K, T>::const_iterator
  cend() const noexcept
  {
    std::scoped_lock<std::mutex> lock(map_mutex_);
    return map_.cend();
  }

private:
  EMAIL_DISABLE_COPY(SafeMap)

  mutable std::mutex map_mutex_;
  std::map<K, T> map_;
};

}  // namespace email

#endif  // EMAIL__SAFE_MAP_HPP_

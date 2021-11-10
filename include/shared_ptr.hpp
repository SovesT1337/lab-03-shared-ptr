// Copyright by SovesT 2021
// Created by sovest on 07.11.2021.
//

#ifndef INCLUDE_SHARED_PTR_HPP_
#define INCLUDE_SHARED_PTR_HPP_

#include <atomic>
#include <iostream>
#include <utility>

template <typename T>
class SharedPtr {
 private:
  T* data;
  std::atomic_uint* n;

 public:
  SharedPtr() {
    data = nullptr;
    n = nullptr;
  }

  explicit SharedPtr(T* ptr) {
    data = ptr;
    n = new std::atomic_uint(1);
  }

  SharedPtr(const SharedPtr& r) {
    data = r.data;
    n = r.n;
    if (r.data != nullptr) (*this->n)++;
  }

  SharedPtr(SharedPtr&& r) noexcept {
    if (data != r.data) {
      data = std::move(r.data);
      n = std::move(r.n);
    }
  }

  ~SharedPtr() {
    if (n) {
      if (*n == 1) {
        delete n;
        delete data;
      } else {
        (*n)--;
      }
    }
  }

  auto operator=(const SharedPtr& r) -> SharedPtr& {
    if (data == r.data) return *this;
    data = r.data;
    n = r.n;
    if (r.data != nullptr) (*this->n)++;
    return *this;
  }

  auto operator=(SharedPtr&& r) noexcept -> SharedPtr& {
    if (data == r.data) return *this;
    data = std::move(r.data);
    n = std::move(r.n);
    return *this;
  }

  // проверяет, указывает ли указатель на объект
  explicit operator bool() { return (data != nullptr); }

  auto operator*() const -> T& { return *data; }

  auto operator->() const -> T* { return data; }

  auto get() -> T* { return data; }

  void reset() {
    (*n)--;
    if (*n == 0) {
      delete data;
      delete n;
    }
    data = nullptr;
    n = nullptr;
  }

  void reset(T* ptr) {
    if (ptr != data) {
      (*n)--;
      if (*n == 0) {
        delete data;
        delete n;
      }
      data = ptr;
      n = new std::atomic_uint(1);
    }
  }

  void swap(SharedPtr& r) {
    T* s = data;
    std::atomic_uint* k = n;
    data = r.data;
    n = r.n;
    r.data = s;
    r.n = k;
  }

  // возвращает количество объектов SharedPtr, которые ссылаются на тот же
  // управляемый объект
  auto use_count() const -> size_t { return *n; }
};

#endif  // INCLUDE_SHARED_PTR_HPP_

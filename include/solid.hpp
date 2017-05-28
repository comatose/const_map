#ifndef __SOLID_HPP
#define __SOLID_HPP

#include <array>
#include <utility>
#include <iostream>
#include <algorithm>

namespace solid {

template<class T>
constexpr void swap(T& a, T& b) {
    T tmp = std::move(b);
    b = std::move(a);
    a = std::move(tmp);
}

template<class InputIt, class OutputIt>
constexpr OutputIt copy(InputIt begin, InputIt end, OutputIt dst) {
    while(begin != end)
        *(dst++) = *(begin++);
    return dst;
}

template<class T>
constexpr T partition(T begin, T end){
    --end;
    T it = begin;
    for(; it != end; ++it){
        if(*it < *end){
            swap(*it, *begin);
            begin++;
        }
    }
    swap(*begin, *end);
    return begin;
}

template<class T>
constexpr void quick_sort(T begin, T end){
    if(begin >= end) return;

    T pivot = partition(begin, end);
    quick_sort(begin, pivot);
    quick_sort(pivot + 1, end);
}

template<class T>
constexpr T quick_sort(T a) {
    quick_sort(a.begin(), a.end());
    return a;
}

template<class T, class V>
constexpr T binary_search(T begin, T end, const V& value){
    T notfound = end;
    while(begin < end){
        T mid = begin + (end - begin) / 2;
        if(*mid == value)
            return mid;
        else if(*mid < value)
            begin = mid + 1;
        else
            end = mid;
    }
    return notfound;
}

template<typename T, std::size_t N>
class array {
  public:
    using iterator = T*;
    using const_iterator = const T*;

    constexpr array() = default;

    constexpr array(const array& other) {
        copy(other.cbegin(), other.cend(), begin());
    }

    constexpr array(std::initializer_list<T> init) {
        copy(init.begin(), init.end(), begin());
    }

    constexpr std::size_t size() const {
        return N;
    }

    constexpr T& operator[](std::size_t i) {
        return elements_[i];
    }

    constexpr const T& operator[](std::size_t i) const {
        return elements_[i];
    }

    constexpr iterator begin() {
        return &elements_[0];
    }

    constexpr iterator end() {
        return &elements_[N];
    }

    constexpr const_iterator begin() const {
        return &elements_[0];
    }

    constexpr const_iterator end() const {
        return &elements_[N];
    }

    constexpr const_iterator cbegin() const {
        return &elements_[0];
    }

    constexpr const_iterator cend() const {
        return &elements_[N];
    }

  private:
    T elements_[N]{};
};

template<typename Key, std::size_t N>
class ordered_set : public array<Key, N> {
    using base_type = array<Key, N>;
  public:
    using iterator = Key*;
    using const_iterator = const Key*;

    using base_type::begin;
    using base_type::end;
    using base_type::cbegin;
    using base_type::cend;
    using base_type::size;
    using base_type::operator[];

    constexpr ordered_set() = default;

    constexpr ordered_set(const ordered_set& other)
    : base_type(other) {
        quick_sort(begin(), end());
    }

    constexpr ordered_set(std::initializer_list<Key> init)
    : base_type(init) {
        quick_sort(begin(), end());
    }

    constexpr iterator find(const Key& k) {
        return binary_search(begin(), end(), k);
    }

    constexpr const_iterator find(const Key& k) const {
        return binary_search(cbegin(), cend(), k);
    }
};

}
#endif // __SOLID_HPP

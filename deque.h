#include <type_traits>
#include <algorithm>
#include <vector>
#include <cassert>
template <typename T1, typename T2>
struct Pair {
    T1 first;
    T2 second;
};

template <typename T>
struct Deque {
    std::vector<std::vector<Pair<std::vector<T>, std::size_t> > > data =
        decltype(data)({{{{}, 0}}, {{{}, 1}}, {{{}, 2}}, {{{}, 3}}});
    struct locals {
        std::size_t first;
        std::size_t second;
        std::size_t size;
        std::vector<Pair<std::vector<T>, std::size_t>>* start;
    };
    std::vector<locals> fragment = decltype(fragment)({{0, 0, data.size(), data.data()}});
    size_t size() const {
        return fragment[0].second - fragment[0].first & data.size() - 1;
    }
    void rotate(){
        fragment[0].first &= data.size() - 1;
        std::rotate(data.begin(), data.begin() + fragment[0].first, data.end());
        fragment[0].second -= fragment[0].first;
        fragment[0].first -= fragment[0].first;
        fragment[0].second &= data.size() - 1;
    }
    void update(){
        fragment[0].start = data.data();
        fragment[0].size = data.size();
        for (size_t q = 0; q < data.size(); ++q) {
            data[q].resize(1);
            data[q][0].second = q;
        }
    }
    void increase_mem(size_t mem) {
        assert(data.size());

        size_t shift = 0;
        while (data.size() << shift < mem) {
            shift++;
        }

        if (shift) {
            rotate();
            data.resize(data.size() << shift);
            update();
        }
    }
    template <typename... Y>
    void push_near(size_t& place, Y&&... val) {
        increase_mem(size() + 5);
        size_t local_place = place;
        if (&place == &fragment[0].first) {
            local_place -= 1;
        }
        // assert(not data[local_place & data.size() - 1][0].first.size());
        data[local_place & data.size() - 1][0].first.emplace_back(std::forward<Y>(val)...);
        if (&place == &fragment[0].second) {
            local_place += 1;
        }
        place = local_place;
    }
    void pop_near(size_t& place) {
        if (&place == &fragment[0].second) {
            place -= 1;
        }
        // assert(data[place & data.size() - 1][0].first.size());
        data[place & data.size() - 1][0].first.pop_back();
        if (&place == &fragment[0].first) {
            place += 1;
        }
    }
    T& operator[](size_t index) {
        return data[fragment[0].first + index & data.size() - 1][0].first[0];
    }
    const T& operator[](size_t index) const {
        return data[fragment[0].first + index & data.size() - 1][0].first[0];
    }
    template <typename Y, typename U>
    using copy_const = std::conditional_t<std::is_same_v<Y, const T>, const U, U>;
    template <typename Y>
    struct iterator_s {
        using difference_type = std::ptrdiff_t;
        using value_type = Y;
        using pointer = Y*;
        using reference = Y&;
        using iterator_category = std::random_access_iterator_tag;
        copy_const<Y, locals>* fragment = nullptr;
        copy_const<Y, Pair<std::vector<T>, std::size_t>>* item = nullptr;
        Y& operator*() {
            return item->first[0];
        }
        Y& operator*() const{
            return item->first[0];
        }
        void add(size_t offset) {
            item = fragment->start[item->second + offset & fragment->size - 1].data();
        }
        auto& operator+=(size_t offset) {
            add(offset);
            return *this;
        }
        auto& operator-=(size_t offset) {
            return (*this) += -offset;
        }
        auto& operator++() {
            return (*this) += 1;
        }
        auto& operator--() {
            return (*this) -= 1;
        }
        auto operator++(int) {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }
        auto operator--(int) {
            auto tmp = *this;
            --(*this);
            return tmp;
        }
        auto& operator[](size_t index) {
            auto tmp = *this;
            tmp += index;
            return *tmp;
        }
        auto& operator[](size_t index) const {
            auto tmp = *this;
            tmp += index;
            return *tmp;
        }
        size_t index() const {
            return item->second - fragment->first + 2 & fragment->size - 1;
        }
        ssize_t sub(const iterator_s& oth) const {
            return index() - oth.index();
        }
        operator iterator_s<const T>() const {
            return {fragment, item};
        }
        auto operator->() const {
            return &**this;
        }
        auto operator->() {
            return &**this;
        }
    };
    using iterator = iterator_s<T>;
    using const_iterator = iterator_s<const T>;
    template <typename Y>
    using is_iterator = std::enable_if_t<
        std::is_same_v<typename Deque<std::remove_const_t<typename Y::value_type>>::iterator, Y> or
            std::is_same_v<typename Deque<std::remove_const_t<typename Y::value_type>>::const_iterator, Y>,
        void>;
    template <typename Y = T>
    void push_back(Y&& val) {
        push_near(fragment[0].second, std::forward<Y>(val));
    }
    template <typename Y = T>
    void push_front(Y&& val) {
        push_near(fragment[0].first, std::forward<Y>(val));
    }
    void pop_back() {
        pop_near(fragment[0].second);
    }
    void pop_front() {
        pop_near(fragment[0].first);
    }
    auto begin() {
        return iterator{fragment.data(), data[fragment[0].first & data.size() - 1].data()};
    }
    auto cbegin() const {
        return const_iterator{fragment.data(), data[fragment[0].first & data.size() - 1].data()};
    }
    auto begin() const {
        return const_iterator{fragment.data(), data[fragment[0].first & data.size() - 1].data()};
    }
    auto rbegin() {
        return std::reverse_iterator(end());
    }
    auto crbegin() const {
        return std::reverse_iterator(end());
    }
    auto rbegin() const {
        return std::reverse_iterator(end());
    }
    auto end() {
        return begin() + size();
    }
    auto cend() const {
        return cbegin() + size();
    }
    auto end() const {
        return begin() + size();
    }
    auto rend() {
        return std::reverse_iterator(begin());
    }
    auto crend() const {
        return std::reverse_iterator(begin());
    }
    auto rend() const {
        return std::reverse_iterator(begin());
    }
    template <typename Y = T>
    void insert(const_iterator iter, Y&& val) {
        size_t index = iter - cbegin();
        push_back(std::forward<Y>(val));
        if (index!=size()-1) {
            rotate();
            std::rotate(data.begin()+index, data.begin() + size()-1, data.begin() + size());
            update();
        }
    }
    void erase(const_iterator iter) {
        size_t index = iter - cbegin();
        rotate();
        if (index != size()) {
            std::rotate(data.begin() + index, data.begin() + index + 1, data.begin() + size());
        }
        update();
        pop_back();
    }
    Deque() = default;
    Deque(Deque&& oth) : data(std::move(oth.data)), fragment(std::move(oth.fragment)) {
        std::destroy_at(&oth);
        // std::construct_at(&oth);
        new(&oth)Deque();
    }
    Deque(const Deque& oth) : data(oth.data), fragment(oth.fragment) {
        update();
    }
    auto& operator=(const Deque& oth) {
        if (&oth != this) {
            std::destroy_at(this);
            // std::construct_at(this, oth);
            new(this)Deque(oth);
        }
        return *this;
    }
    auto& operator=(Deque&& oth) {
        if (&oth != this) {
            std::destroy_at(this);
            // std::construct_at(this, std::move(oth));
            new(this)Deque(std::move(oth));
        }
        return *this;
    }
    template <typename Y = T>
    Deque(size_t len, Y&& val) {
        increase_mem(len + 4);
        for (size_t q = 0; q < len; ++q) {
            push_near(fragment[0].second, std::forward<Y>(val));
        }
    }
    Deque(size_t len) {
        increase_mem(len + 4);
        for (size_t q = 0; q < len; ++q) {
            push_near(fragment[0].second);
        }
    }
    auto& at(size_t index) {
        if (index >= size()) {
            throw std::out_of_range("");
        }
        return (*this)[index];
    }
    auto& at(size_t index) const {
        if (index >= size()) {
            throw std::out_of_range("");
        }
        return (*this)[index];
    }
};

template <typename Y, typename = typename Deque<typename Y::value_type>::template is_iterator<Y>>
auto operator-(const Y& l, const Y& r) {
    return l.sub(r);
}
template <typename Y, typename = typename Deque<typename Y::value_type>::template is_iterator<Y>>
auto operator<(const Y& l, const Y& r) {
    return l.sub(r) < 0;
}
template <typename Y, typename = typename Deque<typename Y::value_type>::template is_iterator<Y>>
auto operator>(const Y& l, const Y& r) {
    return l.sub(r) > 0;
}
template <typename Y, typename = typename Deque<typename Y::value_type>::template is_iterator<Y>>
auto operator<=(const Y& l, const Y& r) {
    return l.sub(r) <= 0;
}
template <typename Y, typename = typename Deque<typename Y::value_type>::template is_iterator<Y>>
auto operator>=(const Y& l, const Y& r) {
    return l.sub(r) >= 0;
}
template <typename Y, typename = typename Deque<typename Y::value_type>::template is_iterator<Y>>
auto operator==(const Y& l, const Y& r) {
    return l.sub(r) == 0;
}
template <typename Y, typename = typename Deque<typename Y::value_type>::template is_iterator<Y>>
auto operator!=(const Y& l, const Y& r) {
    return l.sub(r) != 0;
}

template <typename Y, typename = typename Deque<typename Y::value_type>::template is_iterator<Y>>
auto operator+(const Y& l, size_t off) {
    auto tmp = l;
    tmp += off;
    return tmp;
}
template <typename Y, typename = typename Deque<typename Y::value_type>::template is_iterator<Y>>
auto operator+(size_t off, const Y& l) {
    auto tmp = l;
    tmp += off;
    return tmp;
}
template <typename Y, typename = typename Deque<typename Y::value_type>::template is_iterator<Y>>
auto operator-(const Y& l, size_t off) {
    auto tmp = l;
    tmp -= off;
    return tmp;
}
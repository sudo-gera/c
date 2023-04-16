#include <memory>

template <size_t N>
struct StackStorage {
    char stack_[N];
    size_t start_elem_index_ = 0;
    StackStorage(const StackStorage& stack) = delete;
    StackStorage() = default;
    static constexpr size_t len = N;
};

template <typename T, size_t N>
struct StackAllocator {
    StackStorage<N>* storage;

    template <typename Y>
    StackAllocator(const StackAllocator<Y, N>& allocator) : storage(allocator.storage){};

    explicit StackAllocator(StackStorage<N>& stackstorage) : storage(&stackstorage){};

    void deallocate(T*, size_t) {
    }

    template <typename U>
    struct rebind {
        using other = StackAllocator<U, N>;
    };

    T* allocate(size_t n) {
        auto o = storage->start_elem_index_;
        auto mod = reinterpret_cast<intptr_t>(storage->stack_ + storage->start_elem_index_) % alignof(T);
        if (mod) {
            storage->start_elem_index_ += alignof(T) - mod;
        }
        auto r = storage->stack_ + storage->start_elem_index_;
        storage->start_elem_index_ += sizeof(T) * n;
        if (storage->start_elem_index_ >= N) {
            storage->start_elem_index_ = o;
            throw std::runtime_error("");
        }
        return reinterpret_cast<T*>(r);
    }

    using value_type = T;
};

template <typename T, typename Y, size_t N>
bool operator==(const StackAllocator<T, N>& left, const StackAllocator<Y, N>& right) {
    return left.storage == right.storage;
}

template <typename T, typename Y, size_t N>
bool operator!=(const StackAllocator<T, N>& left, const StackAllocator<Y, N>& right) {
    return left.storage != right.storage;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
auto is_all_moved_on_c_f(T*)
    -> std::conditional_t<true, std::true_type, decltype(T().select_on_container_copy_construction())>;
template <typename T>
auto is_all_moved_on_c_f(...) -> std::false_type;
template <typename T>
auto is_all_moved_on_a_f(T*) -> typename T::propagate_on_container_copy_assignment;
template <typename T>
auto is_all_moved_on_a_f(...) -> std::true_type;

template <typename A, typename poc, typename poa>
struct AllWrapperImpl {};

template <typename A>
struct AllWrapperImpl<A, std::true_type, std::true_type> : A {
    auto& get_all() {
        return *reinterpret_cast<A*>(this);
    }
    auto& get_all() const {
        return *const_cast<A*>(reinterpret_cast<const A*>(this));
    }
    AllWrapperImpl(const AllWrapperImpl& oth) : A(oth.get_all().select_on_container_copy_construction()) {
    }
    auto& operator=(const AllWrapperImpl& oth) {
        get_all() = oth.get_all();
        return *this;
    }
    explicit AllWrapperImpl(A a) : A(std::forward<A>(a)) {
    }
    AllWrapperImpl() = default;
};

template <typename A>
struct AllWrapperImpl<A, std::true_type, std::false_type> : A {
    auto& get_all() {
        return *reinterpret_cast<A*>(this);
    }
    auto& get_all() const {
        return *const_cast<A*>(reinterpret_cast<const A*>(this));
    }
    AllWrapperImpl(const AllWrapperImpl& oth) : A(oth.get_all().select_on_container_copy_construction()) {
    }
    auto& operator=(const AllWrapperImpl&) {
        return *this;
    }
    explicit AllWrapperImpl(A a) : A(std::forward<A>(a)) {
    }
    AllWrapperImpl() = default;
};

template <typename A>
struct AllWrapperImpl<A, std::false_type, std::true_type> : A {
    auto& get_all() {
        return *reinterpret_cast<A*>(this);
    }
    auto& get_all() const {
        return *const_cast<A*>(reinterpret_cast<const A*>(this));
    }
    AllWrapperImpl(const AllWrapperImpl& oth) : A(oth.get_all()) {
    }
    auto& operator=(const AllWrapperImpl& oth) {
        get_all() = oth.get_all();
        return *this;
    }
    explicit AllWrapperImpl(A a) : A(std::forward<A>(a)) {
    }
    AllWrapperImpl() = default;
};

template <typename A>
struct AllWrapperImpl<A, std::false_type, std::false_type> : A {
    auto& get_all() {
        return *reinterpret_cast<A*>(this);
    }
    auto& get_all() const {
        return *const_cast<A*>(reinterpret_cast<const A*>(this));
    }
    AllWrapperImpl(const AllWrapperImpl& oth) : A(oth.get_all()) {
    }
    auto& operator=(const AllWrapperImpl&) {
        return *this;
    }
    explicit AllWrapperImpl(A a) : A(std::forward<A>(a)) {
    }
    AllWrapperImpl() = default;
};

template <typename A>
using all_wrapper = AllWrapperImpl<A, std::integral_constant<bool, decltype(is_all_moved_on_c_f<A>(nullptr))::value>,
                                   std::integral_constant<bool, decltype(is_all_moved_on_a_f<A>(nullptr))::value>>;

struct Node {
    Node* next = nullptr;
    Node* prev = nullptr;
};

template <typename T, typename Allocator = std::allocator<T>>
struct List : all_wrapper<Allocator>, Node {
    struct RealNode : Node {
        T val_;
    };
    size_t size_ = 0;
    auto size() const {
        return size_;
    }
    auto& get_allocator() const {
        return *static_cast<Allocator*>(const_cast<List*>(this));
    }
    List(List&& oth)
        : all_wrapper<Allocator>(reinterpret_cast<all_wrapper<Allocator>&&>(oth))
        , Node(static_cast<Node&&>(oth))
        , size_(oth.size_) {
        if (&oth != this) {
            oth.prev = &oth;
            oth.next = &oth;
            oth.size_ = 0;
            if (size_) {
                next->prev = this;
                prev->next = this;
            } else {
                next = this;
                prev = this;
            }
        }
    }
    List(const List& oth)
        : all_wrapper<Allocator>(reinterpret_cast<const all_wrapper<Allocator>&>(oth)), Node({this, this}), size_(0) {
        try {
            for (auto& w : oth) {
                push_back(w);
            }
        } catch (...) {
            this->~List();
            throw;
        }
    }
    List() {
        next = this;
        prev = this;
    }
    explicit List(size_t n) : Node({this, this}), size_(0) {
        try {
            for (size_t q = 0; q < n; ++q) {
                emplace(end());
            }
        } catch (...) {
            this->~List();
            throw;
        }
    }
    explicit List(Allocator a) : all_wrapper<Allocator>(a), Node({this, this}), size_(0) {
    }
    List(size_t n, Allocator a) : all_wrapper<Allocator>(a), Node({this, this}), size_(0) {
        for (size_t q = 0; q < n; ++q) {
            emplace(end());
        }
    }
    ~List() {
        while (size()) {
            pop_back();
        }
    }
    auto& operator=(const List& oth) {
        auto tmp = oth;
        std::swap(*this, tmp);
        *reinterpret_cast<all_wrapper<Allocator>*>(this) = *reinterpret_cast<const all_wrapper<Allocator>*>(&oth);
        return *this;
    }
    auto& operator=(List&& oth) {
        if (this != &oth) {
            this->~List();
            new (this) List(std::move(oth));
        }
        return *this;
    }
    template <typename C>
    struct Iter {
        using non_const_value_type = T;
        using value_type = C;
        using allocator = Allocator;
        using difference_type = std::ptrdiff_t;
        using pointer = C*;
        using reference = C&;
        using iterator_category = std::bidirectional_iterator_tag;
        Node* n = nullptr;
        auto& operator++() {
            n = n->next;
            return *this;
        }
        auto& operator--() {
            n = n->prev;
            return *this;
        }
        auto operator++(int) {
            auto tmp = *this;
            ++*this;
            return tmp;
        }
        auto operator--(int) {
            auto tmp = *this;
            --*this;
            return tmp;
        }
        C& operator*() {
            return reinterpret_cast<RealNode*>(n)->val_;
        }
        C& operator*() const {
            return reinterpret_cast<RealNode*>(n)->val_;
        }
        operator Iter<const T>() const {
            return {n};
        }
    };
    using iterator = Iter<T>;
    using const_iterator = Iter<const T>;
    using reverse_iterator = std::reverse_iterator<Iter<T>>;
    using const_reverse_iterator = std::reverse_iterator<Iter<const T>>;
    auto end() {
        return Iter<T>{this};
    }
    auto cend() const {
        return Iter<const T>{const_cast<List*>(this)};
    }
    auto end() const {
        return cend();
    }
    auto begin() {
        return ++end();
    }
    auto cbegin() const {
        return ++cend();
    }
    auto begin() const {
        return cbegin();
    }

    auto rend() {
        return std::reverse_iterator(begin());
    }
    auto crend() const {
        return std::reverse_iterator(cbegin());
    }
    auto rend() const {
        return crend();
    }
    auto rbegin() {
        return std::reverse_iterator(end());
    }
    auto crbegin() const {
        return std::reverse_iterator(cend());
    }
    auto rbegin() const {
        return crbegin();
    }

    template <typename Y, typename... U>
    void emplace(Y ptr, U&&... val) {
        auto c = ptr.n;
        --ptr;
        auto a = ptr.n;
        auto b = a;
        typename std::allocator_traits<Allocator>::template rebind_alloc<RealNode> all(get_allocator());
        auto b_ptr = all.allocate(1);
        try {
            b = new (b_ptr) RealNode{{}, std::forward<U>(val)...};
        } catch (...) {
            all.deallocate(reinterpret_cast<RealNode*>(b_ptr), 1);
            throw;
        }
        b->next = c;
        b->prev = a;
        c->prev = b;
        a->next = b;
        ++size_;
    }
    template <typename Y, typename U = T>
    void insert(Y ptr, U&& val) {
        emplace(ptr, std::forward<U>(val));
    }
    template <typename Y>
    void erase(Y ptr) {
        auto b = ptr.n;
        ++ptr;
        auto c = ptr.n;
        --ptr;
        --ptr;
        auto a = ptr.n;
        typename std::allocator_traits<Allocator>::template rebind_alloc<RealNode> all(get_allocator());
        reinterpret_cast<RealNode*>(b)->~RealNode();
        all.deallocate(reinterpret_cast<RealNode*>(b), 1);
        c->prev = a;
        a->next = c;
        --size_;
    }
    template <typename U = T>
    void push_back(U&& val) {
        insert(end(), std::forward<U>(val));
    }
    template <typename U = T>
    void push_front(U&& val) {
        insert(begin(), std::forward<U>(val));
    }
    void pop_back() {
        erase(std::prev(end()));
    }
    void pop_front() {
        erase(begin());
    }
    template <typename Y>
    using is_iterator =
        std::enable_if_t<std::is_same_v<std::decay_t<Y>, Iter<T>> or std::is_same_v<std::decay_t<Y>, Iter<const T>>,
                         void>;
};

template <typename T,
          typename = typename List<typename T::non_const_value_type, typename T::allocator>::template is_iterator<T>>
bool operator==(const T& left, const T& right) {
    return left.n == right.n;
}

template <typename T,
          typename = typename List<typename T::non_const_value_type, typename T::allocator>::template is_iterator<T>>
bool operator!=(const T& left, const T& right) {
    return left.n != right.n;
}

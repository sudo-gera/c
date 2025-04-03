#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <liburing.h>

#include <tuple>
#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <concepts>
#include <deque>
#include <vector>

#if __cplusplus < 202000L
#error "need c++20"
#endif

#define FORWARD(arg) std::forward<decltype(arg)>(arg)

#define LIBURING(expr) (([&](){ auto res__ = (expr) ; if (res__ < 0) { throw std::runtime_error{std::string() + "ERROR: " + #expr + ": " + strerror(-res__)} ; } ; return res__ ; })())
#define SYSCALL(expr) (([&](){ auto res__ = (expr) ; if (errno) { throw std::runtime_error{std::string() + "ERROR: " + #expr + ": " + strerror(errno)} ; } ; return res__ ; })())

struct MakeZero{
    template<typename T>
    operator T(){
        T val;
        memset(&val, 0, sizeof(val));
        return val;
    }
};

volatile auto memset_s = memset;

void assert_f(auto&& cond){
    if (not static_cast<bool>(cond)){
        memset_s(nullptr, 0, 1);
    }
}

#ifdef assert
#undef assert
#endif
#define assert assert_f

#define ZERO MakeZero()

// template<typename R, typename...A>
// struct BaseFuncStorage{
//     virtual R operator()(A...a) = 0;
//     virtual ~BaseFuncStorage()=default;
// };

// template<typename L, typename R, typename...A>
// struct FuncStorage:BaseFuncStorage<R,A...>{
//     L val;
//     FuncStorage(L&& val):val(FORWARD(val)){}
//     R operator()(A...a) override {
//         return val(FORWARD(a)...);
//     }
// };

// template<typename T>
// struct Function;

// template<typename R, typename...A>
// struct Function<R(A...)>{
//     std::unique_ptr<BaseFuncStorage<R,A...>> ptr = nullptr;

//     template<typename L>
//     Function(L&&l){
//         ptr = std::make_unique<FuncStorage<L,R,A...>>(FORWARD(l));
//     }
//     R operator()(A...a){
//         auto& tmp = *ptr;
//         return tmp(FORWARD(a)...);
//     }
// };

template<typename T>
struct NonOwningFunction;

template<typename R, typename...A>
struct NonOwningFunction<R(A...)>{
    std::pair<R(*)(void*, A...), void*> * data;
    R operator()(A...a){
        data->first(data->second, FORWARD(a)...);
    }
};

static off_t get_file_size(int fd) {
    struct stat st = ZERO;
    SYSCALL(fstat(fd, &st));
    return st.st_size;
}

struct io_uring_cqe* CQ_get_nowait(struct io_uring *ring){
    struct io_uring_cqe* cqe = nullptr;
    LIBURING(([&](){
        int ret = io_uring_peek_cqe(ring, &cqe);
        if (ret == -EAGAIN){
            cqe = nullptr;
            ret = 0;
        }
        return ret;
    })());
    return cqe;
}

struct io_uring_cqe* CQ_get_wait(struct io_uring *ring){
    struct io_uring_cqe* cqe = nullptr;
    LIBURING(io_uring_wait_cqe(ring, &cqe));
    return cqe;
}


template<typename T>
struct Heap{
    struct Record{
        T val;
        typename std::list<Record>::iterator iter;
    };
    std::list<Record> data;
    void* put(T&&val){
        auto iter = data.emplace(
            data.end(),
            Record{FORWARD(val), (typename std::list<Record>::iterator())}
        );
        iter->iter = iter;
        typename std::list<Record>::iterator* res = &iter->iter;
        assert(res != nullptr);
        return res;
    }
    T& get(void* ptr){
        assert(ptr);
        auto iter = *(typename std::list<Record>::iterator*)ptr;
        return iter->val;
    }
    void del(void* ptr){
        auto iter = *(typename std::list<Record>::iterator*)ptr;
        data.erase(iter);
    }
};

template<typename T>
struct Pointer{
    std::array<T, 1> val;
    operator T&(){
        return val[0];
    }
    operator T*(){
        return &val[0];
    }
    T* operator->(){
        return &val[0];
    }
};

#define QUEUE_SIZE 256

struct UringLoop{
    Pointer<struct io_uring> ring;
    struct io_uring_sqe* sqe_to_use = nullptr;
    size_t objects_in_queue_count = 0;
    UringLoop(){
        LIBURING(io_uring_queue_init(QUEUE_SIZE, ring, 0));
    }
    template<bool op_num>
    void async_rw(int fd, char* buf, unsigned len, uint64_t pos_in_file, NonOwningFunction<void(struct io_uring_cqe*)> callback){
        auto sqe = peek_sqe();
        consume_sqe();
        assert(sqe);
        io_uring_sqe_set_data(
            sqe,
            callback.data
        );
        if constexpr(op_num){
            io_uring_prep_write(sqe, fd, buf, len, pos_in_file);
        }else{
            io_uring_prep_read(sqe, fd, buf, len, pos_in_file);
        }
    }
    struct io_uring_sqe* peek_sqe(){
        if (not sqe_to_use){
            sqe_to_use = io_uring_get_sqe(ring);
        }
        return sqe_to_use;
    }
    void consume_sqe(){
        assert(sqe_to_use);
        sqe_to_use = nullptr;
        objects_in_queue_count += 1;
    }
    bool can_schedule(){
        return objects_in_queue_count < QUEUE_SIZE and peek_sqe();
    }
    void loop(){
        while (objects_in_queue_count){
            io_uring_submit(ring);
            struct io_uring_cqe* cqe = CQ_get_wait(ring);
            assert(cqe != nullptr);
            auto data = io_uring_cqe_get_data(cqe);
            assert(data);
            (NonOwningFunction<void(struct io_uring_cqe*)>{(std::pair<void (*)(void *, io_uring_cqe *), void *> *)data})(cqe);
            io_uring_cqe_seen(ring, cqe);
            objects_in_queue_count -= 1;
        }
    }
    ~UringLoop(){
        io_uring_queue_exit(ring);
    }
};

template<typename T, size_t N>
struct BoundVector{
    std::array<T, N> data_;
    size_t size_;
    size_t size(){
        return size_;
    }
    size_t capacity(){
        return data_.size();
    }
    T* data(){
        return data_.data();
    }
    void resize(size_t val){
        assert(val <= capacity());
        size_ = val;
    }
};

struct FileCopy;

struct Chunk;

using ChunkDeleter = decltype([](auto chunk_ptr){
    if (chunk_ptr->need_deletion){
        delete chunk_ptr;
    }
});

struct Chunk{
    BoundVector<char, 65536> data;
    size_t processed = 0;
    size_t pos = 0;
    FileCopy* file_copy = nullptr;
    std::unique_ptr<Chunk, ChunkDeleter> loop;
    std::pair<void(*)(void*, struct io_uring_cqe*), void*> func;
    bool need_deletion = true;
};

template<bool op_num>
void handle_rw(void*data, struct io_uring_cqe*cqe);

struct FileCopy{
    UringLoop loop;
    std::array<int, 2> fd;
    uint64_t in_scheduled_bytes = 0;
    size_t insize = 0;
    std::vector<
        std::pair<
            std::array<
                Chunk,
                QUEUE_SIZE
            >,
            std::array<
                std::unique_ptr<
                    Chunk,
                    ChunkDeleter
                >,
                QUEUE_SIZE
            >
        >
    > chunks_v;
    FileCopy(const char*i, const char* o){
        fd[0] = SYSCALL(open(i, O_RDONLY));
        fd[1] = SYSCALL(open(o, O_WRONLY | O_CREAT | O_TRUNC, 0644));
        insize = get_file_size(fd[0]);
        chunks_v.resize(1);
        auto& chunks = chunks_v[0].first;
        auto& chunk_uptrs = chunks_v[0].second;
        for (auto& chunk: chunks){
            auto& chunk_uptr = chunk_uptrs[&chunk - &chunks[0]];
            chunk.need_deletion = false;
            chunk_uptr = std::unique_ptr<Chunk, ChunkDeleter>(&chunk, ChunkDeleter());
        }
        fill_read(chunk_uptrs.data(), chunk_uptrs.size());
        loop.loop();
    }
    void fill_read(std::unique_ptr<Chunk, ChunkDeleter>* chunks_to_use = nullptr, size_t chunks_to_use_len = 0){
        while (in_scheduled_bytes != insize and loop.can_schedule()){
            std::unique_ptr<Chunk, ChunkDeleter> chunk;
            if (chunks_to_use_len){
                chunk = std::move(*chunks_to_use);
                ++chunks_to_use;
                --chunks_to_use_len;
            }else{
                chunk = std::unique_ptr<Chunk, ChunkDeleter>(new Chunk(), ChunkDeleter());
            }
            chunk->file_copy = this;
            chunk->data.resize(std::min(chunk->data.capacity(), insize - in_scheduled_bytes));
            chunk->pos = in_scheduled_bytes;
            in_scheduled_bytes += chunk->data.size();
            schedule_chunk<0>(std::move(chunk));
        }
    }
    template<bool op_num>
    void schedule_chunk(std::unique_ptr<Chunk, ChunkDeleter> chunk){
        if (chunk -> processed != chunk->data.size()){
            auto chunk_ptr = chunk.get();
            chunk->loop = std::move(chunk);
            {
                auto chunk = chunk_ptr;
                chunk->func.second = chunk_ptr;
                chunk->func.first = ::handle_rw<op_num>;
                loop.async_rw<op_num>(
                    fd[op_num],
                    chunk->data.data() + chunk->processed,
                    chunk->data.size() - chunk->processed,
                    chunk->pos + chunk->processed,
                    NonOwningFunction<void(struct io_uring_cqe*)>{&chunk->func}
                );
            }
        }else{
            chunk->processed = 0;
            if constexpr(op_num == 0){
                schedule_chunk<1>(std::move(chunk));
            }else{
                fill_read(&chunk, 1);
            }
        }
    }
    template<bool op_num>
    void handle_rw(std::unique_ptr<Chunk, ChunkDeleter> chunk, struct io_uring_cqe* cqe){
        auto slen = cqe->res;
        if (slen == -EAGAIN){
            slen = 0;
        }
        LIBURING(slen);
        chunk->processed += slen;
        schedule_chunk<op_num>(std::move(chunk));
    }
    ~FileCopy(){
        close(fd[0]);
        close(fd[1]);
    }
};

template<bool op_num>
void handle_rw(void*data, struct io_uring_cqe*cqe)
{
    auto chunk = std::move(((Chunk*)data)->loop);
    chunk->file_copy->handle_rw<op_num>(std::move(chunk), cqe);
}

int main(int argc, char**argv){
    assert(argc == 3);
    (FileCopy(argv[1], argv[2]));
}

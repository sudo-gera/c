#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

#define part_count 64
#define part_len 65536

struct jmp {
    jmp_buf a;
    jmp() {
        memset(a, 0, sizeof(a));
    }
    ~jmp() {
        memset(a, 0, sizeof(a));
    }
};

struct stack_part;
stack_part* current = nullptr;

struct stack_part {
    stack_part* prev = nullptr;
    jmp buf;
    function<void()> f;
    exception_ptr eptr = nullptr;
    void loop() {
        if (!setjmp(buf.a)) {
            return;
        }
        while (1) {
            try {
                f();
            } catch (...) {
                eptr = current_exception();
            }
            f = decltype(f)();
            assert(not f);
            assert(current == this);
            jump();
        }
    }
    void jump() {
        jmp tmp_buf = buf;
        if (!setjmp(buf.a)) {
            longjmp(tmp_buf.a, 1);
        }
    }
    void resume() {
        assert(not eptr);
        prev = current;
        current = this;
        jump();
        current = current->prev;
        if (eptr) {
            auto e = eptr;
            eptr = nullptr;
            rethrow_exception(e);
        }
    }
    static void suspend() {
        current->jump();
    }
};

void init_stack(auto ptr, size_t& len, vector<stack_part>& stack_parts) {
    char data[part_len];
    if (abs(ptr - (char*)&ptr) > part_len) {
        stack_parts[len++].loop();
        if (len < part_count) {
            init_stack((char*)&ptr, len, stack_parts);
        }
    } else {
        init_stack(ptr, len, stack_parts);
    }
}

vector<stack_part> stack_parts = []() {
    vector<stack_part> stack_parts = vector<stack_part>(part_count);
    size_t len = 0;
    init_stack((char*)&len, len, stack_parts);
    return std::move(stack_parts);
}();

struct Coroutine {
    stack_part& con;
    auto& init_con() {
        for (auto& q : stack_parts) {
            if (not q.f) {
                return q;
            }
        }
        assert(0);
    }
    Coroutine(function<void()> f) : con(init_con()) {
        con.f = f;
    }
    void Resume() {
        con.resume();
    }
    bool IsCompleted() {
        return not con.f;
    }
    static void Suspend() {
        stack_part::suspend();
    }
};

#include <memory>
#include <string>
#include <sstream>
#include <thread>

//////////////////////////////////////////////////////////////////////

struct TreeNode;

using TreeNodePtr = std::shared_ptr<TreeNode>;

struct TreeNode {
    TreeNodePtr left;
    TreeNodePtr right;
    std::string data;

    TreeNode(std::string d, TreeNodePtr l, TreeNodePtr r)
        : left(std::move(l)), right(std::move(r)), data(std::move(d)) {
    }

    static TreeNodePtr Fork(std::string data, TreeNodePtr left, TreeNodePtr right) {
        return std::make_shared<TreeNode>(std::move(data), std::move(left), std::move(right));
    }

    static TreeNodePtr Leaf(std::string data) {
        return std::make_shared<TreeNode>(std::move(data), nullptr, nullptr);
    }
};

//////////////////////////////////////////////////////////////////////

class TreeIterator {
public:
    explicit TreeIterator(TreeNodePtr root) : walker_([this, root] { TreeWalk(root); }) {
    }

    bool MoveNext() {
        walker_.Resume();
        return !walker_.IsCompleted();
    }

    std::string_view Data() const {
        return data_;
    }

private:
    void TreeWalk(TreeNodePtr node) {
        if (node->left) {
            TreeWalk(node->left);
        }

        data_ = node->data;
        Coroutine::Suspend();

        if (node->right) {
            TreeWalk(node->right);
        }
    }

private:
    Coroutine walker_;
    std::string_view data_;
};

//////////////////////////////////////////////////////////////////////

#define SIMPLE_TEST(...)

#define ASSERT_TRUE(...) assert((__VA_ARGS__))
#define ASSERT_FALSE(...) assert(!(__VA_ARGS__))

#define ASSERT_EQ(a, s) assert((a) == (s));

#define ASSERT_THROW(a, s) \
    {                      \
        try {              \
            a;             \
            assert(0);     \
        } catch (s) {      \
        }                  \
    }

struct Threads {
    template <typename F>
    void Run(F task) {
        std::thread t([task = std::move(task)]() mutable { task(); });
        t.join();
    }
};

int main() {
    SIMPLE_TEST(JustWorks) {
        Coroutine co([] { Coroutine::Suspend(); });

        ASSERT_FALSE(co.IsCompleted());
        co.Resume();
        ASSERT_FALSE(co.IsCompleted());
        co.Resume();
        ASSERT_TRUE(co.IsCompleted());
    }

    SIMPLE_TEST(Interleaving) {
        int step = 0;

        Coroutine a([&] {
            ASSERT_EQ(step, 0);
            step = 1;
            Coroutine::Suspend();
            ASSERT_EQ(step, 2);
            step = 3;
        });

        Coroutine b([&] {
            ASSERT_EQ(step, 1);
            step = 2;
            Coroutine::Suspend();
            ASSERT_EQ(step, 3);
            step = 4;
        });

        a.Resume();
        b.Resume();

        ASSERT_EQ(step, 2);

        a.Resume();
        b.Resume();

        ASSERT_TRUE(a.IsCompleted());
        ASSERT_TRUE(b.IsCompleted());

        ASSERT_EQ(step, 4);
    }

    SIMPLE_TEST(Threads) {
        size_t steps = 0;

        Coroutine co([&steps] {
            //   std::cout << "Step" << std::endl;
            ++steps;
            Coroutine::Suspend();
            //   std::cout << "Step" << std::endl;
            ++steps;
            Coroutine::Suspend();
            //   std::cout << "Step" << std::endl;
            ++steps;
        });

        auto resume = [&co] { co.Resume(); };

        // Simulate fiber running in thread pool
        Threads threads;
        threads.Run(resume);
        threads.Run(resume);
        threads.Run(resume);

        ASSERT_EQ(steps, 3);
    }

    SIMPLE_TEST(TreeWalk) {
        auto root = TreeNode::Fork(
            "B", TreeNode::Leaf("A"),
            TreeNode::Fork("F", TreeNode::Fork("D", TreeNode::Leaf("C"), TreeNode::Leaf("E")), TreeNode::Leaf("G")));

        std::stringstream traversal;

        TreeIterator iter(root);
        while (iter.MoveNext()) {
            traversal << iter.Data();
        }

        ASSERT_EQ(traversal.str(), "ABCDEFG");
    }

    SIMPLE_TEST(Pipeline) {
        const size_t kSteps = 123;

        size_t step_count = 0;

        Coroutine a([&] {
            Coroutine b([&] {
                for (size_t i = 0; i < kSteps; ++i) {
                    ++step_count;
                    Coroutine::Suspend();
                }
            });

            while (!b.IsCompleted()) {
                b.Resume();
                Coroutine::Suspend();
            }
        });

        while (!a.IsCompleted()) {
            a.Resume();
        }

        ASSERT_EQ(step_count, kSteps);
    }

    struct MyException {};

    SIMPLE_TEST(Exception) {
        Coroutine co([&] {
            Coroutine::Suspend();
            throw MyException{};
            Coroutine::Suspend();
        });

        ASSERT_FALSE(co.IsCompleted());
        co.Resume();
        ASSERT_THROW(co.Resume(), MyException);
        ASSERT_TRUE(co.IsCompleted());
    }

    SIMPLE_TEST(NestedException1) {
        Coroutine a([&] {
            Coroutine b([] { throw MyException(); });
            ASSERT_THROW(b.Resume(), MyException);
        });

        a.Resume();
    }

    SIMPLE_TEST(NestedException2) {
        Coroutine a([&] {
            Coroutine b([] { throw MyException(); });
            b.Resume();
        });

        ASSERT_THROW(a.Resume(), MyException);

        ASSERT_TRUE(a.IsCompleted());
    }

    SIMPLE_TEST(ExceptionsHard) {
      int score = 0;

      Coroutine a([&] {
        Coroutine b([] {
          throw 1;
        });
        try {
          b.Resume();
        } catch (int) {
          ++score;
          // Context switch during stack unwinding
          Coroutine::Suspend();
          throw;
        }
      });

      a.Resume();

      std::thread t([&] {
        try {
          a.Resume();
        } catch (int) {
          ++score;
        }
      });
      t.join();

      ASSERT_EQ(score, 2);
    }

    SIMPLE_TEST(MemoryLeak) {
        auto shared_ptr = std::make_shared<int>(42);
        std::weak_ptr<int> weak_ptr = shared_ptr;

        {
            auto routine = [ptr = std::move(shared_ptr)] {};
            Coroutine co(routine);
            co.Resume();
        }

        ASSERT_FALSE(weak_ptr.lock());
    }
}

// RUN_ALL_TESTS()

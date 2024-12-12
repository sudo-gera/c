#include <atomic>
#include <iostream>
#include <mutex>
#include <stdio.h>
#include <stdlib.h>
#include <random>

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

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

struct abs_lock{
    void lock(){}
    void unlock(){}
};

template<typename T>
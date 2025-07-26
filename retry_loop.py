from collections import deque
import time
import bisect

class Retry:
    def __init__(self, interval: int, failure_count: int):
        self.interval = interval
        self.failure_count = failure_count
        self.failures : deque[int] = deque()
    
    def fail(self) -> bool:
        ct = time.time_ns()
        self.failures.append(ct)
        old_count = bisect.bisect(self.failures, ct - self.interval)
        if len(self.failures) - old_count >= self.failure_count:
            return True
        if len(self.failures) > self.failure_count:
            self.failures.popleft()
        assert len(self.failures) <= self.failure_count
        return False
    
    def success(self) -> None:
        self.failures.clear()
    

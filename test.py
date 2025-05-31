import os
import signal
import time

def child_process():

    resources = set()

    class resource:
        def __enter__(self):
            resources.add(id(self))
        def __exit__(self, *_):
            resources.remove(id(self))

    try:
        while 1:
            with resource():
                pass
    except KeyboardInterrupt:
        exit(len(resources))

def main_process(child_pid):
    time.sleep(0.1)
    os.kill(child_pid, signal.SIGINT)
    pid, rc = os.waitpid(child_pid, 0)
    assert pid == child_pid and rc == 0, f'{child_pid = }, {pid = }, {rc = }'

if __name__ == '__main__':
    for i in range(999):
        print('iteration', i)
        if (pid := os.fork()):
            main_process(pid)
        else:
            child_process()

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
    pid = child_pid
    time.sleep(0.1)
    os.kill(pid, signal.SIGINT)
    pid_, rc = os.waitpid(pid, 0)
    assert pid_ == pid and rc == 0, f'{pid = }, {pid_ = }, {rc = }'

if __name__ == '__main__':
    while True:
        if (pid := os.fork()):
            main_process(pid)
        else:
            child_process()

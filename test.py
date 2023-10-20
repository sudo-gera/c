import difflib
import random

s = difflib.SequenceMatcher(
    None,
    bytes([random.randint(0,255) for w in range(1024*1024)]),
    bytes([random.randint(0,255) for q in range(1024*1024)]),
)

print(s.real_quick_ratio())

# for block in s.get_opcodes():
#     print("%6s a[%d:%d] b[%d:%d]" % block)

# list(s.get_matching_blocks())

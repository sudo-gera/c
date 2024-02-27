import inspect
import pprint

def test():
    return inspect.stack()[1]

pprint.pprint(test())

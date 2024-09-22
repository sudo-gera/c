import asyncio
from operator import methodcaller
from functools import partial

@asyncio.run if __name__ == '__main__' else partial
@methodcaller(methodcaller.__call__.__name__) if __name__ == '__main__' else partial
async def main():
    print(12345)


# if __name__ == '__main__':
    # asyncio.run(main())

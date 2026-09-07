from bs4 import BeautifulSoup, Tag, NavigableString
import itertools
import urllib.request
import pathlib

import download

def get_url_for_page(page: int) -> str:
    if page < 1:
        raise ValueError(f"Page {page} does not exist.")
    if page == 1:
        return 'https://freedns.afraid.org/domain/registry/'
    return f'https://freedns.afraid.org/domain/registry/page-{page}.html'

loader = download.Downloader(pathlib.Path.home() / '.c.cache')

domains = []

for page in itertools.count(1):
    print(f"{page = }")
    for attempt in itertools.count():
        url = f"{get_url_for_page(page)}?a={attempt}"
        print(url)
        data = loader.temporary.download_str(url)
        # print(data)
        if 'Joshua Anderson' in data:
            break
    if 'Invalid page number.' in data:
        break
    soup = BeautifulSoup(data)
    for line in soup.select('html > body > table > tr:nth-child(2) > td:nth-child(2) > center > center > table > tr'):
        if len(line.contents) == 4:
            tag = line.contents[1]
            if isinstance(tag, Tag):
                visibility = tag.contents[0]
                if isinstance(visibility, NavigableString):
                    if str(visibility) == 'public':
                        tag = line.contents[0]
                        if isinstance(tag, Tag):
                            tag = tag.contents[0]
                            if isinstance(tag, Tag):
                                domains.append(str(tag.contents[0]))

domains.sort(key=len)
for domain in domains[:20]:
    print(domain)


from http.server import BaseHTTPRequestHandler, HTTPServer
import base64
import json
import time
import secrets

def imitate_chat_gpt(prompt):
    time.sleep(1)
    return f'''
I ain't gonna answer your prompt:
{prompt!r}
cuz im a lazy chatGPT placeholder
'''

def call_chat_gpt(prompt):
    ans = []
    servers = []
    token = secrets.token_hex(64)
    class S(BaseHTTPRequestHandler):
        def do_GET(self):
            self.send_response(200)
            self.send_header('Content-type', 'text/html; charset=UTF-8')
            self.send_header('Access-Control-Allow-Origin', '*')
            self.end_headers()
            if self.path == '/':
                self.wfile.write(
                    json.dumps(dict(
                        value=prompt,
                        token=token,
                    )).encode())
                return
            data = json.loads(base64.b64decode(self.path[1:].encode()))
            if data['token'] == token:
                ans.append(data['value'])
                raise KeyboardInterrupt
        def log_message(self, *a):
            pass
    try:
        with HTTPServer(('',5205), S) as server:
            servers.append(server)
            server.serve_forever()
    except KeyboardInterrupt:
        if ans:
            return ans[0]
        raise

import os.path
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials as Credentials1
from google_auth_oauthlib.flow import InstalledAppFlow
from googleapiclient.discovery import build
from googleapiclient.errors import HttpError
import gspread
from google.oauth2.service_account import Credentials as Credentials2
import openai

import googleapiclient
import json
import traceback
import sys
import re
from pprint import pprint

def coords_and_A1(a,s = None):
    '''
        A1 is (0,0)
        A2 is (1,0)
        B1 is (0,1)
        B2 is (1,1)
        works in both directions
    '''

    letters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

    def get_columns_with_len(l):
        if not l:
            yield ''
            return
        for head in letters:
            for tail in get_columns_with_len(l-1):
                yield head + tail

    import itertools
    import functools
    import re
    import time

    coords_and_A1.num_and_col_dict = getattr(coords_and_A1, 'num_and_col_dict', {})
    coords_and_A1.iter = getattr(coords_and_A1, 'iter', itertools.count(1))
    num_and_col_dict = coords_and_A1.num_and_col_dict
    
    def col_and_num(a):
        while a not in num_and_col_dict:
            fill_columns()
        return num_and_col_dict[a]

    def fill_columns(*a):
        for col in get_columns_with_len(next(coords_and_A1.iter)):
            num = len(num_and_col_dict)//2
            num_and_col_dict[num]=col
            num_and_col_dict[col]=num

    if s is None:
        a,s = re.fullmatch(r'(\D+)(\d+)', a).groups()
        return int(s)-1, col_and_num(a.upper())
    return col_and_num(s)+str(a+1)



def load_google_creds():
    SCOPES = [
        "https://www.googleapis.com/auth/spreadsheets",
        "https://www.googleapis.com/auth/documents",
    ]
    creds = None
    if os.path.exists("token.json"):
        creds = Credentials1.from_authorized_user_file("token.json", SCOPES)
    
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file(
                "credentials.json", SCOPES
            )
            creds = flow.run_local_server(port=0)
        
        with open("token.json", "w") as token:
            token.write(creds.to_json())
    return creds

class Sheet:
    def read_range(self, x, y) -> list[list[str]]:
        sheet_range = coords_and_A1(x, y)
        result = self.google.sheets.get(
            spreadsheetId=self.doc_id,
            range=sheet_range,
            majorDimension='ROWS',
        ).execute()
        return result['values']
    def write_range(self, x, y, values: list[list[str]]):
        sheet_range = coords_and_A1(x, y)
        self.google.sheets.update(
            spreadsheetId=self.doc_id,
            range=sheet_range,
            valueInputOption='RAW',
            body = dict(
                values = values,
                range = sheet_range,
            ),
        ).execute()
    def write(self, x:int, y:int, text: str):
        return self.write_range(x,y,[[text]])
    def read(self) -> list[list[str]]:
        top_right = self.google.sheets.get(
            spreadsheetId=self.doc_id,
            range='A1:A',
            majorDimension='ROWS',
        ).execute()['range'][::-1].split(':',1)[0][::-1]
        bottom_left = self.google.sheets.get(
            spreadsheetId=self.doc_id,
            range='A1:1',
            majorDimension='ROWS',
        ).execute()['range'][::-1].split(':',1)[0][::-1]
        return self.google.sheets.get(
            spreadsheetId=self.doc_id,
            range=top_right + ':' + bottom_left,
            majorDimension='ROWS',
        ).execute()['values']
    class line:
        def __init__(self, sheet, index):
            self.sheet = sheet
            self.index = index
            try:
                self.sheet.data
            except:
                self.sheet.data = self.sheet.read()
        def __getitem__(self, index):
            try:
                return self.sheet.data[self.index][index]
            except IndexError:
                return ''
        def __setitem__(self, index, value):
            while self.index >= len(self.sheet.data):
                self.sheet.data.append([])
            while index >= len(self.sheet.data[self.index]):
                self.sheet.data[self.index].append('')
            self.sheet.data[self.index][index] = value
            self.sheet.write(self.index, index, value)
        def __delitem__(self, index):
            self[index] = ''
    def __getitem__(self, index):
        return self.line(self, index)



class Doc:
    def __init__(self):
        self.location = 1
    class BatchUpdater:
        def __init__(self, doc):
            self.doc = doc
            self.requests = []
        def __enter__(self):
            return self
        def __exit__(self, *e):
            self.doc.google.docs.batchUpdate(
                documentId=self.doc.doc_id,
                body=dict(
                    requests=self.requests
                )
            ).execute()
        def __getattr__(self, name):
            return lambda **params:\
                self.requests.append({name:params})
        def write(self, text, fontsize):
            self.insertText(
                location=dict(index=self.doc.location),
                text=text
            )
            self.updateTextStyle(
                textStyle=dict(
                    fontSize=dict(
                        magnitude=fontsize,
                        unit='PT',
                    )
                ),
                fields='*',
                range=dict(
                    startIndex=self.doc.location,
                    endIndex=self.doc.location + len(text),
                )
            )
            self.doc.location += len(text)
    def batch(self):
        return self.BatchUpdater(self)
    def __getattr__(self, name):
        def run_in_batch(*a, **s):
            with self.batch() as batch:
                getattr(batch, name)(*a, **s)
        return run_in_batch
            

class Google:
    def __init__(self):
        self.creds = load_google_creds()
        self.sheets = build("sheets", "v4", credentials=self.creds).spreadsheets().values()
        self.docs = build("docs", "v1", credentials=self.creds).documents()
    def open(self, url):
        doc_type, doc_id = re.match(r'https://docs.google.com/([^/]*)/d/([^/]*).*', url).groups()
        doc =  dict(
            spreadsheets=Sheet,
            document=Doc,
        )[doc_type]()
        doc.google = self
        doc.doc_id = doc_id
        return doc

def main():
    google = Google()
    doc = google.open('https://docs.google.com/document/d/1TROJqj7qOjSyZxQuVX5wi67GN7m06duc0B40GjV-VIc/edit')
    sheet = google.open('https://docs.google.com/spreadsheets/d/18CBU8-LsLarHn28SwwN4m01NCpWkANV0gaTGb1XYgJU/edit#gid=0')
    for line in sheet:
        if line[2] == '':
            break
        query = f'Придумай затравку для книги под названием ' + line[2]
        answer = imitate_chat_gpt(query)
        doc.write('\t' + query + '\n', fontsize=15)
        doc.write(answer + '\n'*20, fontsize=11)
        line[18]='done'

if __name__ == '__main__':
    main()



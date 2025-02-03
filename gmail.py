import json
import os.path
import functools

from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from google_auth_oauthlib.flow import InstalledAppFlow
from googleapiclient.discovery import build
from googleapiclient.errors import HttpError

# If modifying these scopes, delete the file token.json.
SCOPES = ["https://www.googleapis.com/auth/gmail.readonly"]


def main():
    creds = None
    # The file token.json stores the user's access and refresh tokens, and is
    # created automatically when the authorization flow completes for the first
    # time.
    if os.path.exists("token.json"):
        creds = Credentials.from_authorized_user_file("token.json", SCOPES)
    # If there are no (valid) credentials available, let the user log in.
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file(
                    "credentials.json", SCOPES
            )
            creds = flow.run_local_server(port=0)
        # Save the credentials for the next run
        with open("token.json", "w") as token:
            token.write(creds.to_json())

    try:
        try:
            with open('gmail.json') as gmail_file:
                gmail = json.load(gmail_file)
        except Exception as e:
            print(e)
            gmail = {}
        # print(len(gmail['messages']))
        # Call the Gmail API
        service = build("gmail", "v1", credentials=creds)
        import googleapiclient.discovery
        assert isinstance(service, googleapiclient.discovery.Resource)
        results = service.users().messages().list(userId="me", includeSpamTrash=True, maxResults=500).execute()
        # print(results)
        def callback(array: list, *args):
            array.append(args)
        messages = []
        import googleapiclient.http
        def work():
            for message in results['messages']:
                if message['id'] not in gmail.setdefault('messages', {}):
                    yield message
        worker = work()
        while 1:
            batch = service.new_batch_http_request()
            assert isinstance(batch, googleapiclient.http.BatchHttpRequest)
            for q in range(100):
                message = next(worker, None)
                if message is None:
                    break
                batch.add(service.users().messages().get(userId='me', id=message['id']), callback=functools.partial(callback, messages, message))
            batch.execute()
            if message is None:
                break

        from pprint import pprint
        for first_message, req_id, second_message, exc in messages:
            if exc is not None:
                print(exc)
                continue
            gmail.setdefault('messages', {})[first_message['id']] = second_message

        for message in gmail['messages'].values():
            n = 0
            try:
                for header in message['payload']['headers']:
                    if header['name'] == 'From':
                        sender = header['value']
                        try:
                            sender = sender[::-1].split('>',1)[1].split('<',1)[0][::-1]
                        except Exception:
                            pass
                        message['sender'] = sender
                        n += 1
            except Exception as e:
                print(e)
                print(message)
                exit()
            assert n == 1

        for message in gmail['messages'].values():
            if message['sender'].endswith('.edu'):
                print(message)


    except HttpError as error:
        # TODO(developer) - Handle errors from gmail API.
        print(f"An error occurred: {error}")
    finally:
        with open('gmail.json', 'w') as gmail_file:
            json.dump(gmail, gmail_file, indent=4)

if __name__ == "__main__":
    main()

dialog = {
    'intens': {
        'hi': {
            'key_words': ['привет', 'hi'],
            'answer': 'здравствуйте'
        },
        'bye': {
            'key_words': ['пока', 'bye'],
            'answer': 'до свидания'
        }
    },
}
while 1:
    try:
        a=input()
    except EOFError:
        break
    for q in a.split():
        for a,s in dialog['intens'].items():
            for d in s['key_words']:
                if q==d:
                    print(s['answer'])


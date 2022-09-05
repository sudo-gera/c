# a=open('/Users/gera/Downloads/yandex.ru_09-05-2022-07-04-07.csv')
# from asyncore import read
# import csv
# csvfile=a
# dialect = csv.Sniffer().sniff(csvfile.read())
# csvfile.seek(0)
# reader = csv.reader(csvfile, dialect)
# a=list(reader)[1:]
# a=[w[10] for w in a]
# a=[w.split(':')[0] for w in a]
# for w in a:
#     print('    '+repr(w)+',')
import json
import os
from tqdm import tqdm
from collections import defaultdict as dd
from typing import *

filename = '../doc_j.json'
file_size = os.path.getsize(filename)

# tid: dd[tuple[int, int], int] = dd(int)

# times: dd[int, int] = dd(int)
# ids: dd[int, int] = dd(int)
# id_oids: dd[str, int] = dd(int)
# kkt_inn_time: dd[tuple[str, str, int], int] = dd(int)
# subtypes: set[str] = set()
# kkt_inn_time_data: dd[tuple[str, str, int], list[Any]] = dd(list)

aaaa: list[dict[str, Any]] = []

# unit='B' and unit_scale=True automatically format bytes to KB, MB, or GB
with open(filename, "r", encoding="utf-8") as f, tqdm(
    total=file_size, unit="B", unit_scale=True, desc="Reading file"
) as pbar:
    for line in f:
        pbar.update(len(line.encode("utf-8")))


        data = json.loads(line)
        aaaa.append(data)

        match data:
            case {
                '_id': {
                    '$oid': id_oid,
                    **id_empty_rest
                },
                'fsId': fsid,
                'kktRegId': kktregid,
                'subtype': subtype,
                'receiveDate': {
                    '$date': receivedate_date,
                    **receivedate_empty_rest,
                },
                'protocolVersion': protocolversion,
                'ofdId': ofdid,
                'protocolSubversion': protocolSubversion,
                'content': {
                    'fiscalDriveNumber': content_fiscalDriveNumber,
                    'rawData': content_rawData,
                    'kktRegId': content_kttregid,
                    'userInn': content_userinn,
                    'fiscalSign': content_fiscalsign,
                    'fiscalDocumentNumber': content_fiscalDocumentNumber,
                    'dateTime': {
                        '$date': content_datetime_date,
                        **content_datetime_rest,
                    },
                    **content_rest,
                },
                'documentId': documentid,
                **empty_rest,
            } if (True
                and isinstance(id_oid, str)
                and not id_empty_rest
                and isinstance(fsid, str)
                and isinstance(kktregid, str)
                and isinstance(subtype, str)
                and isinstance(receivedate_date, int)
                and not receivedate_empty_rest
                and isinstance(protocolversion, int|str)
                and isinstance(ofdid, str)
                and isinstance(protocolSubversion, int)
                and isinstance(content_fiscalDriveNumber, str)
                and isinstance(content_rawData, str)
                and isinstance(content_kttregid, str)
                and isinstance(content_userinn, str)
                and isinstance(content_fiscalsign, int)
                and isinstance(content_fiscalDocumentNumber, int)
                and isinstance(content_datetime_date, int)
                and not content_datetime_rest
                and isinstance(documentid, int)
                and not empty_rest
            ):
                if subtype == 'receipt':
                    match content_rest:
                        case {
                            'shiftNumber': content_shiftNumber,
                            'cashTotalSum': content_cashTotalSum,
                            'receiptCode': content_receiptCode,
                            'taxationType': content_taxationType,
                            'requestNumber': content_requestNumber,
                            'ecashTotalSum': content_ecashTotalSum,
                            'operationType': content_operationType,
                            **content_rest,
                        } if (True
                            and isinstance(content_shiftNumber, int)
                            and isinstance(content_cashTotalSum, int)
                            and isinstance(content_receiptCode, int)
                            and isinstance(content_taxationType, int | list)
                            and isinstance(content_requestNumber, int)
                            and isinstance(content_ecashTotalSum, int)
                            and isinstance(content_operationType, int)
                        ):
                            ...
                        case data:
                            raise TabError(data)
                # if subtype in ['receipt', 'openShift', 'closeShift']:
                #     times[content_datetime_date] += 1
                #     ids[documentid] += 1
                #     tid[content_datetime_date, documentid] += 1
                #     id_oids[id_oid] += 1
                #     kkt_inn_time[kktregid, content_userinn, content_datetime_date] += 1
                #     if (kktregid, content_userinn, content_datetime_date) == ('0000001655050213', '2225074005', 1479896700000):
                #         kkt_inn_time_data[kktregid, content_userinn, content_datetime_date].append(data)
                # else:
                #     subtypes.add(subtype)
            case data:
                raise TabError(data)

# # print(*sorted(dict(zip(*[*zip(*times.items())][::-1])).items()), sep='\n')
# # print(*sorted(dict(zip(*[*zip(*ids.items())][::-1])).items()), sep='\n')
# # print(*sorted(dict(zip(*[*zip(*tid.items())][::-1])).items()), sep='\n')
# # print(*sorted(dict(zip(*[*zip(*id_oids.items())][::-1])).items()), sep='\n')
# print(*sorted(dict(zip(*[*zip(*kkt_inn_time.items())][::-1])).items()), sep='\n')
# print(subtypes)
# for (kkt, inn, time),v in kkt_inn_time.items():
#     if v > 1:
#         print((kkt, inn, time))

# # for vv in kkt_inn_time_data.values():
# #     for vvv in vv:
# #         print(vvv['subtype'])



import itertools

for (kkt, inn), kkt_inn_group_iter in itertools.groupby(aaaa, key=lambda data: (data['kktRegId'], data['content']['userInn'])):
    if inn == '5007091422':
        kkt_inn_group_els = list(kkt_inn_group_iter)

        kkt_inn_group_els.sort(key=lambda x: x['content']['dateTime']['$date'])

        for date, date_group_iter in itertools.groupby(kkt_inn_group_els, key=lambda data: data['receiveDate']['$date']):
            date_group_els = list(date_group_iter)

            for x in date_group_els:
                # print(x)
                print(x['subtype'], x['kktRegId'], x['content']['userInn'], x['content']['dateTime']['$date'], sep='\t')

            # if any(
            #     data['subtype'] == 'receipt'
            #     for data in date_group_els
            # ):
            #     if any(
            #         data['subtype'] == 'openShift'
            #         for data in date_group_els
            #     ) or any(
            #         data['subtype'] == 'closeShift'
            #         for data in date_group_els
            #     ):
            #         print(date_group_els)



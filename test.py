import json
import os
from tqdm import tqdm
from collections import defaultdict as dd

filename = '../doc_j.json'
file_size = os.path.getsize(filename)

tid: dd[tuple[int, int], int] = dd(int)

times: dd[int, int] = dd(int)
ids: dd[int, int] = dd(int)
id_oids: dd[str, int] = dd(int)

# unit='B' and unit_scale=True automatically format bytes to KB, MB, or GB
with open(filename, "r", encoding="utf-8") as f, tqdm(
    total=file_size, unit="B", unit_scale=True, desc="Reading file"
) as pbar:
    for line in f:
        pbar.update(len(line.encode("utf-8")))


        data = json.loads(line)

        match data:
            case {
                '_id': {
                    '$oid': id_oid,
                    **id_empty_rest
                },
                'fsId': fsid,
                'kktRegId': kkdregid,
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
                and isinstance(kkdregid, str)
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
                times[content_datetime_date] += 1
                ids[documentid] += 1
                tid[content_datetime_date, documentid] += 1
                id_oids[id_oid] += 1
            case data:
                raise TabError(data)

# print(*sorted(dict(zip(*[*zip(*times.items())][::-1])).items()), sep='\n')
# print(*sorted(dict(zip(*[*zip(*ids.items())][::-1])).items()), sep='\n')
# print(*sorted(dict(zip(*[*zip(*tid.items())][::-1])).items()), sep='\n')
print(*sorted(dict(zip(*[*zip(*id_oids.items())][::-1])).items()), sep='\n')

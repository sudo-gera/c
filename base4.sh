LANG=''
if (($# < 2))
then
    cat test.txt|base64|tr -d '\n'|sed "s/\(.\)/+\1+/g"|base64|\
    sed "s/.\(.\)\(.\)./++\1++\2++/g"|base64 -d|sed "s/.\(....\)./\1/g"|\
    sed "s/\(.\)/\1++/g"|base64|sed "s/.\(.\)..\(.\).../M\1++M\2++/g"|\
    base64 -d|sed "s/\(.\)../\1/g"|sed "s/0/00/g"|sed "s/1/01/g"|\
    sed "s/2/10/g"|sed "s/3/11/g"
else
    cat test1.txt|sed "s/\(..\)/+\1/g"|sed "s/+11/3/g"|sed "s/+10/2/g"|\
    sed "s/+01/1/g"|sed "s/+00/0/g"|sed "s/\(.\)/\1++/g"|base64|\
    sed "s/.\(.\)...\(.\)../+\1++\2+++/g"|base64 -d|sed "s/\(.\)../\1/g"|\
    sed "s/\(....\)/+\1+/g"|base64|sed "s/..\(.\)..\(.\)../+\1\2+/g"|\
    base64 -d|sed "s/.\(.\)./\1/g"|base64 -d
fi

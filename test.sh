LANG=''
cat test.txt |\
    sed "s/\(.\)/M\1M/g" |\
    base64 |\
    sed "s/.\(.\)\(.\)./MM\1MM\2MM/g" |\
    base64 -d |\
    sed "s/.\(....\)./\1/g" | sed "s/\(.\)/\1MM/g" |\
    base64 |\
    sed "s/.\(.\)..\(.\).../M\1MMM\2MM/g" |\
    base64 -d |\
    sed "s/\(.\)../\1/g"

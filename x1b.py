for w in range(108):
 for e in range(108):
  #print('\x1b['+str(w)+';'+str(e)+'m['+str(w)+' '*(4-len(str(w)))+str(e)+' '*(3-len(str(e)))+']\x1b[0m',end=' ')
  print('\x1b['+str(w)+';'+str(e)+'m00\x1b[0m',end='')
 print()

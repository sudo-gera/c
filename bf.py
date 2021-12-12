[(a:=[]),(i:=0),(stdin:=__import__('sys').stdin.buffer),(stdout:=__import__('sys').stdout.buffer),[
	a[i]:=a[i]+1
		if w=='+' else 
	a[i]:=a[i]-1
		if w=='-' else 
	i:=i+1
		if w=='>' else 
	i:=i-1
		if w=='<' else 
	stdout.write(bytearray([a[i]]))
		if w=='.' else 
	a[i]:=ord(stdin.read(1))
		if w=='' else 
	a[i]:=a[i]+1
		if w=='+' else 
	a[i]:=a[i]+1
		if w=='+' else 













 for w in __import__('sys').argv[-1]]]

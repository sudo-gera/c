from pathlib import Path
q=open(str(Path.home())+'/../usr/include/bits/stdc++.h').read()
q=q.split('\n')
w=q
w=['#if __has_include("'+q.split('<')[-1].split('>')[0]+'")\n'+q+'\n#endif' if q.strip().startswith('#') and q.strip()[1:].strip().startswith('include') else q for q in w]
w='\n'.join(w)
open(str(Path.home())+'/../usr/include/bits/stdc++.h','w').write(w)

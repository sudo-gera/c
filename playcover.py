import os,shutil
for w in os.listdir('/Users/gera/Library/Containers/me.playcover.PlayCover'):
	if w.endswith('.app'):
		shutil.copytree('/Users/gera/Library/Containers/me.playcover.PlayCover/'+w,'/Applications/playcover__'+w)

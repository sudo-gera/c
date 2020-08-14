sh("cd %homepath%\testbot && git add *")
sh("cd %homepath%\testbot && git commit -am 'send'")
sh("cd %homepath%\testbot && git pull")
sh("cd %homepath%\testbot && git push")



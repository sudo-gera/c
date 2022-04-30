from subprocess import run
run('adb connect 192.168.49.1:53142'.split())
run('adb shell cmd statusbar click-tile com.cloudflare.onedotonedotonedotone/com.cloudflare.app.domain.quicksettingstile.QuickSettingsTileService'.split())

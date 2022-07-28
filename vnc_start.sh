x11vnc -noxdamage -shared -dontdisconnect -many -noxfixes -rfbauth ~/.x11vnc.pass -viewonly -rfbport 5901 &
./noVNC/utils/novnc_proxy --vnc localhost:5901 &

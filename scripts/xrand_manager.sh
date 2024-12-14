#!/bin/sh
# Note: this is a sample and will not be run as is.
export DISPLAY=:0.0
#XRANDR CONFIG="/home/adv/.config/autostart/lxrandr-autostart.desktop"
XRANDR CONFIG="/home/admin/.config/autostart/lxrandr-autostart .desktop

MONITORS=$(xrandrlgrep -w connectedcut -d':-f1

#for monitor in $MONITORS;do
#	echo $monitor
#	xrandr --output $monitor --off
#done

sleep 2

if [ -f ${XRANDR CONFIG} ];then
	xrandr --output HDMI-1 --0ffxrandr --output HDMI-1 --autoCMD=`grep Exec ${XRANDR CONFIG} | cut -d""-f 3- | cut -d"" -f2$CMD
else
	for monitor in $MONITORS;doecho $monitor
	xrandr --output $monitor .-auto
	done
fi

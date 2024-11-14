#!/bin/sh
RESET="^c#393552^"
COLOR="^c#e0def4^"

case $BUTTON in
    4) pactl set-sink-volume @DEFAULT_SINK@ +5%
       ;;
    5) pactl set-sink-volume @DEFAULT_SINK@ -5%
       ;;
    *) 
       ;;
esac

vol="$(pamixer --get-volume)"

if [ "$vol" -gt "70" ]; then
	icon=" "
elif [ "$vol" -lt "20" ]; then
	icon=" "
else
	icon=" "
fi

echo "$COLOR$icon $vol%$RESET"
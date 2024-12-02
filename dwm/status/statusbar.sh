#!/bin/bash

BUTTON="$1"
MODULE="$2"

set_status() {
    spotify=$(spotify)
    volume=$(volume)
    ethernet=$(ping -c 1 8.8.8.8 >/dev/null 2>&1 && echo "􀙇" || echo "􀙈")
    time=$(date +"%a %b %d  %I:%M %p")

    xsetroot -name "$(printf '\x01%s  \x02 %s  \x03 %s  \x04 %s' "$spotify" "$volume" "$ethernet" "$time")"
}

spotify() {
    PLAYERCTL_STATUS=$(playerctl --player=spotify status 2>/dev/null)
    TITLE=$(playerctl --player=spotify metadata --format "{{ artist }} - {{ title }}" 2>/dev/null)

    ICON_PLAYING="􀑪"
    ICON_PAUSED="􀊆"
    ICON_PLAY="􀊄"

    MAX_LENGTH=24
    
    if [ "$PLAYERCTL_STATUS" = "Playing" ]; then
        ICON=$ICON_PLAYING
    elif [ "$PLAYERCTL_STATUS" = "Paused" ]; then
        ICON=$ICON_PLAY
    else
        echo ""
        return
    fi

    if [ ${#TITLE} -gt $MAX_LENGTH ]; then
        TITLE="${TITLE:0:$((MAX_LENGTH - 3))}..."
    fi

    echo "$ICON $TITLE"
}

volume() {
    vol="$(pamixer --get-volume)"
    mute="$(pamixer --get-mute)"

    if [ "$mute" = "true" ] || [ "$vol" -eq 0 ]; then
        icon="􀊣 "  # Muted icon
    elif [ "$vol" -ge 1 ] && [ "$vol" -le 19 ]; then
        icon="􀊡 "  # Quiet volume
    elif [ "$vol" -ge 20 ] && [ "$vol" -le 49 ]; then
        icon="􀊥 "  # Low volume
    elif [ "$vol" -ge 50 ] && [ "$vol" -le 69 ]; then
        icon="􀊧 "  # Medium volume
    elif [ "$vol" -ge 70 ]; then
        icon="􀊩 "  # High volume
    else
        icon="􀊧 "  # Default to medium volume icon
    fi

    echo "$icon$vol%"
}

case "$MODULE" in
    SPOTIFY)
        case "$BUTTON" in
            1) playerctl play-pause;;
            2) playerctl previous;;
            3) playerctl next;;
        esac
        ;;
    VOLUME)
        case "$BUTTON" in
            1) pactl set-sink-mute @DEFAULT_SINK@ toggle ;; # Left-click: Toggle mute
            4) pactl set-sink-volume @DEFAULT_SINK@ +5% ;;  # Scroll up: Increase volume
            5) pactl set-sink-volume @DEFAULT_SINK@ -5% ;;  # Scroll down: Decrease volume
        esac
        ;;
    ETHERNET)
        case "$BUTTON" in
            1) notify-send "$(ping -c 1 8.8.8.8 >/dev/null 2>&1 && echo "􀙇 Connected" || echo "􀙈 Not Connected")" ;;
        esac
        ;;
esac

set_status
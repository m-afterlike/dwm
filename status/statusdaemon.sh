#!/bin/bash

# Path to the status bar script
STATUSBAR_SCRIPT="/home/m/.config/dwm/status/statusbar.sh"

# Function to ping and run the script if output changes
ping_listener() {
    last_ping_output=""
    while true; do
        current_ping_output=$(ping -c 1 8.8.8.8 | grep "time=")
        if [ "$current_ping_output" != "$last_ping_output" ]; then
            last_ping_output="$current_ping_output"
            bash "$STATUSBAR_SCRIPT"
        fi
        sleep 5
    done
}

# Function to run the script every time a new minute begins
minute_listener() {
    while true; do
        sleep $((60 - $(date +%S)))  # Sleep until the next minute starts
        bash "$STATUSBAR_SCRIPT"
    done
}

# Function to listen for volume changes and run the script
volume_listener() {
    pactl subscribe | grep --line-buffered "sink" | while read -r event; do
        bash "$STATUSBAR_SCRIPT"
    done
}

# Function to monitor Spotify and run the script on state/song changes
spotify_listener() {
    spotify_running=false
    current_song=""
    previous_status=""

    while true; do
        # Check if Spotify is running
        playerctl --list-all | grep -q spotify
        spotify_detected=$?

        if [ $spotify_detected -eq 0 ]; then
            if [ "$spotify_running" = false ]; then
                spotify_running=true
                bash "$STATUSBAR_SCRIPT"
            fi

            # Check playback status
            playback_status=$(playerctl --player=spotify status 2>/dev/null || echo "Stopped")
            if [ "$playback_status" != "$previous_status" ]; then
                previous_status="$playback_status"
                bash "$STATUSBAR_SCRIPT"
            fi

            # Check current song
            new_song=$(playerctl --player=spotify metadata --format "{{artist}} - {{title}}" 2>/dev/null || echo "")
            if [ "$new_song" != "$current_song" ]; then
                current_song="$new_song"
                bash "$STATUSBAR_SCRIPT"
            fi
        else
            if [ "$spotify_running" = true ]; then
                spotify_running=false
                bash "$STATUSBAR_SCRIPT"
            fi
        fi

        sleep 2
    done
}

# Run all listeners in the background
ping_listener &
minute_listener &
volume_listener &
spotify_listener &

# Wait for all background processes to complete
wait
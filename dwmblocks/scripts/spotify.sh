#!/bin/bash

PLAYER="spotify"
FORMAT="{{ title }} - {{ artist }}"  # Format for currently playing song
NOT_PLAYING_TEXT="Not Playing"       # Text to show when no song is playing
MAX_LENGTH=20            # Set the maximum number of characters to display
RESET="^c#393552^"
COLOR="^c#ea9a97^"
ICON="  "

# Get the player status using playerctl
PLAYERCTL_STATUS=$(playerctl --player=$PLAYER status 2>/dev/null)

# Display appropriate output based on the playback status
if [ "$PLAYERCTL_STATUS" = "Playing" ]; then
    # Get the current song info
    TITLE=$(playerctl --player=$PLAYER metadata --format "$FORMAT")
    
    # Check if the title length exceeds MAX_LENGTH
    if [ ${#TITLE} -gt $MAX_LENGTH ]; then
        # Truncate and add ellipsis
        TRUNCATED_TITLE="${TITLE:0:$((MAX_LENGTH - 3))}..."
        echo -e "$COLOR$ICON$TRUNCATED_TITLE$RESET"
    else
        # Display the full title if within the limit
        echo -e "$COLOR$ICON$TITLE$RESET"
    fi
elif [ "$PLAYERCTL_STATUS" = "Paused" ]; then
    echo -e "$COLOR$ICON$NOT_PLAYING_TEXT$RESET"  # Display "Not Playing" when paused
else
    echo -e "$COLOR$ICON$NOT_PLAYING_TEXT$RESET"  # Display "Not Playing" when Spotify is inactive or there's an error
fi
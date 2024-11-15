#!/bin/bash
RESET="^c#393552^"
COLOR="^c#e0def4^"

# Ping Google once and capture the output
ping_output=$(ping -c 1 google.com 2>&1)

# Check if the output contains "Temporary failure in name resolution" or other errors
if echo "$ping_output" | grep -q "Temporary failure in name resolution\|Name or service not known\|100% packet loss"; then
    # Not connected
    echo "$COLOR󱘖  Not Connected$RESET"
else
    # Connected
    echo "$COLOR  Connected$RESET"
fi
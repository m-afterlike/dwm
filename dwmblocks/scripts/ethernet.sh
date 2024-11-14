#!/bin/bash
RESET="^c#393552^"
echo -e "GET http://google.com HTTP/1.0\n\n" | nc google.com 80 > /dev/null 2>&1

if [ $? -eq 0 ]; then
    #not connected
    echo "󱘖  Not Connected$RESET"
else
    #connected
    echo "  Connected$RESET"
fi
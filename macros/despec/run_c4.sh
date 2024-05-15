#!/bin/bash

while true; do
        root -b -q s143_online.C

        if [ $? -ne 0 ]; then
                echo "s143_online macro crashed or quit unexpectedly. Restarting..."
        else
                echo "s143_online macro completed successfully. Restarting, CTRL+C to quit process."
        fi

        sleep 5
done

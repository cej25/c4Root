#!/bin/bash

while true; do
        root -b -q s101_online.C

        if [ $? -ne 0 ]; then
                echo "s101_online macro crashed or quit unexpectedly. Restarting..."
        else
                echo "s101_online macro completed successfully. Restarting, CTRL+C to quit process."
        fi

        sleep 5
done

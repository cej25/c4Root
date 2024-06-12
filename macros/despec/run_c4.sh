#!/bin/bash

while true; do
        root -b -q s181_online.C

        if [ $? -ne 0 ]; then
                echo "s181_online macro crashed or quit unexpectedly. Restarting..."
        else
                echo "s181_online macro completed successfully. Restarting, CTRL+C to quit process."
        fi

        sleep 5
done

#!/bin/bash

while true; do
        root -b -q s100_online_new.C

        if [ $? -ne 0 ]; then
                echo "s100_online macro crashed or quit unexpectedly. Restarting..."
        else
                echo "s100_online macro completed successfully. Restarting, CTRL+C to quit process."
        fi

        sleep 5
done

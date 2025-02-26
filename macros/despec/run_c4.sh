#!/bin/bash

while true; do
        root -l -b s115_online.C

        if [ $? -ne 0 ]; then
                echo "s115_online macro crashed or quit unexpectedly. Restarting..."
        else
                echo "s115_online macro completed successfully. Restarting, CTRL+C to quit process."
        fi

        sleep 5
done

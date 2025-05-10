#!/bin/bash

while true; do
        root -l -b -q s103_online.C

        if [ $? -ne 0 ]; then
                echo "s103_online macro crashed or quit unexpectedly. Restarting..."
        else
                echo "s103_online macro completed successfully. Restarting, CTRL+C to quit process."
        fi

        sleep 5
done

#!/bin/bash
tog=0
prev_msg_counts=$(dmesg | wc -l)
log_counter=0

# Function to log new dmesg messages
log_new_dmesg_messages() {
    msg_counts=$(dmesg| wc -l)
    new_msg_counts=$(($msg_counts-$prev_msg_counts))
    log_counter=$(($new_msg_counts+$log_counter))

    if [ $new_msg_counts -gt 0 ]; then
        new_messages=$(dmesg | tail -n $new_msg_counts)

        echo "$new_messages" >> dmesg_log.txt
        if [ $log_counter -ge 10 ]; then
            if [ $tog -eq 0 ]; then
                echo 1 > /sys/class/leds/input3::capslock/brightness
                tog=1
            else
                echo 0 > /sys/class/leds/input3::capslock/brightness
                tog=0
            fi
            # clear the log file if it exceeds a 10 messages
            echo "=======================COUNTS-REACHED==========================" >> dmesg_log.txt
            log_counter=0
        fi
    fi
    
    prev_msg_counts=$msg_counts
}

# Continuously monitor and log new dmesg messages
while true; do
    log_new_dmesg_messages
    sleep 1
done










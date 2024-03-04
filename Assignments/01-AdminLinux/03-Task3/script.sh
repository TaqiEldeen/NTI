#!/bin/bash

if [ -f "$HOME/.bashrc" ]; then
    echo ".bashrc file exists in the home directory."

    if grep -q "HELLO" "$HOME/.bashrc" && grep -q "LOCAL" "$HOME/.bashrc"; then
        echo "Variables Already Exists!!"

    else 
        echo "HELLO=$HOSTNAME" >> "$HOME/.bashrc"
        echo "LOCAL=$(whoami)" >> "$HOME/.bashrc"
        echo "Environment variables appended to .bashrc."
    fi

    # the & used to make it run in the background 
    gnome-terminal &
    
else
    echo ".bashrc file does not exist in the home directory."
fi
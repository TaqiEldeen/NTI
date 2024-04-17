#!/bin/bash

user_name=$1
group='FamilyGroup'

if ["$#" -eq 0]
then
    echo "Please add argument of the user name"
    exit 
fi

if cat /etc/group | grep -q $group 
then
    echo "group exist"
else
    echo "Creating group 'FamilyGroup'"
    sudo groupadd FamilyGroup
fi

if cut -d':' -f 1 /etc/passwd | grep -q $user_name 
then
    echo "User Exist"
    echo "Exiting..."
    exit
else
    sudo adduser $user_name
    sudo usermod -aG $group $user_name

    # Display relevant info for the user and group
    id $user_name

    getent group $group
fi 


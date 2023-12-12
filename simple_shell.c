#!/bin/bash

while true; do
    
    echo -n "simple_shell> "

    read command

    if [ -z "$command" ]; then
        echo "Exiting shell. Goodbye!"
        break
    fi

    if command -v "$command" &> /dev/null; then
        
        $command
    else
        echo "Command not found: $command"
    fi

done 

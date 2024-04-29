# Get a list of all commands in the shell history
commands=$(history | cut -c 8-)

# Process the list to extract individual commands and count their occurrences
declare -A command_count
for command in $commands; do
    if [[ ${command_count[$command]} ]]; then
        ((command_count[$command]++))
    else
        command_count[$command]=1
    fi
done

# Generate a frequency list of all commands
frequency_list=""
for command in "${!command_count[@]}"; do
    frequency_list+="$command:${command_count[$command]}\n"
done

# Sort the frequency list in descending order based on command counts
sorted_list=$(echo -e "$frequency_list" | sort -rn -k2)

# Display the top 5 commands along with their counts
echo -e "Top 5 commands:"
echo -e "$sorted_list" | head -n 5



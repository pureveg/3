# Open the file
with open("10cuos.txt") as f:
    d = {}
    # Process each line in the file
    for line in f:
        # Split the line into words
        l = line.split()
        # Process each word
        for word in l:
            # Update the word count
            if word in d:
                d[word] = d[word] + 1
            else:
                d[word] = 1
    # Print the word counts
    for key in d:
        print(key, " : ", d[key])


o/P:
This : 1
is : 1
UOS : 1
assignment : 1
10c : 1
. : 1
TY : 2
IT : 2
WCE : 2
sangli. : 1
Unix : 2


cmd:
python word_count.py


if python3 then:
python3 word_count.py


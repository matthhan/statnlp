cat $1 | 
    sed -e "s/[[:punct:]]/\ &\ /g" | #put spaces before and after each piece of punctuation
    sed -e "s/[[:space:]]/\\n/g" | #replace every space with newline
    grep . | #Only take the lines that actually contain something (i.e. remove duplicate newlines)
    tr '[:upper:]' '[:lower:]' > preprocessed.txt #replace everything by lowercase


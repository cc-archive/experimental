#/bin/bash

# The idea here is to generate a list of all files with translatable strings in
# them to make this whole thing faster and to track down any problems with 
# strings that are not found.

# TODO: The idea here is to have a list of fitetypes to include and also those
# to exclude.
#
# TODO: I dunno why this thing still won't get the searches, but the solution
# is close. After that, then just copy what is done for the INCLUDE set for 
# the exclude set
#

INCLUDE="php inc"
EXCLUDE=

SEARCH=

# echo $INCLUDE

for i in $INCLUDE;
do 
    if [ '' != "$SEARCH" ]; then
        SEARCH="$SEARCH -o"
    fi
    # echo $i
    SEARCH="$SEARCH -name \"*.$i\"" 
done

echo $SEARCH

#if [ -x "$SEARCH" ]; then
#    exit 1
#fi

echo "find .$SEARCH | xargs grep -l \"_(.*)\" | sort"

find .$SEARCH | xargs grep -l "_(.*)" | sort

exit 0

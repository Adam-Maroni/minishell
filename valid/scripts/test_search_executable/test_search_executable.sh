#!/bin/bash

OUTPUT=test_search_executable
VALID_CODE=0
INVALID_CODE=1

GREEN_TEXT="\e[92m"
DEFAULT_TEXT="\e[0m"
RED_TEXT="\e[31m"
BOLD_TEXT="\e[1m"

#param1 = cmd
#param2 = expected returned value
function test_case {
	make
	valgrind -q ./$OUTPUT $1
	RETURN_CODE=$?
	echo -n "'$1' => "
	if [ $RETURN_CODE == $2 ]; then 
		echo -e "$GREEN_TEXT Alright $DEFAULT_TEXT"
	else
		echo -e "$RED_TEXT Not found $DEFAULT_TEXT"
	fi
	rm $OUTPUT
}

echo
echo -e "$BOLD_TEXT----------Valid commands----------$DEFAULT_TEXT"
test_case "pwd" $VALID_CODE
test_case "echo" $VALID_CODE
test_case "ls" $VALID_CODE
test_case "cat" $VALID_CODE
test_case "bash" $VALID_CODE
echo -e "$BOLD_TEXT----------Invalid commands----------$DEFAULT_TEXT"
test_case "dfghnjmk,l." $INVALID_CODE
test_case "123" $INVALID_CODE
test_case "       " $INVALID_CODE
test_case "" $INVALID_CODE
echo 


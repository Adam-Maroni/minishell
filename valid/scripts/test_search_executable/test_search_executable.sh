#!/bin/bash

OUTPUT=test_search_executable

GREEN_TEXT="\e[92m"
DEFAULT_TEXT="\e[0m"
RED_TEXT="\e[31m"
BOLD_TEXT="\e[1m"

function test_case {
	make
	./$OUTPUT $1
	RETURN_CODE=$?
	echo -n "$1 => "
	if [ $RETURN_CODE == 0 ]; then 
		echo -e "$GREEN_TEXT Alright $DEFAULT_TEXT"
	else
		echo -e "$RED_TEXT Not found $DEFAULT_TEXT"
	fi
	rm $OUTPUT
}

echo
echo -e "$BOLD_TEXT----------Should Return Alright----------$DEFAULT_TEXT"
test_case "pwd"
test_case "echo"
test_case "ls"
echo -e "$BOLD_TEXT----------Should Return Not found----------$DEFAULT_TEXT"
test_case "dfghnjmk,l."
test_case "123"
test_case "       "
echo 


#!/usr/bin/bash
#place in ft_containers directory or assign var FT_CONT
FT_CONT="./../"
TESTS="./tests/"
seed=$RANDOM
containers="vector.cpp map.cpp stack.cpp"
T_PATH="$(pwd)/tester/"
bonus=(set.cpp)
speed="speed/map.cpp speed/vector.cpp"
GREEN="\033[1;32m"
BLUE="\033[1;34m"
PURPLE="\033[1;35m"
WHITE="\033[0;37m"


if [[ $# -gt 2 ]]
then echo "Require one, two or no arguments\n";exit 
elif [[ -z $1 ]]
then TO_COMPILE="${containers}" #vector.cpp map.cpp stack.cpp pair.cpp \ #containers #iterators.cpp \ #iterators iterator_traits.cpp reverse_iterator.cpp
elif [ $1 = "bonus" ]
then TO_COMPILE=${bonus}
elif [ $1 = "all" ]
then TO_COMPILE="${containers} ${bonus} 42.cpp"
elif [ $1 = "speed" ]
then TO_COMPILE="${speed}"
else TO_COMPILE=$1.cpp
fi


if [ "$1" = "speed" ]
	then 
	for t in ${TO_COMPILE[@]}; do
	clang++ -Wall -Wextra -Werror -I. -I${FT_CONT} -std=c++98 ${T_PATH}/${t}  -D FT -o ${T_PATH}test_ft
	printf "ft ${t} took ${PURLE}"
	${T_PATH}/test_ft ${seed} 
	clang++ -Wall -Wextra -Werror -I. -I${FT_CONT} -std=c++98 ${T_PATH}/${t} -o ${T_PATH}test_std
	printf "std ${t} took ${PURLE}"
	${T_PATH}/test_std ${seed}
	rm -f ${T_PATH}/test_std  ${T_PATH}time_f ${T_PATH}time_std ${T_PATH}/test_ft
	rm -f ../test_std  ../test_ft
	done
	exit

fi

for t in ${TO_COMPILE[@]}; do
	clang++ -Wall -Wextra -Werror -I. -I${FT_CONT} -std=c++98 ${T_PATH}/${t}  -D FT -o test_ft
	start=`date +%s.%N`
	./test_ft ${seed} > ${T_PATH}/res/log_ft.txt  
	end=`date +%s.%N`
	ft=$( echo "$end - $start" | bc -l )
	
	clang++ -Wall -Wextra -Werror -I. -I${FT_CONT} -std=c++98 ${T_PATH}/${t} -o test_std
	start=`date +%s.%N`	clang++ -Wall -Wextra -Werror -I. -I${FT_CONT} -std=c++98 ${T_PATH}/${t}  -D FT -o test_ft
	clang++ -Wall -Wextra -Werror -I. -I${FT_CONT} -std=c++98 ${T_PATH}/${t} -o test_std

	./test_std ${seed} > ${T_PATH}/res/log_std.txt
	end=`date +%s.%N`
	std=$( echo "$end - $start" | bc -l )
	
	diff ${T_PATH}/res/log_std.txt ${T_PATH}/res/log_ft.txt >${T_PATH}/res/diff

	if [ $? -eq 0 ] 
		then
		printf "${PURPLE}${t} ${GREEN}OK ٩{˘◡˘}۶${WHITE}\n"
		if [ "$2" = "time" ]
		then
			e=$(awk "BEGIN {print ${ft}/${std}}") 
			printf "times : ft : ${ft}, std : ${std} => ft is ${e} times slower than std\n"
		fi
	else
		printf "${PURPLE}${t} ${BLUE}KO ಥ_ಥ${WHITE}\n"
	fi
	rm -f test_ft
	rm -f test_std
	rm -f ${T_PATH}/test_std  ${T_PATH}/test_ft

done
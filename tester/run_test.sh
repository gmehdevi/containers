#!bin/bash
#place in ft_containers directory or assign var FT_CONT
FT_CONT = "./../"
seed = $RANDOM
containers  = vector.cpp map.cpp stack.cpp pair.cpp
iter        = iterators.cpp
utils       = enable_if.cpp is_integral.cpp equal.cpp lexicographical_compare.cpp
bonus       = set.cpp

if [!($# -eq 0) && !($# -gt 1)]
  then
    echo "Require one or no arguments\n"
else if [-z "$1"]
  then
    TO_COMPILE =  $(containers) $(iter) $(utils) #vector.cpp map.cpp stack.cpp pair.cpp \ #containers
                    #iterators.cpp \ #iterators iterator_traits.cpp reverse_iterator.cpp
else if [$1 -eq "bonus"]
  then
    TO_COMPILE = $(bonus)
else if [$1 -eq "all"]
    then    
        TO_COMPILE =  $(containers) $(iter) $(utils) $(bonus)  
else if ($# -eq 1)
    then TO_COMPILE = $1.cpp
fi
printf "Seed: $(seed)\n"
clang++ -Wall -Wextra -Werror -I. -std=c++98 $(TO_COMPILE) -I$(FT_CONT) -D FT -o test_ft
./test $(seed) > ./res/log_ft
clang++ -Wall -Wextra -Werror -I. -std=c++98 $(TO_COMPILE) -I$(FT_CONT) -D -o test_std
./test $(seed) > ./res/log_std
diff ./res/log_std  ./res/log_ft
if [ $? -eq 0 ]
	then
		echo $1 "OK ✅"
	else
		echo $1 "KO ❌"
fi
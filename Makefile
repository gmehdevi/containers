CONTAINERS  	= vector map stack pair
iter        	= #iterators.cpp
utils       	= #enable_if.cpp is_integral.cpp equal.cpp lexicographical_compare.cpp
BONUS       	= set
FT_CONT 		= ./../

CXX				= clang++
RM				= rm -f
CXXFLAGS		= -Wall -Wextra -Werror -ferror-limit=2 -I. -std=c++98

NAME			= container_test

all:			
				./tester/run_test.sh all

time:
				./tester/run_test.sh all time
clean:
				$(RM) -f tester/test_ft tester/test_std
				$(RM) -f ${T_PATH}/test_std ${T_PATH}/test_ft
bonus:		
				./tester/run_test.sh bonus

fclean:			clean
				$(RM) -f ./tester/res/*
				$(RM) -f ${T_PATH}time_f ${T_PATH}time_std
re:				fclean $(NAME)

speed :			
				./tester/run_test.sh speed

.PHONY:			all clean fclean re test 42
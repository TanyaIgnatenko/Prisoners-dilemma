#include "user.h"
#include "enum.h"

int main(int argc, const char **argv)
{ 	
	Parser_Result result = User::instance()->command_line_parser(argc, argv);
	if(result.success)
	{
		return (User::instance()->user_interface(result.strategy_name, result.mode, result.steps, result.rules) == Result::Success);
		
	}
	return 1;
}

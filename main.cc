#include "user.h"
#include "enum.h"

int main(int argc, const char **argv)
{ 	
	if(User::instance()->command_line_parser(argc, argv) == Result::Success)
	{
		return 0;		
	}
	else
	{
		return 1;
	}

}

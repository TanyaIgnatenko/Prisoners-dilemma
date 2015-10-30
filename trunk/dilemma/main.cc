#include "user.h"
#include "enum.h"

int main(int argc, const char **argv)
{ 	
	user info;
	if(info.command_line_parser(argc, argv) == Result::Success)
	{
		return 0;		
	}
	else
	{
		return 1;
	}

}

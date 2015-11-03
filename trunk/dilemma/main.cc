#include "user.h"
#include "enum.h"

int main(int argc, const char **argv)
{ 	
	return (User::instance()->command_line_parser(argc, argv) == Result::Success);
}

#include "grid.h"
#include <iostream>
#include <string>
#include <cctype>
#include <cassert> 

using namespace std;

int performCommands(string commandString, char& plotChar, int& mode, int& badPos);//performs a command string
void plotHorizontalLine(int r, int c, int distance, char ch); //plots horizontal line starting at point (r,c)
void plotVerticalLine(int r, int c, int distance, char ch); //plots vertical line starting at point (r,c)
void plotRectangle(int r, int c, int height, int width, char ch); //plots a rectange with upper left corner being (r,c)
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg); //plots a line in any given direction and location on the grid

const int HORIZ = 0; //horizontal direction argument input (global)
const int VERT = 1; //vertical direction argument input (global)

const int FG = 0; //foreground, char replaces any char in place (global)
const int BG = 1; //background, char replaces "_", but not any other char in place (global)

int main()
{
	setSize(20, 30);
	char currentChar = '*';
	int currentMode = FG;
	for (;;)
	{
		cout << "Enter a command string: ";
		string cmd;
		getline(cin, cmd);
		if (cmd == "")
			break;
		int position;
		int status = performCommands(cmd, currentChar, currentMode, position);
		switch (status)
		{
		case 0:
			draw();
			break;
		case 1:
			cout << "Syntax error at position " << position + 1 << endl;
			break;
		case 2:
			cout << "Cannot perform command at position " << position + 1 << endl;
			break;
		default:
			// It should be impossible to get here.
			cerr << "performCommands returned " << status << "!" << endl;
		}
	}
}


/* Function takes 4 arguments, a command, character, mode, and position. Command string is read 
and executed based on a sequence of commands. If all commands execute with no error, the function will 
return an int 0, otherwise the function may return a 1 or 2*/
int performCommands(string commandString, char& plotChar, int& mode, int& badPos)
{
	int row = 1; //function starts at row 1
	int col = 1; //function starts at column 1
	int dis;
	bool commandError = true;
	int cePosition = 0;

	for (int l = 0; l < commandString.size(); l++)
	{
		if (commandString[l] == 'v' || commandString[l] == 'V') //evaluates for vertical line command
		{
			if (commandString[l + 1] == '-' && isdigit(commandString[l + 2]) && isdigit(commandString[l + 3])) //a minus sign followed by two digit characters
			{
				dis = -1 * ((commandString[l + 2] - '0') * 10 + (commandString[l + 3] - '0'));
				if (plotLine(row, col, dis, VERT, plotChar, mode))
					row += dis;
				else //command error is made
				{
					cePosition = l;
					commandError = false;
				}
				l = l + 3;
				dis = 0;
				continue;
			}
			else if (commandString[l + 1] == '-' && isdigit(commandString[l + 2])) //a minus sign followed by one digit character
			{
				dis = -1 * ((commandString[l + 2] - '0'));
				if (plotLine(row, col, dis, VERT, plotChar, mode))
					row += dis;
				else //command error is made
				{
					cePosition = l;
					commandError = false;
				}
				l = l + 2;
				dis = 0;
				continue;
			}
			else if (isdigit(commandString[l + 1]) && isdigit(commandString[l + 2])) //two digit character
			{
				dis = ((commandString[l + 1] - '0') * 10 + (commandString[l + 2] - '0'));
				if (plotLine(row, col, dis, VERT, plotChar, mode))
					row += dis;
				else //command error is made
				{
					cePosition = l;
					commandError = false;
				}
				l = l + 2;
				dis = 0;
				continue;
			}
			else if (isdigit(commandString[l + 1])) //one digit character
			{
				dis = (commandString[l + 1] - '0');
				if (plotLine(row, col, dis, VERT, plotChar, mode))
					row += dis;
				else //command error is made
				{
					cePosition = l;
					commandError = false;
				}
				l = l + 1;
				dis = 0;
				continue;
			}
			else
			{
				badPos = l + 1;
				return 1;
			}
		}

		if (commandString[l] == 'h' || commandString[l] == 'H') //evaluates for horizontal line command
		{
			if (commandString[l + 1] == '-' && isdigit(commandString[l + 2]) && isdigit(commandString[l + 3])) //a minus sign followed by two digit characters
			{
				dis = -1 * ((commandString[l + 2] - '0') * 10 + (commandString[l + 3] - '0'));
				if (plotLine(row, col, dis, HORIZ, plotChar, mode))
					col += dis;
				else //if plotLine does not return true, command error is made
				{
					cePosition = l;
					commandError = false;
				}
				l = l + 3;
				dis = 0;
				continue;
			}
			else if (commandString[l + 1] == '-' && isdigit(commandString[l + 2])) //a minus sign followed by one digit character
			{
				dis = -1 * ((commandString[l + 2] - '0'));
				if (plotLine(row, col, dis, HORIZ, plotChar, mode))
					col += dis;
				else //if plotLine does not return true, command error is made
				{
					cePosition = l;
					commandError = false;
				}
				l = l + 2;
				dis = 0;
				continue;
			}
			else if (isdigit(commandString[l + 1]) && isdigit(commandString[l + 2])) //two digit character
			{
				dis = ((commandString[l + 1] - '0') * 10 + (commandString[l + 2] - '0'));
				if (plotLine(row, col, dis, HORIZ, plotChar, mode))
					col += dis;
				else //if plotLine does not return true, command error is made
				{
					cePosition = l;
					commandError = false;
				}
				l = l + 2;
				dis = 0;
				continue;
			}
			else if (isdigit(commandString[l + 1])) //one digit character
			{
				dis = (commandString[l + 1] - '0');
				if (plotLine(row, col, dis, HORIZ, plotChar, mode))
					col += dis;
				else //if plotLine does not return true, command error is made
				{
					cePosition = l;
					commandError = false;
				}
				l = l + 1;
				dis = 0;
				continue;
			}
			else
			{
				badPos = l + 1;
				return 1;
			}
		}

		if (commandString[l] == 'f' || commandString[l] == 'F') //changes current mode to foreground and plotChar to a desired character
		{
			if (isprint(commandString[l + 1]))
			{
				mode = FG; 
				plotChar = commandString[l + 1];
				l++;
				continue;
			}
			else
			{
				badPos = l + 1;
				return 1;
			}
		}
		if (commandString[l] == 'b' || commandString[l] == 'B') //changes current mode to background and plotChar to a desired character
		{
			if (isprint(commandString[l + 1]))
			{
				mode = BG;
				plotChar = commandString[l + 1];
				l++;
				continue;
			}
			else
			{
				badPos = l + 1;
				return 1;
			}
		}
		if (commandString[l] == 'c' || commandString[l] == 'C') //resets the grid settings to default (grid, mode, plotchar, position)
		{
			clearGrid();
			row = 1;
			col = 1;
			plotChar = '*';
			mode = FG;
			continue;
		}

		else
		{
			badPos = l;
			return 1;
		}
	}
	if (! (commandError)) //return 2 if a command error is made
	{
		badPos = cePosition;
		return 2;
	}
	else 
		return 0;
}

void plotHorizontalLine(int r, int c, int distance, char ch)
{
	for (int d = 0; d <= distance; d++)
	{
		setChar(r, c, ch);
		c++;
	}
}
void plotVerticalLine(int r, int c, int distance, char ch)
{
	for (int d = 0; d <= distance; d++)
	{
		setChar(r, c, ch);
		r++;
	}
}
void plotRectangle(int r, int c, int height, int width, char ch)
{
	plotHorizontalLine(r, c, width, ch);
	plotVerticalLine(r, c, height, ch);
	plotVerticalLine(r, (c + height), width, ch);
	plotHorizontalLine((r + width), c, height, ch);
}

/*Function plotLine plots a line given the parameters
of one endpoint, length, direction (vert or horiz),
character being plotted, and whether this line will be in the
background or foreground.*/
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg)
{
	if (dir == 0) //checks direction horizontal
	{
		if (c + distance > getCols() || c + distance < 1) //Checks to make sure the horizontal line drawn is within bound
			return false;

		if (distance >= 0) //line will be drawn left to right
		{
			for (int d = 0; d <= distance; d++)
			{
				if (fgbg == 0) //character will replace any character in place
				{
					setChar(r, c, plotChar);
					c++;
				}

				else if (fgbg == 1) //character will only replace '_'
				{
					if (getChar(r, c) == ' ')
					{
						setChar(r, c, plotChar);
						c++;
					}
					else 
					{
						setChar(r, c, getChar(r, c));
						c++;
					}
				}
				else
					return false; //if FGBG != 0 or 1, return false
			}
		}

		else if (distance < 0) //line will be drawn right to left
		{
			for (int d = 0; d >= distance; d--)
			{
				if (fgbg == 0) //character will replace any character in place
				{
					setChar(r, c, plotChar);
					c--;
				}

				else if (fgbg == 1) //character will only replace "_"
				{
					if (getChar(r, c) == ' ')
					{
						setChar(r, c, plotChar);
						c--;
					}
					else
					{
						setChar(r, c, getChar(r, c));
						c--;
					}
				}
				else
					return false; //if FGBG != 0 or 1, return false
			}
		}
	}

	else if (dir == 1) //checks direction vertical
	{
		if (r + distance > getRows() || r + distance < 1) //Checks to make sure vertical line drawn is within bound
			return false;

		if (distance >= 0) //line will be drawn top to bottom
		{
			for (int d = 0; d <= distance; d++)
			{
				if (fgbg == 0) //character will replace any character in place
				{
					setChar(r, c, plotChar);
					r++;
				}

				else if (fgbg == 1) //character will only replace "_"
				{
					if (getChar(r, c) == ' ')
					{
						setChar(r, c, plotChar);
						r++;
					}
					else
					{
						setChar(r, c, getChar(r, c));
						r++;
					}
				}
				else
					return false; //if FGBG != 0 or 1, return false
			}
		}

		else if (distance < 0) //line will be drawn bottom to top
		{
			for (int d = 0; d >= distance; d--)
			{
				if (fgbg == 0) //character will replace any character in place
				{
					setChar(r, c, plotChar);
					r--;
				}
				else if (fgbg == 1) //character will only replace "_"
				{
					if (getChar(r, c) == ' ')
					{
						setChar(r, c, plotChar);
						r--;
					}
					else
					{
						setChar(r, c, getChar(r, c));
						r--;
					}
				}
				else
					return false; //if FGBG != 0 or 1, return false
			}
		}
	}
	else 
		return false;
		
	return true;
}

	
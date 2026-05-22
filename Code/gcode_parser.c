#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gcode_parser.h"

MotionCommand commands[MAX_COMMANDS];

int commandCount = 0;

void parseGcodeLine(char* line)
{
    if(commandCount >= MAX_COMMANDS)
        return;

    MotionCommand cmd;

    cmd.x = 0;
    cmd.y = 0;
    cmd.z = 0;

    cmd.a = 0;
    cmd.b = 0;
    cmd.c = 0;

    cmd.feed = 0;

    cmd.motion = -1;

    char* token = strtok(line, " ");

    while(token != NULL)
    {
        switch(token[0])
        {
            case 'G':
                cmd.motion = atoi(&token[1]);
                break;

            case 'X':
                cmd.x = atof(&token[1]);
                break;

            case 'Y':
                cmd.y = atof(&token[1]);
                break;

            case 'Z':
                cmd.z = atof(&token[1]);
                break;

            case 'A':
                cmd.a = atof(&token[1]);
                break;

            case 'B':
                cmd.b = atof(&token[1]);
                break;

            case 'C':
                cmd.c = atof(&token[1]);
                break;

            case 'F':
                cmd.feed = atof(&token[1]);
                break;
        }

        token = strtok(NULL, " ");
    }

    commands[commandCount] = cmd;

    commandCount++;
}
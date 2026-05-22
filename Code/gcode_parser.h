#ifndef GCODE_PARSER_H
#define GCODE_PARSER_H

#define MAX_COMMANDS 2000

typedef struct
{
    float x;
    float y;
    float z;

    float feed;

    int motion;

} MotionCommand;

extern MotionCommand commands[MAX_COMMANDS];

extern int commandCount;

void parseGcodeLine(char* line);

#endif
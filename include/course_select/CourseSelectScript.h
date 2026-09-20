#pragma once

#include <types.h>

struct CourseSelectScriptCommand {
    u32 type;
    u32 arg;
};

struct CourseSelectScript {
    u32 priority;
    CourseSelectScriptCommand* script_start;
};

extern const CourseSelectScript scWorldMapScripts[121];

struct CourseSelectCommand {
    enum Commands {
        ShowMiiverseSetup = 311,
        End = 344
    };
};

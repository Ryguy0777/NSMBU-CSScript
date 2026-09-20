#pragma once

#include <course_select/CourseSelectScript.h>
#include <actor/ActorUniqueID.h>
#include <heap/seadDisposer.h>

class CourseSelectScriptMgr {
    SEAD_SINGLETON_DISPOSER(CourseSelectScriptMgr)

public:
    bool isRunningScript();

    u32 getCurrentScriptID() {
        return mCurrentScriptID;
    }

    u32 getCurrentCommandIndex() {
        return mCurrentCommandIndex;
    }
protected:
    u8              _10[80][16];         // Array of 16 CLASS_21e5118
    u32             mCurrentScriptID;
    u8              _514[4];
    u8              _518[4][18];         // Array of 18 CLASS_21e50dc
    u32             mCurrentCommandIndex;
    s32             _564;
    u8              _568[4];             // Unknown values
    ActorUniqueID   mEventAssistantID;   // Actor ID of the event assistant (Profile 909)
};
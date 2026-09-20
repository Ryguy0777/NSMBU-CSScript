#include <csscript/CSScript.h>
#include <course_select/CourseSelectScriptMgr.h>
#include <csscript/actor/CourseSelectScriptLoader.h>

red::Registrar* csscript::getRegistrar() {
    static red::Registrar sRegistrar("csscript");
    return &sRegistrar;
}

void main() { }

namespace csscript {

u32 getCurrentCommandArg(CourseSelectScriptMgr* mgr) {
    u32 out = 0xFFFFFFFF;
    if (mgr->isRunningScript()) {
        ResultID result = CourseSelectScriptLoader::customScriptExists(mgr->getCurrentScriptID());
        if (result.result) {
            out = CourseSelectScriptLoader::getWMScriptFile()->mScripts[result.id].script_start[mgr->getCurrentCommandIndex()].arg;
        } else {
            out = scWorldMapScripts[mgr->getCurrentScriptID()].script_start[mgr->getCurrentCommandIndex()].arg;
        }
    }

    return out;
}
tBranch(0x021E4AFC, getCurrentCommandArg, tk::BranchType::b);

u32* getCurrentScriptCommandType(CourseSelectScriptMgr* mgr, u32* out) {
    if (mgr->isRunningScript()) {
        ResultID result = CourseSelectScriptLoader::customScriptExists(mgr->getCurrentScriptID());
        if (result.result) {
            if (out || (out = new u32, out)) {
                *out = CourseSelectScriptLoader::getWMScriptFile()->mScripts[result.id].script_start[mgr->getCurrentCommandIndex()].type;
            }
        } else {
            if (out || (out = new u32, out)) { // TODO: check
                *out = scWorldMapScripts[mgr->getCurrentScriptID()].script_start[mgr->getCurrentCommandIndex()].type;
            }
        }
    } else {
        if (out || (out = new u32, out)) {
            *out = 0;
        }
    }

    return out;
}
tBranch(0x021E42FC, getCurrentScriptCommandType, tk::BranchType::b);

u32 getScriptPriority(CourseSelectScriptMgr* mgr, u32& tableIndex) {
    ResultID result = CourseSelectScriptLoader::customScriptExists(tableIndex);
    if (result.result) {
        return CourseSelectScriptLoader::getWMScriptFile()->mScripts[result.id].priority;
    } else {
        return scWorldMapScripts[tableIndex].priority;
    }
}
tBranch(0x021E4B50, getScriptPriority, tk::BranchType::b);

} // namespace csscript

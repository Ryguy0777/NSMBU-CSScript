#pragma once

#include <actor/ActorCreateParam.h>
#include <course_select/CourseSelectActor.h>
#include <actor/Profile.h>
#include <csscript/Cobra.h>

namespace csscript {

struct ResultID {
    ResultID() : result(false), id(0) { }
    bool result;
    u32 id;
};

class CourseSelectScriptLoader : public CourseSelectActor {
    SEAD_RTTI_OVERRIDE(CourseSelectScriptLoader, CourseSelectActor);

public:
    static Profile* sProfile;

    CourseSelectScriptLoader(const ActorCreateParam& param);
    ~CourseSelectScriptLoader() override = default;

    Result create() override;

    static WMSFile* getWMScriptFile() { return mInstance->mWMScFile; }
    static ResultID customScriptExists(u32 scriptID);

    static CourseSelectScriptLoader* mInstance;

private:
    WMSFile* mWMScFile;
};
 
} // namespace csscript

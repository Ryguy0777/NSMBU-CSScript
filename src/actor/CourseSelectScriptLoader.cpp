#include <csscript/actor/CourseSelectScriptLoader.h>
#include <csscript/CSScript.h>
#include <actor/ActorMgr.h>
#include <telkin/Hooks.h>

namespace csscript {

CourseSelectScriptLoader* CourseSelectScriptLoader::mInstance = nullptr;

void createScriptLoader() {
    ActorCreateParam CourseSelectScriptLoader;
    CourseSelectScriptLoader.profile = CourseSelectScriptLoader::sProfile;

    ActorMgr::instance()->createImmediately(CourseSelectScriptLoader);
}

tBranch(0x021E3CFC, createScriptLoader, tk::BranchType::b);

SEAD_RTTI_OVERRIDE_IMPL(CourseSelectScriptLoader, CourseSelectActor);

Profile* CourseSelectScriptLoader::sProfile = getRegistrar()->newProfile<CourseSelectScriptLoader>("csscriptloader")
    .build();

CourseSelectScriptLoader::CourseSelectScriptLoader(const ActorCreateParam& param)
    : CourseSelectActor(param)
    , mWMScFile(nullptr)
{ }

ActorBase::Result CourseSelectScriptLoader::create() {
    mInstance = this;
    mWMScFile = new WMSFile(mActorHeap);

    return cResult_Success;
}

ResultID CourseSelectScriptLoader::customScriptExists(u32 scriptID) {
    ResultID result;

    for (u32 i = 0; i < mInstance->mWMScFile->mHeader.num_scripts; i++) {
        if (mInstance->mWMScFile->mScriptIDs[i] == scriptID) {
            result.id = i;
            result.result = true;

            return result;
        }
    }

    return result;
}

} // namespace csscript
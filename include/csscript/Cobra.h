#pragma once

// Holds structs and code for dealing with files outputted by Cobra (https://github.com/RoadrunnerWMC/Cobra)

#define COBRA_MAGIC "WMS"
#define COBRA_VERSION '0'
#define COBRA_GAME 'U'
#define COBRA_VARIANT "130"

#include <telkin/Telkin.h>
#include <course_select/CourseSelectScript.h>
#include <sead/engine/library/include/heap/seadHeap.h>
#include <sead/engine/library/include/filedevice/seadFileDevice.h>
#include <sead/engine/library/include/filedevice/seadFileDeviceMgr.h>

class WMSFile {
public:
    struct Header {
        char magic[3];
        char version;
        char game;
        char game_variant[3];
        u32 file_size;
        u32 num_scripts;
    };

    WMSFile(sead::Heap* heap) {
        sead::FileHandle handle;
        sead::FileDevice* device = sead::FileDeviceMgr::instance()->tryOpen(&handle, "course_select/scripts.wmsc", sead::FileDevice::cFileOpenFlag_ReadOnly, 0);

        const s32 align = sead::FileDevice::cBufferMinAlignment;

        if (!handle.getDevice()) {
            tk::println("course_select/scripts.wmsc not found, falling back to original game scripts!");
            return;
        }

        u8* headerBuffer = (u8*)heap->tryAlloc(sizeof(Header), align);
        u32 bytesRead = handle.read(reinterpret_cast<u8*>(headerBuffer), sizeof(Header));
        OSBlockMove(&mHeader, headerBuffer, sizeof(Header), false);

        if (bytesRead != sizeof(Header)) {
            tk::fatal("scripts.wmsc header read size mismatch, read size: %x, expected size: %x", bytesRead, sizeof(Header));
        }

        if (std::memcmp(mHeader.magic, COBRA_MAGIC, sizeof(mHeader.magic)) != 0) {
            tk::fatal("scripts.wmsc header magic invalid!");
        }

        if (mHeader.version != COBRA_VERSION) {
            tk::fatal("scripts.wmsc version invalid, only version %c supported!", COBRA_VERSION);
        }

        if (mHeader.game != COBRA_GAME) {
            tk::fatal("scripts.wmsc is for the wrong game, only NSMBU is supported!");
        }

        if (std::memcmp(mHeader.game_variant, COBRA_VARIANT, sizeof(mHeader.game_variant)) != 0) {
            tk::fatal("scripts.wmsc is for the wrong game variant, only %s is supported!", COBRA_VARIANT);
        }

        u32* scriptIDBuffer = (u32*)heap->tryAlloc(sizeof(u32) * mHeader.num_scripts, align);
        CourseSelectScript* scriptBuffer = (CourseSelectScript*)heap->tryAlloc(sizeof(CourseSelectScript) * mHeader.num_scripts, align);

        bytesRead = handle.read(reinterpret_cast<u8*>(scriptIDBuffer), sizeof(u32) * mHeader.num_scripts);

        if (bytesRead != sizeof(u32) * mHeader.num_scripts) {
            tk::fatal("scripts.wmsc script ID read size mismatch, read size: %x, expected size: %x", bytesRead, sizeof(u32) * mHeader.num_scripts);
        }

        bytesRead = handle.read(reinterpret_cast<u8*>(scriptBuffer), sizeof(CourseSelectScript) * mHeader.num_scripts);

        if (bytesRead != sizeof(CourseSelectScript) * mHeader.num_scripts) {
            tk::fatal("scripts.wmsc script read size mismatch, read size: %x, expected size: %x", bytesRead, sizeof(u32) * mHeader.num_scripts);
        }

        mScriptIDs = (u32*)heap->tryAlloc(sizeof(u32) * mHeader.num_scripts, sizeof(u32));
        OSBlockMove(mScriptIDs, scriptIDBuffer, sizeof(u32) * mHeader.num_scripts, false);

        mScripts = (CourseSelectScript*)heap->tryAlloc(sizeof(CourseSelectScript) * mHeader.num_scripts, sizeof(CourseSelectScript));
        OSBlockMove(mScripts, scriptBuffer, sizeof(CourseSelectScript) * mHeader.num_scripts, false);

        u32 dataSize = mHeader.file_size - sizeof(Header) - (sizeof(u32) * mHeader.num_scripts) - (sizeof(CourseSelectScript) * mHeader.num_scripts);

        u8* scriptDataBuffer = (u8*)heap->tryAlloc(dataSize, align);

        bytesRead = handle.read(reinterpret_cast<u8*>(scriptDataBuffer), dataSize);

        if (bytesRead != dataSize) {
            tk::fatal("scripts.wmsc script data read size mismatch, read size: %x, expected size: %x", bytesRead, dataSize);
        }

        mScriptsData = (CourseSelectScriptCommand*)heap->tryAlloc(dataSize, sizeof(CourseSelectScriptCommand));
        OSBlockMove(mScriptsData, scriptDataBuffer, dataSize, false);

        u32 fileOffsetToScriptsData = sizeof(Header) + (sizeof(u32) * mHeader.num_scripts) + (sizeof(CourseSelectScript) * mHeader.num_scripts);
        for (u32 i = 0; i < mHeader.num_scripts; i++) {
            u32* ptrToScriptStart = (u32*)(&mScripts[i].script_start);
            *ptrToScriptStart -= fileOffsetToScriptsData;
            *ptrToScriptStart += (u32)(mScriptsData);
        }

        heap->free(headerBuffer);
        heap->free(scriptIDBuffer);
        heap->free(scriptBuffer);
        heap->free(scriptDataBuffer);
    }

    Header mHeader;
    u32* mScriptIDs;
    CourseSelectScript* mScripts;
    CourseSelectScriptCommand* mScriptsData;
};

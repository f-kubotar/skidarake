#ifndef __kawaii__sprite_frame_cache__
#define __kawaii__sprite_frame_cache__

#include "hashed_string.h"

#include <map>
#include <set>

namespace kawaii {

class SpriteFrame;

class SpriteFrameCache {
public:
    static inline SpriteFrameCache *Shared() {
        if (__shared == NULL) {
            __shared = new SpriteFrameCache;
        }
        return __shared;
    }

    bool AddSpriteFramesWithFile(const string& json_path);
    shared_ptr<SpriteFrame> get(const char* sprite_frame_name) {
        HashedString hashed_name(sprite_frame_name);
        return sprite_frames_[hashed_name];
    }

private:
    typedef std::map<HashedString, shared_ptr<SpriteFrame> > SpriteFrameTable;

    static SpriteFrameCache *__shared;

    SpriteFrameCache() {}

    SpriteFrameTable sprite_frames_;
    std::set<HashedString> loaded_filenames_;
};

}

#endif /* defined(__kawaii__sprite_frame_cache__) */

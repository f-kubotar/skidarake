#include "sometuke/process/animate.h"
#include "sometuke/node/sprite.h"

#include "sometuke/logger.h"

namespace sometuke {

const HashedString Animate::TYPE("process:animate");

void Animate::set_target(const weak_ptr<Sprite>& target) {
    if (shared_ptr<Sprite> sprite = target.lock()) {
        original_frame_ = sprite->display_frame();
    }
    target_ = target;
}

void Animate::OnStart() {
    frame_num_ = 0;
    elapsed_ = 0;
    executed_loops_ = 0;
    if (shared_ptr<Sprite> sprite = target_.lock()) {
        sprite->set_display_frame(animation_->frames[frame_num_].sprite_frame);
    }
}

void Animate::OnEnd() {
    if (shared_ptr<Sprite > sprite = target_.lock()) {
        sprite->set_display_frame(original_frame_);
    }
}

bool Animate::Update(const s2_time delta_time) {
    shared_ptr<Sprite> sprite = target_.lock();
    if (!sprite) {
        return false;
    }

    s2_time current_frame_time = animation_->frames[frame_num_].time;
    if (elapsed_ > current_frame_time) {
        elapsed_ = 0;
        
        if (++frame_num_ >= animation_->frame_size) {
            if (++executed_loops_ >= animation_->loops) {
                return false;
            }
            frame_num_ = 0;
        }

        shared_ptr<SpriteFrame> sprite_frame = animation_->frames[frame_num_].sprite_frame;
        sprite->set_display_frame(sprite_frame);
    }
    elapsed_ += delta_time;

    return true;
}

}

#include "director.h"

#include "application.h"
#include "assets.h"
#include "shader_cache.h"
#include "texture_2d.h"
#include "process_manager.h"
#include "event_manager.h"
#include "matrix_stack.h"
#include "logger.h"
#include "scene.h"

#include "OpenGL_Internal.h"

namespace kawaii {

Director::Director() {
    process_manager_ = new ProcessManager;
    event_manager_   = new EventManager;
}

Director::~Director() {
    delete process_manager_;
    delete event_manager_;
}

void Director::AddActor(const shared_ptr<Actor>& actor) {
    actor_id id = actor->id();
    actor_table_[id] = actor;
}

const shared_ptr<Actor> Director::ActorById(const actor_id id) {
    return actor_table_[id];
}

bool Director::Initialize() {
    return true;
}

void Director::ReshapeProjection() {
    Application *app = Application::Current();
    const vec2 size_in_points = app->size_in_points();
    const vec2 size_in_pixels = app->size_in_pixels();
    const float content_scale_factor = app->content_scale_factor();
    
    IIINFO("SetProjection %fx%f", size_in_points.x, size_in_points.y);
    glViewport(0, 0, size_in_points.x, size_in_points.y);

    float zeye = size_in_pixels.y / 1.1566f / content_scale_factor;
    mat4 projection = mat4::Perspective(60, size_in_points.x / size_in_points.y,
                                        0.1f, zeye * 2);
    MatrixStack::GLProjection()->Push(projection);

    vec3 eye(size_in_points.x / 2, size_in_points.y / 2, zeye);
    vec3 center(size_in_points.x / 2, size_in_points.y / 2, 0);
    vec3 up(0, 1, 0);
    mat4 model_view = mat4::LookAt(eye, center, up);
    MatrixStack::GLModelView()->Push(model_view);

    CHECK_GL_ERROR();
}

void Director::MainLoop(const float delta_time) {
    process_manager_->UpdateProcesses(delta_time);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (running_scene_) {
        running_scene_->Visit();
    }
}

void Director::RunWithScene(shared_ptr<Scene> scene) {
    running_scene_ = scene;
}

// void Director::ReplaceScene(shared_ptr<Scene> scene) {
// }

// void Director::PushScene(shared_ptr<Scene> scene) {
// }

// void Director::PopScene() {
// }

// void Director::SetNextScene(shared_ptr<Scene> scene) {
// }

void Director::End() {
}

}

#include "physics/physics_system.h"

bool PhysicsSystem::checkBox(const WorldObject& a, const WorldObject& b)
{
    glm::vec3 aMin = a.position - a.collider->box.halfSize;
    glm::vec3 aMax = a.position + a.collider->box.halfSize;
    glm::vec3 bMin = b.position - b.collider->box.halfSize;
    glm::vec3 bMax = b.position + b.collider->box.halfSize;
    return (
        aMin.x <= bMax.x && aMax.x >= bMin.x &&
        aMin.y <= bMax.y && aMax.y >= bMin.y &&
        aMin.z <= bMax.z && aMax.z >= bMin.z
        );
}

void PhysicsSystem::resolveCollision(WorldObject& a, WorldObject& b)
{
    glm::vec3 aMin = a.position - a.collider->box.halfSize;
    glm::vec3 aMax = a.position + a.collider->box.halfSize;
    glm::vec3 bMin = b.position - b.collider->box.halfSize;
    glm::vec3 bMax = b.position + b.collider->box.halfSize;

    glm::vec3 overlap;
    overlap.x = std::min(aMax.x, bMax.x) - std::max(aMin.x, bMin.x);
    overlap.y = std::min(aMax.y, bMax.y) - std::max(aMin.y, bMin.y);
    overlap.z = std::min(aMax.z, bMax.z) - std::max(aMin.z, bMin.z);

    // Weight: static objects absorb 0 of the correction, dynamic absorb all of it.
    // If both dynamic, split 50/50. If one static, the other takes the full overlap.
    float aShare = a.isStatic ? 0.0f : (b.isStatic ? 1.0f : 0.5f);
    float bShare = b.isStatic ? 0.0f : (a.isStatic ? 1.0f : 0.5f);

    if (overlap.x < overlap.y && overlap.x < overlap.z)
    {
        float dir = (a.position.x < b.position.x) ? -1.0f : 1.0f;
        a.position.x += overlap.x * dir * aShare;
        b.position.x += overlap.x * -dir * bShare;
        if (!a.isStatic) a.velocity.x = 0.0f;
        if (!b.isStatic) b.velocity.x = 0.0f;
    }
    else if (overlap.y < overlap.z)
    {
        float dir = (a.position.y < b.position.y) ? -1.0f : 1.0f;
        a.position.y += overlap.y * dir * aShare;
        b.position.y += overlap.y * -dir * bShare;
        if (!a.isStatic) a.velocity.y = 0.0f;
        if (!b.isStatic) b.velocity.y = 0.0f;

        // Grounded: the object being pushed *upward* (dir > 0 for a, dir < 0 for b)
        // has landed on a surface — clear its flying flag only.
        if (!a.isStatic && dir > 0) a.isGrounded = true;
        if (!b.isStatic && dir < 0) b.isGrounded = true;
    }
    else
    {
        float dir = (a.position.z < b.position.z) ? -1.0f : 1.0f;
        a.position.z += overlap.z * dir * aShare;
        b.position.z += overlap.z * -dir * bShare;
        if (!a.isStatic) a.velocity.z = 0.0f;
        if (!b.isStatic) b.velocity.z = 0.0f;
    }
}

void PhysicsSystem::update(std::vector<WorldObject*>& entities, float dt)
{
    // 1. Gravity — skip static scene objects entirely
    for (auto* e : entities) {
        if (!e->isStatic && !e->flying) {
            e->velocity.y += -9.81f * e->gravityScale * dt;
        }
        e->isGrounded = false; // Reset grounded state before collision checks
    }

    // 2. Movement — static objects never move
    for (auto* e : entities) {
        if (!e->isStatic) {
            e->position += e->velocity * dt;
        }
    }

    // 3. Collision — iterate i < j to process each pair exactly once
    for (size_t i = 0; i < entities.size(); ++i) {
        for (size_t j = i + 1; j < entities.size(); ++j) {
            WorldObject* a = entities[i];
            WorldObject* b = entities[j];

            if (!a->getCollider() || !b->getCollider()) continue;
            if (a->isStatic && b->isStatic)             continue; // two static objects never need resolution

            if (checkBox(*a, *b)) {
                resolveCollision(*a, *b);
            }
        }
    }
}
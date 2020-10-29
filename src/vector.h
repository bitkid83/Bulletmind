#pragma once

#include "c99defs.h"
#include <math.h>

#ifdef __cplusplus
extern "C" {
}
#endif

typedef struct vec2i {
    int32_t x;
    int32_t y;
} vec2i_t;

typedef struct vec2f {
    float x;
    float y;
} vec2f_t;

static inline void vec2f_set(vec2f_t* dst, float x, float y) {
    dst->x = x;
    dst->y = y;
}

static inline void vec2f_zero(vec2f_t* dst) {
    vec2f_set(dst, 0.f, 0.f);
}

static inline void vec2f_copy(vec2f_t* dst, const vec2f_t other) {
    dst->x = other.x;
    dst->y = other.y;
}

static inline void vec2f_add(vec2f_t* dst, const vec2f_t lhs, const vec2f_t rhs) {
    vec2f_set(dst, lhs.x + rhs.x, lhs.y + rhs.y);
}

static inline void vec2f_sub(vec2f_t* dst, const vec2f_t lhs, const vec2f_t rhs) {
    vec2f_set(dst, lhs.x - rhs.x, lhs.y - rhs.y);
}

static inline void vec2f_mul(vec2f_t* dst, const vec2f_t lhs, const vec2f_t rhs) {
    vec2f_set(dst, lhs.x * rhs.x, lhs.y * rhs.y);
}

static inline void vec2f_div(vec2f_t* dst, const vec2f_t lhs, const vec2f_t rhs) {
    vec2f_set(dst, lhs.x / rhs.x, lhs.y / rhs.y);
}

static inline void vec2f_addf(vec2f_t* dst, const vec2f_t v, float f) {
    vec2f_set(dst, v.x + f, v.y + f);
}

static inline void vec2f_subf(vec2f_t* dst, const vec2f_t v, float f) {
    vec2f_set(dst, v.x - f, v.y - f);
}

static inline void vec2f_mulf(vec2f_t* dst, const vec2f_t v, float f) {
    vec2f_set(dst, v.x * f, v.y * f);
}

static inline void vec2f_divf(vec2f_t* dst, const vec2f_t v, float f) {
    vec2f_set(dst, v.x / f, v.y / f);
}

static inline void vec2f_negate(vec2f_t* dst, const vec2f_t v) {
    vec2f_set(dst, -v.x, -v.y);
}

static inline float vec2f_dot(const vec2f_t v1, const vec2f_t v2) {
    return v1.x * v2.x + v1.y * v2.x;
}

static inline float vec2f_len(const vec2f_t v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}

static inline float vec2f_norm(vec2f_t* dst, const vec2f_t v) {
    const float length = 1.f / vec2f_len(v);
    vec2f_mulf(dst, v, length);
    return length;
}

static inline float vec2f_dist(const vec2f_t v1, const vec2f_t v2) {
    vec2f_t temp;
    vec2f_sub(&temp, v1, v2);
    return vec2f_len(temp);
}

static inline void vec2f_fabsf(vec2f_t* dst, const vec2f_t v) {
    vec2f_set(dst, fabsf(v.x), fabsf(v.y));
}

static inline void vec2f_friction(vec2f_t* dst, const vec2f_t a, float friction) {
    float speed = vec2f_len(a);
    float new_speed = speed - (speed * friction);

    if(new_speed > 0)
        new_speed /= speed;
    else
        new_speed = 0;

    vec2f_mulf(dst, a, new_speed);
}

// OLD DEFS

typedef struct {
    int32_t x, y;
    int32_t w, h;
} rect_t;


typedef struct rgba {
    float r;
    float g;
    float b;
    float a;
} rgba_t;

/*

typedef struct vec2f {
    float x;
    float y;
} vec2f_t;

typedef struct vec3f {
    float x;
    float y;
    float z;
} vec3f_t;

typedef struct vec4f {
    float x;
    float y;
    float z;
    float w;
} vec4f_t;

inline void vec2f_set(vec2f_t* dst, vec2f_t* value) {
    dst->x = value->x;
    dst->y = value->y;
}

inline void vec2f_setf(vec2f_t* dst, float x, float y) {
    dst->x = x;
    dst->y = y;
}

inline void vec2f_add(vec2f_t* dst, vec2f_t* a, vec2f_t* b) {
    dst->x = a->x + b->x;
    dst->y = a->y + b->y;
}

inline void vec2f_sub(vec2f_t* dst, vec2f_t* a, vec2f_t* b) {
    dst->x = a->x - b->x;
    dst->y = a->y - b->y;
}

inline void vec2f_equ(vec2f_t* a, vec2f_t* b) {
    a->x = b->x;
    a->y = b->y;
}

inline void vec2f_addequ(vec2f_t* a, vec2f_t* b) {
    a->x += b->x;
    a->y += b->y;
}

inline void vec2f_subequ(vec2f_t* a, vec2f_t* b) {
    a->x -= b->x;
    a->y -= b->y;
}

inline void vec2f_mul(vec2f_t* a, vec2f_t* b) {
    a->x *= b->x;
    a->y *= b->y;
}

inline void vec2f_sqr(vec2f_t* a) {
    a->x *= a->x;
    a->y *= a->y;
}

inline void vec2f_fabsf(vec2f_t* a) {
    a->x = fabsf(a->x);
    a->y = fabsf(a->y);
}

// add float to vec2f
inline void vec2f_addf(vec2f_t* a, float s) {
    a->x += s;
    a->y += s;
}

// subtract float from vec2f
inline void vec2f_subf(vec2f_t* a, float s) {
    a->x -= s;
    a->y -= s;
}

// scales a vec2f by a float
inline void vec2f_scale(vec2f_t* a, float s) {
    a->x *= s;
    a->y *= s;
}

inline float vec2f_sqrlen(vec2f_t* a) {
    return (a->x * a->x + a->y * a->y);
}

// return the length of vector
inline float vec2f_length(vec2f_t* a) {
    return sqrtf(vec2f_sqrlen(a));
}

// produce a unit vector
inline float vec2f_norm(vec2f_t* a) {
    float length = 1.0f / vec2f_length(a);
    a->x *= length;
    a->y *= length;
    return length;
}

// return the dot product of vectors a and b
inline float vec2f_dot(vec2f_t* a, vec2f_t* b) {
    return (a->x * b->x) + (a->y * b->y);
}

// vector friction
inline void vec2f_friction(vec2f_t* a, float friction) {
    float speed = vec2f_length(a);
    float newspeed = speed - (speed * friction);

    if(newspeed > 0)
        newspeed /= speed;
    else
        newspeed = 0;

    vec2f_scale(a, newspeed);
}
*/

#ifdef __cplusplus
}
#endif

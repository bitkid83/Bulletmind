#pragma once

#include "c99defs.h"
#include "types.h"
#include <math.h>

#ifdef __cplusplus
extern "C" {
}
#endif

typedef struct vec2i {
    i32 x;
    i32 y;
} vec2i_t;

typedef struct vec2f {
    f32 x;
    f32 y;
} vec2f_t;

static inline void vec2f_set(vec2f_t* dst, f32 x, f32 y) {
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

static inline void vec2f_addf(vec2f_t* dst, const vec2f_t v, f32 f) {
    vec2f_set(dst, v.x + f, v.y + f);
}

static inline void vec2f_subf(vec2f_t* dst, const vec2f_t v, f32 f) {
    vec2f_set(dst, v.x - f, v.y - f);
}

static inline void vec2f_mulf(vec2f_t* dst, const vec2f_t v, f32 f) {
    vec2f_set(dst, v.x * f, v.y * f);
}

static inline void vec2f_divf(vec2f_t* dst, const vec2f_t v, f32 f) {
    vec2f_set(dst, v.x / f, v.y / f);
}

static inline void vec2f_negate(vec2f_t* dst, const vec2f_t v) {
    vec2f_set(dst, -v.x, -v.y);
}

static inline f32 vec2f_dot(const vec2f_t v1, const vec2f_t v2) {
    return v1.x * v2.x + v1.y * v2.x;
}

static inline f32 vec2f_len(const vec2f_t v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}

static inline f32 vec2f_norm(vec2f_t* dst, const vec2f_t v) {
    const f32 length = 1.f / vec2f_len(v);
    vec2f_mulf(dst, v, length);
    return length;
}

static inline f32 vec2f_dist(const vec2f_t v1, const vec2f_t v2) {
    vec2f_t temp;
    vec2f_sub(&temp, v1, v2);
    return vec2f_len(temp);
}

static inline void vec2f_fabsf(vec2f_t* dst, const vec2f_t v) {
    vec2f_set(dst, fabsf(v.x), fabsf(v.y));
}

static inline void vec2f_friction(vec2f_t* dst, const vec2f_t a, f32 friction) {
    f32 speed = vec2f_len(a);
    f32 new_speed = speed - (speed * friction);

    if(new_speed > 0)
        new_speed /= speed;
    else
        new_speed = 0;

    vec2f_mulf(dst, a, new_speed);
}

// OLD DEFS

typedef struct {
    i32 x, y;
    i32 w, h;
} rect_t;


typedef struct rgba {
    f32 r;
    f32 g;
    f32 b;
    f32 a;
} rgba_t;

/*

typedef struct vec2f {
    f32 x;
    f32 y;
} vec2f_t;

typedef struct vec3f {
    f32 x;
    f32 y;
    f32 z;
} vec3f_t;

typedef struct vec4f {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} vec4f_t;

inline void vec2f_set(vec2f_t* dst, vec2f_t* value) {
    dst->x = value->x;
    dst->y = value->y;
}

inline void vec2f_setf(vec2f_t* dst, f32 x, f32 y) {
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

// add f32 to vec2f
inline void vec2f_addf(vec2f_t* a, f32 s) {
    a->x += s;
    a->y += s;
}

// subtract f32 from vec2f
inline void vec2f_subf(vec2f_t* a, f32 s) {
    a->x -= s;
    a->y -= s;
}

// scales a vec2f by a f32
inline void vec2f_scale(vec2f_t* a, f32 s) {
    a->x *= s;
    a->y *= s;
}

inline f32 vec2f_sqrlen(vec2f_t* a) {
    return (a->x * a->x + a->y * a->y);
}

// return the length of vector
inline f32 vec2f_length(vec2f_t* a) {
    return sqrtf(vec2f_sqrlen(a));
}

// produce a unit vector
inline f32 vec2f_norm(vec2f_t* a) {
    f32 length = 1.0f / vec2f_length(a);
    a->x *= length;
    a->y *= length;
    return length;
}

// return the dot product of vectors a and b
inline f32 vec2f_dot(vec2f_t* a, vec2f_t* b) {
    return (a->x * b->x) + (a->y * b->y);
}

// vector friction
inline void vec2f_friction(vec2f_t* a, f32 friction) {
    f32 speed = vec2f_length(a);
    f32 newspeed = speed - (speed * friction);

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

#pragma once

typedef struct {
    float32 x,y,z;
} vec3;

typedef struct {
    float32 x,y;
} vec2;

vec3  vec3_make(float32 i) { return (vec3){ i, i, i }; }
vec3  vec3_addv(vec3 v, vec3 v1) { return (vec3){ v.x + v1.x, v.y + v1.y, v.z + v1.z }; }
vec3  vec3_subv(vec3 v, vec3 v1) { return (vec3){ v.x - v1.x, v.y - v1.y, v.z - v1.z }; }
vec3  vec3_addf(vec3 v, float32 a) { return (vec3){ v.x + a, v.y + a, v.z + a }; }
vec3  vec3_subf(vec3 v, float32 s) { return (vec3){ v.x - s, v.y - s, v.z - s }; }
vec3  vec3_mulf(vec3 v, float32 m) { return (vec3){ v.x * m, v.y * m, v.z * m }; }
vec3  vec3_divf(vec3 v, float32 d) { return (vec3){ v.x / d, v.y / d, v.z / d }; } // assuming 'd' is never zero
float vec3_dot(vec3 v, vec3 v1) { return v.x * v1.x + v.y * v1.y + v.z * v1.z; }

vec3 vec3_cross(vec3 v, vec3 v1) {
    vec3 r;
    r.x = v.y * v1.z - v.z * v1.y;
    r.y = v.z * v1.x - v.x * v1.z;
    r.z = v.x * v1.y - v.y * v1.x;
    return r;
}
vec3 vec3_mulv(vec3 v, vec3 v1) {
    v.x *= v1.x;
    v.y *= v1.y;
    v.z *= v1.z;
    return v;
}

vec2  vec2_make(float32 i) { return (vec2){ i, i }; }
vec2  vec2_addv(vec2 v, vec2 v1) { return (vec2){ v.x + v1.x, v.y + v1.y }; }
vec2  vec2_subv(vec2 v, vec2 v1) { return (vec2){ v.x - v1.x, v.y - v1.y }; }
vec2  vec2_addf(vec2 v, float32 a) { return (vec2){ v.x + a, v.y + a }; }
vec2  vec2_subf(vec2 v, float32 s) { return (vec2){ v.x - s, v.y - s }; }
vec2  vec2_mulf(vec2 v, float32 m) { return (vec2){ v.x * m, v.y * m }; }
vec2  vec2_divf(vec2 v, float32 d) { return (vec2){ v.x / d, v.y / d }; } // assuming 'd' is never zero
float vec2_dot(vec2 v, vec2 v1) { return v.x * v1.x + v.y * v1.y; }

vec2 vec2_mulv(vec2 v, vec2 v1) {
    v.x *= v1.x;
    v.y *= v1.y;
    return v;
}

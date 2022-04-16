#pragma once

struct Vec3 {
    float32 x,y,z;

    float Dot(Vec3 a);
    Vec3  Cross(Vec3 a);
    Vec3  Normalized();
    float Magnitude();
    float SqrMagnitude();
    
    Vec3 operator+(float32 a);
    Vec3 operator-(float32 a);
    Vec3 operator*(float32 a);
    Vec3 operator/(float32 a);
    Vec3 operator+(Vec3 a);
    Vec3 operator-(Vec3 a);
    Vec3 operator*(Vec3 a);
    Vec3 operator/(Vec3 a);

    void Print();
};

float Vec3::Dot(Vec3 a) {
    return x * a.x + y * a.y + z * a.z;
}

Vec3 Vec3::Cross(Vec3 a) {
    Vec3 r;
    r.x = y * a.z - z * a.y;
    r.y = z * a.x - x * a.z;
    r.z = x * a.y - y * a.x;
    return r;
}

Vec3 Vec3::Normalized() {
    return *this / sqrtf(x*x + y*y + z*z);
}

float Vec3::Magnitude() {
    return sqrtf(x*x + y*y + z*z);
}

float Vec3::SqrMagnitude() {
    return x*x + y*y + z*z;
}

Vec3 Vec3::operator+(float32 a) { return { x + a, y + a, z + a }; }
Vec3 Vec3::operator-(float32 a) { return { x - a, y - a, z - a }; }
Vec3 Vec3::operator*(float32 a) { return { x * a, y * a, z * a }; }
Vec3 Vec3::operator/(float32 a) { return { x / a, y / a, z / a }; }
Vec3 Vec3::operator+(Vec3 a) { return { x + a.x, y + a.y, z + a.z }; }
Vec3 Vec3::operator-(Vec3 a) { return { x - a.x, y - a.y, z - a.z }; }
Vec3 Vec3::operator*(Vec3 a) { return { x * a.x, y * a.y, z * a.z }; }
Vec3 Vec3::operator/(Vec3 a) { return { x / a.x, y / a.y, z / a.z }; }
void Vec3::Print() { DebugLog("Vec3(%f, %f, %f)", x, y, z); }

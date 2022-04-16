#pragma once

struct Vec3 {
    float x,y,z;

    float Dot(Vec3 a)   const;
    Vec3  Cross(Vec3 a) const;
    Vec3  Normalized()  const;
    float Length()      const;
    float SqrLength()   const;
    
    Vec3 operator+(float) const;
    Vec3 operator-(float) const;
    Vec3 operator*(float) const;
    Vec3 operator/(float) const;
    void operator+=(float);
    void operator-=(float);
    void operator*=(float);
    void operator/=(float);
    Vec3 operator+(Vec3) const;
    Vec3 operator-(Vec3) const;
    Vec3 operator*(Vec3) const;
    Vec3 operator/(Vec3) const;
    void operator+=(Vec3);
    void operator-=(Vec3);
    void operator*=(Vec3);
    void operator/=(Vec3);
    void operator= (Vec3);

    friend Vec3 operator*(float, Vec3);

    void Print();
};

float Vec3::Dot(Vec3 a) const {
    return x * a.x + y * a.y + z * a.z;
}

Vec3 Vec3::Cross(Vec3 a) const {
    Vec3 r;
    r.x = y * a.z - z * a.y;
    r.y = z * a.x - x * a.z;
    r.z = x * a.y - y * a.x;
    return r;
}

Vec3 Vec3::Normalized() const {
    return *this / sqrtf(x*x + y*y + z*z);
}

float Vec3::Length() const {
    return sqrtf(x*x + y*y + z*z);
}

float Vec3::SqrLength() const {
    return x*x + y*y + z*z;
}

Vec3 Vec3::operator+(float a) const { return { x + a, y + a, z + a }; }
Vec3 Vec3::operator-(float a) const { return { x - a, y - a, z - a }; }
Vec3 Vec3::operator*(float a) const { return { x * a, y * a, z * a }; }
Vec3 Vec3::operator/(float a) const { return { x / a, y / a, z / a }; }
void Vec3::operator+=(float a) { x += a; y += a; z += a; }
void Vec3::operator-=(float a) { x -= a; y -= a; z -= a; }
void Vec3::operator*=(float a) { x *= a; y *= a; z *= a; }
void Vec3::operator/=(float a) { x /= a; y /= a; z /= a; }
Vec3 Vec3::operator+(Vec3 a) const { return { x + a.x, y + a.y, z + a.z }; }
Vec3 Vec3::operator-(Vec3 a) const { return { x - a.x, y - a.y, z - a.z }; }
Vec3 Vec3::operator*(Vec3 a) const { return { x * a.x, y * a.y, z * a.z }; }
Vec3 Vec3::operator/(Vec3 a) const { return { x / a.x, y / a.y, z / a.z }; }
void Vec3::operator+=(Vec3 a) { x += a.x; y += a.y; z += a.z; }
void Vec3::operator-=(Vec3 a) { x -= a.x; y -= a.y; z -= a.z; }
void Vec3::operator*=(Vec3 a) { x *= a.x; y *= a.y; z *= a.z; }
void Vec3::operator/=(Vec3 a) { x /= a.x; y /= a.y; z /= a.z; }
void Vec3::operator= (Vec3 a) { x = a.x; y = a.y; z = a.z; };

Vec3 operator*(float a, Vec3 v) { return {v.x * a, v.y * a, v.z * a}; }

void Vec3::Print() { DebugLog("Vec3(%f, %f, %f)\n", x, y, z); }

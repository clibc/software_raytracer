#pragma once

struct v3 {
    float x,y,z;

    float Dot(v3 a)   const;
    v3  Cross(v3 a) const;
    v3  Normalize()  const;
    float Length()      const;
    float SqrLength()   const;
    
    v3 operator+(float) const;
    v3 operator-(float) const;
    v3 operator*(float) const;
    v3 operator/(float) const;
    void operator+=(float);
    void operator-=(float);
    void operator*=(float);
    void operator/=(float);
    v3 operator+(v3) const;
    v3 operator-(v3) const;
    v3 operator*(v3) const;
    v3 operator/(v3) const;
    void operator+=(v3);
    void operator-=(v3);
    void operator*=(v3);
    void operator/=(v3);
    void operator= (v3);

    friend v3 operator*(float, v3);

    void Print();
};

float v3::Dot(v3 a) const {
    return x * a.x + y * a.y + z * a.z;
}

v3 v3::Cross(v3 a) const {
    v3 r;
    r.x = y * a.z - z * a.y;
    r.y = z * a.x - x * a.z;
    r.z = x * a.y - y * a.x;
    return r;
}

v3 v3::Normalize() const {
    v3 res = {0,0,0};
    float length = sqrtf(x*x + y*y + z*z);
    if(length != 0) {
        res = *this * (1.0f / length);
    }
    return res;
}

float v3::Length() const {
    return sqrtf(x*x + y*y + z*z);
}

float v3::SqrLength() const {
    return x*x + y*y + z*z;
}

v3 v3::operator+(float a) const { return { x + a, y + a, z + a }; }
v3 v3::operator-(float a) const { return { x - a, y - a, z - a }; }
v3 v3::operator*(float a) const { return { x * a, y * a, z * a }; }
v3 v3::operator/(float a) const { return { x / a, y / a, z / a }; }
void v3::operator+=(float a) { x += a; y += a; z += a; }
void v3::operator-=(float a) { x -= a; y -= a; z -= a; }
void v3::operator*=(float a) { x *= a; y *= a; z *= a; }
void v3::operator/=(float a) { x /= a; y /= a; z /= a; }
v3 v3::operator+(v3 a) const { return { x + a.x, y + a.y, z + a.z }; }
v3 v3::operator-(v3 a) const { return { x - a.x, y - a.y, z - a.z }; }
v3 v3::operator*(v3 a) const { return { x * a.x, y * a.y, z * a.z }; }
v3 v3::operator/(v3 a) const { return { x / a.x, y / a.y, z / a.z }; }
void v3::operator+=(v3 a) { x += a.x; y += a.y; z += a.z; }
void v3::operator-=(v3 a) { x -= a.x; y -= a.y; z -= a.z; }
void v3::operator*=(v3 a) { x *= a.x; y *= a.y; z *= a.z; }
void v3::operator/=(v3 a) { x /= a.x; y /= a.y; z /= a.z; }
void v3::operator= (v3 a) { x = a.x; y = a.y; z = a.z; };

v3 operator*(float a, v3 v) { return {v.x * a, v.y * a, v.z * a}; }

void v3::Print() { DebugLog("Vec3(%f, %f, %f)\n", x, y, z); }

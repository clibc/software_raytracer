#pragma once

#include <math.h>
#include <cmath>

struct v3 {
    float x,y,z;

    v3(float, float, float);
    v3() = default;

    inline float Dot(v3 a)     const;
    inline v3  Cross(v3 a)     const;
    inline v3  Normalize()     const;
    inline float Length()      const;
    inline float SqrLength()   const;
    
    inline v3 operator+(float) const;
    inline v3 operator-(float) const;
    inline v3 operator*(float) const;
    inline v3 operator/(float) const;
    inline void operator+=(float);
    inline void operator-=(float);
    inline void operator*=(float);
    inline void operator/=(float);
    inline v3 operator+(v3) const;
    inline v3 operator-(v3) const;
    inline v3 operator*(v3) const;
    inline v3 operator/(v3) const;
    inline void operator+=(v3);
    inline void operator-=(v3);
    inline void operator*=(v3);
    inline void operator/=(v3);
    inline void operator= (v3);

    inline friend v3 operator*(float, v3);

    void Print();
};

v3::v3(float ix, float iy, float iz) {
    x = ix;
    y = iy;
    z = iz;
}

inline float v3::Dot(v3 a) const {
    return x * a.x + y * a.y + z * a.z;
}

inline v3 v3::Cross(v3 a) const {
    v3 r;
    r.x = y * a.z - z * a.y;
    r.y = z * a.x - x * a.z;
    r.z = x * a.y - y * a.x;
    return r;
}

inline v3 v3::Normalize() const {
    v3 res = {0,0,0};
    float length = sqrtf(x*x + y*y + z*z);
    if(length != 0) {
        res = *this * (1.0f / length);
    }
    return res;
}

inline float v3::Length() const {
    return sqrtf(x*x + y*y + z*z);
}

inline float v3::SqrLength() const {
    return x*x + y*y + z*z;
}

inline v3 v3::operator+(float a) const { return { x + a, y + a, z + a }; }
inline v3 v3::operator-(float a) const { return { x - a, y - a, z - a }; }
inline v3 v3::operator*(float a) const { return { x * a, y * a, z * a }; }
inline v3 v3::operator/(float a) const { return { x / a, y / a, z / a }; }
inline void v3::operator+=(float a) { x += a; y += a; z += a; }
inline void v3::operator-=(float a) { x -= a; y -= a; z -= a; }
inline void v3::operator*=(float a) { x *= a; y *= a; z *= a; }
inline void v3::operator/=(float a) { x /= a; y /= a; z /= a; }
inline v3 v3::operator+(v3 a) const { return { x + a.x, y + a.y, z + a.z }; }
inline v3 v3::operator-(v3 a) const { return { x - a.x, y - a.y, z - a.z }; }
inline v3 v3::operator*(v3 a) const { return { x * a.x, y * a.y, z * a.z }; }
inline v3 v3::operator/(v3 a) const { return { x / a.x, y / a.y, z / a.z }; }
inline void v3::operator+=(v3 a) { x += a.x; y += a.y; z += a.z; }
inline void v3::operator-=(v3 a) { x -= a.x; y -= a.y; z -= a.z; }
inline void v3::operator*=(v3 a) { x *= a.x; y *= a.y; z *= a.z; }
inline void v3::operator/=(v3 a) { x /= a.x; y /= a.y; z /= a.z; }
inline void v3::operator= (v3 a) { x = a.x; y = a.y; z = a.z; };

inline v3 operator*(float a, v3 v) { return {v.x * a, v.y * a, v.z * a}; }

void v3::Print() {
#ifdef DebugLog
    DebugLog("Vec3(%f, %f, %f)\n", x, y, z);
#endif
}

struct v4 {
    float x,y,z,w;
    
    v4(float, float, float, float);
    v4(v3, float);
    v4() = default;

    inline float Dot(v4 a)     const;
    inline v4  Normalize()     const;
    inline float Length()      const;
    inline float SqrLength()   const;
    
    inline v4 operator+(float) const;
    inline v4 operator-(float) const;
    inline v4 operator*(float) const;
    inline v4 operator/(float) const;
    inline void operator+=(float);
    inline void operator-=(float);
    inline void operator*=(float);
    inline void operator/=(float);
    inline v4 operator+(v4) const;
    inline v4 operator-(v4) const;
    inline v4 operator*(v4) const;
    inline v4 operator/(v4) const;
    inline void operator+=(v4);
    inline void operator-=(v4);
    inline void operator*=(v4);
    inline void operator/=(v4);
    inline void operator= (v4);

    inline friend v4 operator*(float, v4);

    void Print();
};

v4::v4(float ix, float iy, float iz, float iw) {
    x = ix;
    y = iy;
    z = iz;
    w = iw;
}

v4::v4(v3 v, float iw) {
    x = v.x;
    y = v.y;
    z = v.z;
    w = iw;
}


inline float v4::Dot(v4 a) const {
    return x * a.x + y * a.y + z * a.z + w * a.w;
}

inline v4 v4::Normalize() const {
    v4 res = {0,0,0,0};
    float length = sqrtf(x*x + y*y + z*z + w*w);
    if(length != 0) {
        res = *this * (1.0f / length);
    }
    return res;
}

inline float v4::Length() const {
    return sqrtf(x*x + y*y + z*z + w*w);
}

inline float v4::SqrLength() const {
    return x*x + y*y + z*z + w*w;
}

inline v4 v4::operator+(float a) const { return { x + a, y + a, z + a, w + a }; }
inline v4 v4::operator-(float a) const { return { x - a, y - a, z - a, w - a }; }
inline v4 v4::operator*(float a) const { return { x * a, y * a, z * a, w * a }; }
inline v4 v4::operator/(float a) const { return { x / a, y / a, z / a, w / a }; }
inline void v4::operator+=(float a) { x += a; y += a; z += a; w += a; }
inline void v4::operator-=(float a) { x -= a; y -= a; z -= a; w -= a; }
inline void v4::operator*=(float a) { x *= a; y *= a; z *= a; w *= a; }
inline void v4::operator/=(float a) { x /= a; y /= a; z /= a; w /= a; }
inline v4 v4::operator+(v4 a) const { return { x + a.x, y + a.y, z + a.z, w + a.w }; }
inline v4 v4::operator-(v4 a) const { return { x - a.x, y - a.y, z - a.z, w - a.w }; }
inline v4 v4::operator*(v4 a) const { return { x * a.x, y * a.y, z * a.z, w * a.w }; }
inline v4 v4::operator/(v4 a) const { return { x / a.x, y / a.y, z / a.z, w / a.w }; }
inline void v4::operator+=(v4 a) { x += a.x; y += a.y; z += a.z, w += a.w; }
inline void v4::operator-=(v4 a) { x -= a.x; y -= a.y; z -= a.z, w -= a.w; }
inline void v4::operator*=(v4 a) { x *= a.x; y *= a.y; z *= a.z, w *= a.w; }
inline void v4::operator/=(v4 a) { x /= a.x; y /= a.y; z /= a.z, w /= a.w; }
inline void v4::operator= (v4 a) { x = a.x; y = a.y; z = a.z; w = a.w; };

inline v4 operator*(float a, v4 v) { return {v.x * a, v.y * a, v.z * a, v.w * a}; }

void v4::Print() {
#ifdef DebugLog
    DebugLog("Vec4(%f, %f, %f, %f)\n", x, y, z, w);
#endif
}


// m0 m4 m8  m12
// m1 m5 m9  m13
// m2 m6 m10 m14
// m3 m7 m11 m15
struct m4 { // matrix4x4
    float values[16];

    static m4 Identity(float);
    inline void   operator=(m4 const&);
    inline float& operator[](int);
    inline m4     operator*(m4 const&);
    inline v3     operator*(v3 const&) const;

    inline void SetRow(int, float, float, float, float);
    inline void SetColumn(int, float, float, float, float);
    inline void Print();
};

inline m4 m4::Identity(float a = 1.0f) {
    m4 ret = {0};
    ret[0 * 4 + 0] = a;
    ret[1 * 4 + 1] = a;
    ret[2 * 4 + 2] = a;
    ret[3 * 4 + 3] = a;
    return ret;
}

inline float& m4::operator[](int index) { return values[index]; }

inline void m4::operator=(m4 const& a) {
    (*this)[0]  = a.values[0];
    (*this)[1]  = a.values[1];
    (*this)[2]  = a.values[2];
    (*this)[3]  = a.values[3];
    (*this)[4]  = a.values[4];
    (*this)[5]  = a.values[5];
    (*this)[6]  = a.values[6];
    (*this)[7]  = a.values[7];
    (*this)[8]  = a.values[8];
    (*this)[9]  = a.values[9];
    (*this)[10] = a.values[10];
    (*this)[11] = a.values[11];
    (*this)[12] = a.values[12];
    (*this)[13] = a.values[13];
    (*this)[14] = a.values[14];
    (*this)[15] = a.values[15];
}

inline m4 m4::operator*(m4 const& a) {
    m4 res = {};
    float* o1 = &(this->values[0]);
    const float* o2 = &(a.values[0]);

    res[0]  = o1[0] * o2[0] + o1[4] * o2[1] + o1[8] * o2[2] + o1[12] * o2[3]; 
    res[4]  = o1[0] * o2[4] + o1[4] * o2[5] + o1[8] * o2[6] + o1[12] * o2[7]; 
    res[8]  = o1[0] * o2[8] + o1[4] * o2[9] + o1[8] * o2[10] + o1[12] * o2[11]; 
    res[12] = o1[0] * o2[12] + o1[4] * o2[13] + o1[8] * o2[14] + o1[12] * o2[15]; 

    res[1]  = o1[1] * o2[0] + o1[5] * o2[1] + o1[9] * o2[2] + o1[13] * o2[3];
    res[5]  = o1[1] * o2[4] + o1[5] * o2[5] + o1[9] * o2[6] + o1[13] * o2[7]; 
    res[9]  = o1[1] * o2[8] + o1[5] * o2[9] + o1[9] * o2[10] + o1[13] * o2[11]; 
    res[13] = o1[1] * o2[12] + o1[5] * o2[13] + o1[9] * o2[14] + o1[13] * o2[15]; 

    res[2]  = o1[2] * o2[0] + o1[6] * o2[1] + o1[10] * o2[2] + o1[14] * o2[3];
    res[6]  = o1[2] * o2[4] + o1[6] * o2[5] + o1[10] * o2[6] + o1[14] * o2[7]; 
    res[10] = o1[2] * o2[8] + o1[6] * o2[9] + o1[10] * o2[10] + o1[14] * o2[11]; 
    res[14] = o1[2] * o2[12] + o1[6] * o2[13] + o1[10] * o2[14] + o1[14] * o2[15];

    res[3]  = o1[3] * o2[0] + o1[7] * o2[1] + o1[11] * o2[2] + o1[15] * o2[3];
    res[7]  = o1[3] * o2[4] + o1[7] * o2[5] + o1[11] * o2[6] + o1[15] * o2[7];
    res[11] = o1[3] * o2[8] + o1[7] * o2[9] + o1[11] * o2[10] + o1[15] * o2[11];
    res[15] = o1[3] * o2[12] + o1[7] * o2[13] + o1[11] * o2[14] + o1[15] * o2[15];
    
    return res;
}

inline v3 m4::operator*(v3 const& a) const {
    v3 res = {};
    const float* o = &(this->values[0]);
    
    res.x = o[0] * a.x + o[1] * a.y + o[2]  * a.z + o[3];
    res.y = o[4] * a.x + o[5] * a.y + o[6]  * a.z + o[7];
    res.z = o[8] * a.x + o[9] * a.y + o[10] * a.z + o[11];

    return res;
}

inline void m4::SetRow(int row, float a1, float a2, float a3, float a4) {
    values[row + 0 * 4] = a1;
    values[row + 1 * 4] = a2;
    values[row + 2 * 4] = a3;
    values[row + 3 * 4] = a4;
}

inline void m4::SetColumn(int column, float a1, float a2, float a3, float a4) {
    values[column * 4 + 0] = a1;
    values[column * 4 + 1] = a2;
    values[column * 4 + 2] = a3;
    values[column * 4 + 3] = a4;
}

inline void m4::Print() {
#ifdef DebugLog
    DebugLog("\nRow major:\n");
    DebugLog("(%f, %f, %f, %f)\n", values[0], values[4], values[8],  values[12]); 
    DebugLog("(%f, %f, %f, %f)\n", values[1], values[5], values[9],  values[13]); 
    DebugLog("(%f, %f, %f, %f)\n", values[2], values[6], values[10], values[14]); 
    DebugLog("(%f, %f, %f, %f)\n", values[3], values[7], values[11], values[15]); 
    DebugLog("Column major:\n");
    DebugLog("(%f, %f, %f, %f)\n", values[0], values[1], values[2],  values[3]); 
    DebugLog("(%f, %f, %f, %f)\n", values[4], values[5], values[6],  values[7]); 
    DebugLog("(%f, %f, %f, %f)\n", values[8], values[9], values[10], values[11]); 
    DebugLog("(%f, %f, %f, %f)\n", values[12], values[13], values[14], values[15]); 
    DebugLog("\n");
#endif
}

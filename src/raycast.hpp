#pragma once

#define MAX_OBJECT_COUNT 16

struct Sphere {
    u16 position;
    u16 material;
    f32 radius;
};

struct Plane {
    u16 position;
    u16 material;
    v3  normal;
    f32 offset;
};

struct Material {
    v3 color;
};

struct World {
    u16       sphere_count;
    u16       plane_count;
    Sphere*   spheres;
    Plane*    planes;
    Material* materials;
    v3*       positions;
};

struct Hit {
    v3 point;
    v3 normal;
    v3 color;
    f32 distance;
};

static World world;
v3 RaycastWorld(v3,v3);

// @TODO: instead of doing bouncing here,
// do it on RaycastWorld() and have a fucntion that returns
// first hit. Then bounce it!!
Hit RaycastSphere(v3 ro, v3 rd, v3 s, f32 radius) {
    Hit hit = {};
    hit.distance = -1;
    hit.color = {0.6f, 0.5f, 0};

    v3  p = ro + abs((s - ro).Dot(rd)) * rd;
    f32 d = (p - s).SqrLength();

    if(d < radius*radius) { // hit
        f32 rad = p.Length() - sqrtf(radius*radius - d);
        v3  t   = ro + rad*rd;
        v3 n = (t-s).Normalize();

        hit.point = t;
        hit.normal = n;
        hit.distance = rad;
        v3 scol = {};
        
        for(int i = 0; i < 5; ++i) {
            scol += RaycastWorld(t, n);
        }

        hit.color += scol / 5.0f;
        hit.color /= 2.0f;
    }

    return hit;
}

Hit RaycastPlane(v3 ro, v3 rd, v3 n, f32 d) {
    Hit hit = {};
    hit.distance = -1;
    hit.color = {0.2f, 0.0f, 0.6f};
    
    f32 epsilon = 0.0001f;
    f32 denom = n.Dot(rd);
    
    if(denom < epsilon) {
        f32 t = (-d  - n.Dot(ro)) / denom;
        hit.distance = (rd*t).Length();
        hit.normal = n;
    }

    return hit;
}

v3 RaycastWorld(v3 ro, v3 rd) {
    v3 col = {};
    f32 distance = FLT_MAX - 100;
    v3 light_dir = v3(0, 1, 0);
    
    for(u32 i = 0; i < world.sphere_count; ++i) {
        Sphere s = world.spheres[i];
        Hit hit = RaycastSphere(ro, rd, world.positions[s.position], s.radius);
        if(hit.distance > 0 && hit.distance < distance) {
            col = hit.color;
            distance = hit.distance;

            col += hit.normal.Dot(light_dir);
            col *= 0.5f;
        }
    }

    for(u32 i = 0; i < world.plane_count; ++i) {
        Plane p = world.planes[i];
        Hit hit = RaycastPlane(ro, rd, p.normal, p.offset);
        if(hit.distance > 0 && hit.distance < distance) {
            col = hit.color;
            distance = hit.distance;
        }
    }
    
    return col;
}

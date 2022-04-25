#pragma once

v3 RaycastSphere(v3 ro, v3 rd, v3 s, f32 radius) {
    v3 col = {0, 0, 0};
    v3  p = ro + abs((s - ro).Dot(rd)) * rd;
    f32 d = (p - s).SqrLength();
            
    if(d < radius * radius) { // hit
        f32 rad = p.Length() - sqrtf(radius*radius - d);
        v3  t   = ro + rad*rd;
        v3 n = (t-s).Normalize();

        col = n;
        col = {1, 0, 0};
    }

    return col;
}

v3 RaycastPlane(v3 ro, v3 rd, v3 n, f32 d) {
    v3 col = {0, 0, 0};
    f32 epsilon = 0.0001f;
    
    f32 denom = n.Dot(rd);

    if(denom < epsilon) {
        f32 t = (-d  - n.Dot(ro)) / denom;

        f32 dist = (ro + rd*t).Length();
        dist = min(1000, dist);

        col.y = dist / 1000.0f;;
    }
    
    return col;
}


v3 RaycastWorld(v3 ro, v3 rd) {
    v3 col;

    v3 SpherePos =  {0, 0, 11};
    f32 SphereRadius = 1.0f;
    col = RaycastSphere(ro, rd, SpherePos, SphereRadius);
    //col = RaycastPlane(ro, rd, {0, 1,0}, 100);
    return col;
}

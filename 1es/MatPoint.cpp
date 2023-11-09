#include "MatPoint.h"

Vector3 MatPoint::R(){
    return Vector3(X(), Y(), Z());
}

Vector3 MatPoint::V(){
    return m_vel;
}

Vector3 MatPoint::GravField(Vector3 pos){
    Vector3 raggio, campo;
    raggio = pos - R();
    campo = -Mass()*(1/(raggio*raggio))*raggio.Unit();
    return campo;
}
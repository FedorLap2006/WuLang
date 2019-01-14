#include "Object.hpp"


BasicObj::BasicObj(Type t,void* value){

}
BasicObj::BasicObj(Type t,BasicObj* v,int tf){

}



Object::Object(Type t,BasicObj* v,int tf):BasicObj(t,v,tf){
    vtobj=Object::VTSTD;
}

Object::Object(Type t,void* value):BasicObj(t,value){
    vtobj=Object::VTSTD;
    this->stdval = new BasicValue;
}

Object::Object(vector<BasicObj> nt,Type t){
    vtobj=Object::VTCUSTOM;
    this->tobj.ftype=t.ftype;
    this->tobj.label=t.label;
    this->tobj.size=t.size;
    this->tobj.tv=t.tv;
    vobj = new vector<BasicObj>;
}
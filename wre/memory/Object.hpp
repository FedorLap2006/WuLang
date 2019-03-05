#pragma once

#include <new>
#include <string>
#include <cstdarg>
#include <cstdlib>

#include <vector>
#include <iterator>

#include <map>

using namespace std;



class BasicObj
{
protected:
    typedef struct BasicValue{
        union{
            void *val;
            BasicObj *child_el;
            BasicObj *near_el;
        };
        short sel;
    };
    BasicValue *stdval;
    struct oType{
        public:
            string label;
            size_t size;
            short ftype; // functional type -- enum,union,struct,...
            short tv;
            enum FT{
                TSTRUCT,
                TENUM,
                TUNION
            };
            enum TV{
                LONG,
                LONGx2,
                UNSG,
                UNSG_LONGx2,
                SHORT,
                UNSG_SHORT
            };
    };
    
public:
    const static short Tchild=1;
    const static short TNear=1;

    typedef struct Type
    {
        public:
            string label;
            size_t size;
            short ftype; // functional type -- enum,union,struct,...
            short tv;
            enum FT{
                TSTRUCT,
                TENUM,
                TUNION
            };
            enum TV{
                LONG,
                LONGx2,
                UNSG,
                UNSG_LONGx2,
                SHORT,
                UNSG_SHORT
            };
    };

    BasicObj(Type t,void *value);
    BasicObj(Type t,BasicObj *v,int tf);
    BasicObj();
    ~BasicObj();
private:
    struct oType tobj;
};



class Object : public BasicObj
{
private:
    vector<BasicObj> *vobj;
    short vtobj;
    const static short VTSTD;
    const static short VTCUSTOM;
    oType tobj;
public:
    Object(Type t,void *value);
    Object(Type t,BasicObj* v,int tf);
    Object(vector<BasicObj> nt,Type t);
    ~Object();
};
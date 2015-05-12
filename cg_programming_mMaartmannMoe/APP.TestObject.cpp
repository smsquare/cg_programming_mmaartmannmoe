// APP.TestObject.cpp
//////////////////////////////////////////////////////////////////////////

#include "APP.TestObject.h"

TestObject::TestObject() {
	LoadTriangles(1, 3, GL_TRIANGLE_STRIP);
	SetScale(vec3(0.5f));
}

TestObject::~TestObject() {

}

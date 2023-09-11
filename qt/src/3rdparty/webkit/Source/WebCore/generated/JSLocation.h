/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef JSLocation_h
#define JSLocation_h

#include "JSDOMBinding.h"
#include <runtime/JSGlobalObject.h>
#include <runtime/JSObjectWithGlobalObject.h>
#include <runtime/ObjectPrototype.h>

namespace WebCore {

class Location;

class JSLocation : public JSDOMWrapper {
    typedef JSDOMWrapper Base;
public:
    JSLocation(JSC::Structure*, JSDOMGlobalObject*, PassRefPtr<Location>);
    static JSC::JSObject* createPrototype(JSC::ExecState*, JSC::JSGlobalObject*);
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::PropertySlot&);
    virtual bool getOwnPropertyDescriptor(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::PropertyDescriptor&);
    bool getOwnPropertySlotDelegate(JSC::ExecState*, const JSC::Identifier&, JSC::PropertySlot&);
    bool getOwnPropertyDescriptorDelegate(JSC::ExecState*, const JSC::Identifier&, JSC::PropertyDescriptor&);
    virtual void put(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::JSValue, JSC::PutPropertySlot&);
    bool putDelegate(JSC::ExecState*, const JSC::Identifier&, JSC::JSValue, JSC::PutPropertySlot&);
    static const JSC::ClassInfo s_info;

    static JSC::Structure* createStructure(JSC::JSGlobalData& globalData, JSC::JSValue prototype)
    {
        return JSC::Structure::create(globalData, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), AnonymousSlotCount, &s_info);
    }

    virtual bool deleteProperty(JSC::ExecState*, const JSC::Identifier&);
    virtual void getOwnPropertyNames(JSC::ExecState*, JSC::PropertyNameArray&, JSC::EnumerationMode mode = JSC::ExcludeDontEnumProperties);
    virtual void defineGetter(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::JSObject* getterFunction, unsigned attributes);

    // Custom attributes
    void setHref(JSC::ExecState*, JSC::JSValue);
    void setProtocol(JSC::ExecState*, JSC::JSValue);
    void setHost(JSC::ExecState*, JSC::JSValue);
    void setHostname(JSC::ExecState*, JSC::JSValue);
    void setPort(JSC::ExecState*, JSC::JSValue);
    void setPathname(JSC::ExecState*, JSC::JSValue);
    void setSearch(JSC::ExecState*, JSC::JSValue);
    void setHash(JSC::ExecState*, JSC::JSValue);

    // Custom functions
    JSC::JSValue assign(JSC::ExecState*);
    JSC::JSValue replace(JSC::ExecState*);
    JSC::JSValue reload(JSC::ExecState*);
    JSC::JSValue toStringFunction(JSC::ExecState*);
    Location* impl() const { return m_impl.get(); }

private:
    RefPtr<Location> m_impl;
protected:
    static const unsigned StructureFlags = JSC::OverridesGetPropertyNames | JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
};

class JSLocationOwner : public JSC::WeakHandleOwner {
    virtual bool isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown>, void* context, JSC::SlotVisitor&);
    virtual void finalize(JSC::Handle<JSC::Unknown>, void* context);
};

inline JSC::WeakHandleOwner* wrapperOwner(DOMWrapperWorld*, Location*)
{
    DEFINE_STATIC_LOCAL(JSLocationOwner, jsLocationOwner, ());
    return &jsLocationOwner;
}

inline void* wrapperContext(DOMWrapperWorld* world, Location*)
{
    return world;
}

JSC::JSValue toJS(JSC::ExecState*, JSDOMGlobalObject*, Location*);
Location* toLocation(JSC::JSValue);

class JSLocationPrototype : public JSC::JSObjectWithGlobalObject {
    typedef JSC::JSObjectWithGlobalObject Base;
public:
    static JSC::JSObject* self(JSC::ExecState*, JSC::JSGlobalObject*);
    static const JSC::ClassInfo s_info;
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier&, JSC::PropertySlot&);
    virtual bool getOwnPropertyDescriptor(JSC::ExecState*, const JSC::Identifier&, JSC::PropertyDescriptor&);
    static JSC::Structure* createStructure(JSC::JSGlobalData& globalData, JSC::JSValue prototype)
    {
        return JSC::Structure::create(globalData, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), AnonymousSlotCount, &s_info);
    }
    virtual void put(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::JSValue, JSC::PutPropertySlot&);
    bool putDelegate(JSC::ExecState*, const JSC::Identifier&, JSC::JSValue, JSC::PutPropertySlot&);
    virtual void defineGetter(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::JSObject* getterFunction, unsigned attributes);
    JSLocationPrototype(JSC::JSGlobalData& globalData, JSC::JSGlobalObject* globalObject, JSC::Structure* structure) : JSC::JSObjectWithGlobalObject(globalData, globalObject, structure) { }
protected:
    static const unsigned StructureFlags = JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
};

// Functions

JSC::EncodedJSValue JSC_HOST_CALL jsLocationPrototypeFunctionAssign(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsLocationPrototypeFunctionReplace(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsLocationPrototypeFunctionReload(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsLocationPrototypeFunctionGetParameter(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsLocationPrototypeFunctionToString(JSC::ExecState*);
// Attributes

JSC::JSValue jsLocationHref(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSLocationHref(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsLocationProtocol(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSLocationProtocol(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsLocationHost(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSLocationHost(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsLocationHostname(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSLocationHostname(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsLocationPort(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSLocationPort(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsLocationPathname(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSLocationPathname(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsLocationSearch(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSLocationSearch(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsLocationHash(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
void setJSLocationHash(JSC::ExecState*, JSC::JSObject*, JSC::JSValue);
JSC::JSValue jsLocationOrigin(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);

} // namespace WebCore

#endif

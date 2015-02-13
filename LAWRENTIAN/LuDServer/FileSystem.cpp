// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.5.1
//
// <auto-generated>
//
// Generated from file `FileSystem.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#include "FileSystem.h"
#include <Ice/LocalException.h>
#include <Ice/ObjectFactory.h>
#include <Ice/BasicStream.h>
#include <Ice/Object.h>
#include <IceUtil/Iterator.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 305
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

namespace
{

const ::std::string __FileSystem__File__receiveFile_name = "receiveFile";

const ::std::string __FileSystem__File__sendFile_name = "sendFile";

}
::IceProxy::Ice::Object* ::IceProxy::FileSystem::upCast(::IceProxy::FileSystem::File* p) { return p; }

void
::IceProxy::FileSystem::__read(::IceInternal::BasicStream* __is, ::IceInternal::ProxyHandle< ::IceProxy::FileSystem::File>& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::FileSystem::File;
        v->__copyFrom(proxy);
    }
}

::FileSystem::ByteSeq
IceProxy::FileSystem::File::receiveFile(const ::std::string& name, const ::Ice::Context* __ctx)
{
    ::IceInternal::InvocationObserver __observer(this, __FileSystem__File__receiveFile_name, __ctx);
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__FileSystem__File__receiveFile_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::FileSystem::File* __del = dynamic_cast< ::IceDelegate::FileSystem::File*>(__delBase.get());
            return __del->receiveFile(name, __ctx, __observer);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex, __observer);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, true, __cnt, __observer);
        }
    }
}

::Ice::AsyncResultPtr
IceProxy::FileSystem::File::begin_receiveFile(const ::std::string& name, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__FileSystem__File__receiveFile_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __FileSystem__File__receiveFile_name, __del, __cookie);
    try
    {
        __result->__prepare(__FileSystem__File__receiveFile_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->__startWriteParams(::Ice::DefaultFormat);
        __os->write(name);
        __result->__endWriteParams();
        __result->__send(true);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __result->__exceptionAsync(__ex);
    }
    return __result;
}

::FileSystem::ByteSeq
IceProxy::FileSystem::File::end_receiveFile(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __FileSystem__File__receiveFile_name);
    ::FileSystem::ByteSeq __ret;
    bool __ok = __result->__wait();
    try
    {
        if(!__ok)
        {
            try
            {
                __result->__throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::IceInternal::BasicStream* __is = __result->__startReadParams();
        __is->read(__ret);
        __result->__endReadParams();
        return __ret;
    }
    catch(const ::Ice::LocalException& ex)
    {
        __result->__getObserver().failed(ex.ice_name());
        throw;
    }
}

bool
IceProxy::FileSystem::File::sendFile(const ::std::string& name, const ::FileSystem::ByteSeq& seq, const ::Ice::Context* __ctx)
{
    ::IceInternal::InvocationObserver __observer(this, __FileSystem__File__sendFile_name, __ctx);
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__FileSystem__File__sendFile_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::FileSystem::File* __del = dynamic_cast< ::IceDelegate::FileSystem::File*>(__delBase.get());
            return __del->sendFile(name, seq, __ctx, __observer);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex, __observer);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, true, __cnt, __observer);
        }
    }
}

::Ice::AsyncResultPtr
IceProxy::FileSystem::File::begin_sendFile(const ::std::string& name, const ::FileSystem::ByteSeq& seq, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__FileSystem__File__sendFile_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __FileSystem__File__sendFile_name, __del, __cookie);
    try
    {
        __result->__prepare(__FileSystem__File__sendFile_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->__startWriteParams(::Ice::DefaultFormat);
        __os->write(name);
        __os->write(seq);
        __result->__endWriteParams();
        __result->__send(true);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __result->__exceptionAsync(__ex);
    }
    return __result;
}

bool
IceProxy::FileSystem::File::end_sendFile(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __FileSystem__File__sendFile_name);
    bool __ret;
    bool __ok = __result->__wait();
    try
    {
        if(!__ok)
        {
            try
            {
                __result->__throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::IceInternal::BasicStream* __is = __result->__startReadParams();
        __is->read(__ret);
        __result->__endReadParams();
        return __ret;
    }
    catch(const ::Ice::LocalException& ex)
    {
        __result->__getObserver().failed(ex.ice_name());
        throw;
    }
}

const ::std::string&
IceProxy::FileSystem::File::ice_staticId()
{
    return ::FileSystem::File::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::FileSystem::File::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::FileSystem::File);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::FileSystem::File::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::FileSystem::File);
}

::IceProxy::Ice::Object*
IceProxy::FileSystem::File::__newInstance() const
{
    return new File;
}

::FileSystem::ByteSeq
IceDelegateM::FileSystem::File::receiveFile(const ::std::string& name, const ::Ice::Context* __context, ::IceInternal::InvocationObserver& __observer)
{
    ::IceInternal::Outgoing __og(__handler.get(), __FileSystem__File__receiveFile_name, ::Ice::Normal, __context, __observer);
    try
    {
        ::IceInternal::BasicStream* __os = __og.startWriteParams(::Ice::DefaultFormat);
        __os->write(name);
        __og.endWriteParams();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    ::FileSystem::ByteSeq __ret;
    try
    {
        if(!__ok)
        {
            try
            {
                __og.throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
                throw __uue;
            }
        }
        ::IceInternal::BasicStream* __is = __og.startReadParams();
        __is->read(__ret);
        __og.endReadParams();
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

bool
IceDelegateM::FileSystem::File::sendFile(const ::std::string& name, const ::FileSystem::ByteSeq& seq, const ::Ice::Context* __context, ::IceInternal::InvocationObserver& __observer)
{
    ::IceInternal::Outgoing __og(__handler.get(), __FileSystem__File__sendFile_name, ::Ice::Normal, __context, __observer);
    try
    {
        ::IceInternal::BasicStream* __os = __og.startWriteParams(::Ice::DefaultFormat);
        __os->write(name);
        __os->write(seq);
        __og.endWriteParams();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    bool __ret;
    try
    {
        if(!__ok)
        {
            try
            {
                __og.throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
                throw __uue;
            }
        }
        ::IceInternal::BasicStream* __is = __og.startReadParams();
        __is->read(__ret);
        __og.endReadParams();
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::FileSystem::ByteSeq
IceDelegateD::FileSystem::File::receiveFile(const ::std::string& name, const ::Ice::Context* __context, ::IceInternal::InvocationObserver&)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(::FileSystem::ByteSeq& __result, const ::std::string& __p_name, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _result(__result),
            _m_name(__p_name)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::FileSystem::File* servant = dynamic_cast< ::FileSystem::File*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            _result = servant->receiveFile(_m_name, _current);
            return ::Ice::DispatchOK;
        }
        
    private:
        
        ::FileSystem::ByteSeq& _result;
        const ::std::string& _m_name;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __FileSystem__File__receiveFile_name, ::Ice::Normal, __context);
    ::FileSystem::ByteSeq __result;
    try
    {
        _DirectI __direct(__result, name, __current);
        try
        {
            __direct.getServant()->__collocDispatch(__direct);
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
    }
    catch(const ::Ice::SystemException&)
    {
        throw;
    }
    catch(const ::IceInternal::LocalExceptionWrapper&)
    {
        throw;
    }
    catch(const ::std::exception& __ex)
    {
        ::IceInternal::LocalExceptionWrapper::throwWrapper(__ex);
    }
    catch(...)
    {
        throw ::IceInternal::LocalExceptionWrapper(::Ice::UnknownException(__FILE__, __LINE__, "unknown c++ exception"), false);
    }
    return __result;
}

bool
IceDelegateD::FileSystem::File::sendFile(const ::std::string& name, const ::FileSystem::ByteSeq& seq, const ::Ice::Context* __context, ::IceInternal::InvocationObserver&)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(bool& __result, const ::std::string& __p_name, const ::FileSystem::ByteSeq& __p_seq, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _result(__result),
            _m_name(__p_name),
            _m_seq(__p_seq)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::FileSystem::File* servant = dynamic_cast< ::FileSystem::File*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            _result = servant->sendFile(_m_name, _m_seq, _current);
            return ::Ice::DispatchOK;
        }
        
    private:
        
        bool& _result;
        const ::std::string& _m_name;
        const ::FileSystem::ByteSeq& _m_seq;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __FileSystem__File__sendFile_name, ::Ice::Normal, __context);
    bool __result;
    try
    {
        _DirectI __direct(__result, name, seq, __current);
        try
        {
            __direct.getServant()->__collocDispatch(__direct);
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
    }
    catch(const ::Ice::SystemException&)
    {
        throw;
    }
    catch(const ::IceInternal::LocalExceptionWrapper&)
    {
        throw;
    }
    catch(const ::std::exception& __ex)
    {
        ::IceInternal::LocalExceptionWrapper::throwWrapper(__ex);
    }
    catch(...)
    {
        throw ::IceInternal::LocalExceptionWrapper(::Ice::UnknownException(__FILE__, __LINE__, "unknown c++ exception"), false);
    }
    return __result;
}

::Ice::Object* FileSystem::upCast(::FileSystem::File* p) { return p; }

namespace
{
const ::std::string __FileSystem__File_ids[2] =
{
    "::FileSystem::File",
    "::Ice::Object"
};

}

bool
FileSystem::File::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__FileSystem__File_ids, __FileSystem__File_ids + 2, _s);
}

::std::vector< ::std::string>
FileSystem::File::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__FileSystem__File_ids[0], &__FileSystem__File_ids[2]);
}

const ::std::string&
FileSystem::File::ice_id(const ::Ice::Current&) const
{
    return __FileSystem__File_ids[0];
}

const ::std::string&
FileSystem::File::ice_staticId()
{
    return __FileSystem__File_ids[0];
}

::Ice::DispatchStatus
FileSystem::File::___receiveFile(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.startReadParams();
    ::std::string name;
    __is->read(name);
    __inS.endReadParams();
    ::FileSystem::ByteSeq __ret = receiveFile(name, __current);
    ::IceInternal::BasicStream* __os = __inS.__startWriteParams(::Ice::DefaultFormat);
    __os->write(__ret);
    __inS.__endWriteParams(true);
    return ::Ice::DispatchOK;
}

::Ice::DispatchStatus
FileSystem::File::___sendFile(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.startReadParams();
    ::std::string name;
    ::FileSystem::ByteSeq seq;
    __is->read(name);
    __is->read(seq);
    __inS.endReadParams();
    bool __ret = sendFile(name, seq, __current);
    ::IceInternal::BasicStream* __os = __inS.__startWriteParams(::Ice::DefaultFormat);
    __os->write(__ret);
    __inS.__endWriteParams(true);
    return ::Ice::DispatchOK;
}

namespace
{
const ::std::string __FileSystem__File_all[] =
{
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "receiveFile",
    "sendFile"
};

}

::Ice::DispatchStatus
FileSystem::File::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< const ::std::string*, const ::std::string*> r = ::std::equal_range(__FileSystem__File_all, __FileSystem__File_all + 6, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __FileSystem__File_all)
    {
        case 0:
        {
            return ___ice_id(in, current);
        }
        case 1:
        {
            return ___ice_ids(in, current);
        }
        case 2:
        {
            return ___ice_isA(in, current);
        }
        case 3:
        {
            return ___ice_ping(in, current);
        }
        case 4:
        {
            return ___receiveFile(in, current);
        }
        case 5:
        {
            return ___sendFile(in, current);
        }
    }

    assert(false);
    throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}

void
FileSystem::File::__writeImpl(::IceInternal::BasicStream* __os) const
{
    __os->startWriteSlice(ice_staticId(), -1, true);
    __os->endWriteSlice();
}

void
FileSystem::File::__readImpl(::IceInternal::BasicStream* __is)
{
    __is->startReadSlice();
    __is->endReadSlice();
}

void 
FileSystem::__patch(FilePtr& handle, const ::Ice::ObjectPtr& v)
{
    handle = ::FileSystem::FilePtr::dynamicCast(v);
    if(v && !handle)
    {
        IceInternal::Ex::throwUOE(::FileSystem::File::ice_staticId(), v);
    }
}
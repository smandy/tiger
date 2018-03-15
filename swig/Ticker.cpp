// **********************************************************************
//
// Copyright (c) 2003-2017 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.7.0
//
// <auto-generated>
//
// Generated from file `Ticker.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#include <Ticker.h>
#include <IceUtil/PushDisableWarnings.h>
#include <Ice/LocalException.h>
#include <Ice/ValueFactory.h>
#include <Ice/OutgoingAsync.h>
#include <Ice/InputStream.h>
#include <Ice/OutputStream.h>
#include <IceUtil/PopDisableWarnings.h>

#if defined(_MSC_VER)
#   pragma warning(disable:4458) // declaration of ... hides class member
#elif defined(__clang__)
#   pragma clang diagnostic ignored "-Wshadow"
#elif defined(__GNUC__)
#   pragma GCC diagnostic ignored "-Wshadow"
#endif

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 307
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 0
#       error Ice patch level mismatch!
#   endif
#endif

#ifdef ICE_CPP11_MAPPING // C++11 mapping

namespace
{

const ::std::string iceC_argo_TickListener_ids[2] =
{
    "::Ice::Object",
    "::argo::TickListener"
};
const ::std::string iceC_argo_TickListener_ops[] =
{
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "onImage",
    "onTick"
};
const ::std::string iceC_argo_TickListener_onTick_name = "onTick";
const ::std::string iceC_argo_TickListener_onImage_name = "onImage";

const ::std::string iceC_argo_TickerPlant_ids[2] =
{
    "::Ice::Object",
    "::argo::TickerPlant"
};
const ::std::string iceC_argo_TickerPlant_ops[] =
{
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "sayHello",
    "subscribe",
    "subscribeWithIdent"
};
const ::std::string iceC_argo_TickerPlant_subscribe_name = "subscribe";
const ::std::string iceC_argo_TickerPlant_subscribeWithIdent_name = "subscribeWithIdent";
const ::std::string iceC_argo_TickerPlant_sayHello_name = "sayHello";

}

bool
argo::TickListener::ice_isA(::std::string s, const ::Ice::Current&) const
{
    return ::std::binary_search(iceC_argo_TickListener_ids, iceC_argo_TickListener_ids + 2, s);
}

::std::vector<::std::string>
argo::TickListener::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector<::std::string>(&iceC_argo_TickListener_ids[0], &iceC_argo_TickListener_ids[2]);
}

::std::string
argo::TickListener::ice_id(const ::Ice::Current&) const
{
    return ice_staticId();
}

const ::std::string&
argo::TickListener::ice_staticId()
{
    static const ::std::string typeId = "::argo::TickListener";
    return typeId;
}

bool
argo::TickListener::_iceD_onTick(::IceInternal::Incoming& inS, const ::Ice::Current& current)
{
    _iceCheckMode(::Ice::OperationMode::Normal, current.mode);
    auto istr = inS.startReadParams();
    ::argo::TickSeq iceP_t;
    istr->readAll(iceP_t);
    inS.endReadParams();
    this->onTick(::std::move(iceP_t), current);
    inS.writeEmptyParams();
    return true;
}

bool
argo::TickListener::_iceD_onImage(::IceInternal::Incoming& inS, const ::Ice::Current& current)
{
    _iceCheckMode(::Ice::OperationMode::Normal, current.mode);
    auto istr = inS.startReadParams();
    ::argo::TickImage iceP_img;
    istr->readAll(iceP_img);
    inS.endReadParams();
    this->onImage(::std::move(iceP_img), current);
    inS.writeEmptyParams();
    return true;
}

bool
argo::TickListener::_iceDispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair<const ::std::string*, const ::std::string*> r = ::std::equal_range(iceC_argo_TickListener_ops, iceC_argo_TickListener_ops + 6, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - iceC_argo_TickListener_ops)
    {
        case 0:
        {
            return _iceD_ice_id(in, current);
        }
        case 1:
        {
            return _iceD_ice_ids(in, current);
        }
        case 2:
        {
            return _iceD_ice_isA(in, current);
        }
        case 3:
        {
            return _iceD_ice_ping(in, current);
        }
        case 4:
        {
            return _iceD_onImage(in, current);
        }
        case 5:
        {
            return _iceD_onTick(in, current);
        }
        default:
        {
            assert(false);
            throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
        }
    }
}

bool
argo::TickerPlant::ice_isA(::std::string s, const ::Ice::Current&) const
{
    return ::std::binary_search(iceC_argo_TickerPlant_ids, iceC_argo_TickerPlant_ids + 2, s);
}

::std::vector<::std::string>
argo::TickerPlant::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector<::std::string>(&iceC_argo_TickerPlant_ids[0], &iceC_argo_TickerPlant_ids[2]);
}

::std::string
argo::TickerPlant::ice_id(const ::Ice::Current&) const
{
    return ice_staticId();
}

const ::std::string&
argo::TickerPlant::ice_staticId()
{
    static const ::std::string typeId = "::argo::TickerPlant";
    return typeId;
}

bool
argo::TickerPlant::_iceD_subscribe(::IceInternal::Incoming& inS, const ::Ice::Current& current)
{
    _iceCheckMode(::Ice::OperationMode::Normal, current.mode);
    auto istr = inS.startReadParams();
    ::std::shared_ptr<::argo::TickListenerPrx> iceP_l;
    istr->readAll(iceP_l);
    inS.endReadParams();
    this->subscribe(::std::move(iceP_l), current);
    inS.writeEmptyParams();
    return true;
}

bool
argo::TickerPlant::_iceD_subscribeWithIdent(::IceInternal::Incoming& inS, const ::Ice::Current& current)
{
    _iceCheckMode(::Ice::OperationMode::Normal, current.mode);
    auto istr = inS.startReadParams();
    ::Ice::Identity iceP_ident;
    istr->readAll(iceP_ident);
    inS.endReadParams();
    this->subscribeWithIdent(::std::move(iceP_ident), current);
    inS.writeEmptyParams();
    return true;
}

bool
argo::TickerPlant::_iceD_sayHello(::IceInternal::Incoming& inS, const ::Ice::Current& current)
{
    _iceCheckMode(::Ice::OperationMode::Normal, current.mode);
    inS.readEmptyParams();
    ::std::string ret = this->sayHello(current);
    auto ostr = inS.startWriteParams();
    ostr->writeAll(ret);
    inS.endWriteParams();
    return true;
}

bool
argo::TickerPlant::_iceDispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair<const ::std::string*, const ::std::string*> r = ::std::equal_range(iceC_argo_TickerPlant_ops, iceC_argo_TickerPlant_ops + 7, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - iceC_argo_TickerPlant_ops)
    {
        case 0:
        {
            return _iceD_ice_id(in, current);
        }
        case 1:
        {
            return _iceD_ice_ids(in, current);
        }
        case 2:
        {
            return _iceD_ice_isA(in, current);
        }
        case 3:
        {
            return _iceD_ice_ping(in, current);
        }
        case 4:
        {
            return _iceD_sayHello(in, current);
        }
        case 5:
        {
            return _iceD_subscribe(in, current);
        }
        case 6:
        {
            return _iceD_subscribeWithIdent(in, current);
        }
        default:
        {
            assert(false);
            throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
        }
    }
}

void
argo::TickListenerPrx::_iceI_onTick(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<void>>& outAsync, const ::argo::TickSeq& iceP_t, const ::Ice::Context& context)
{
    outAsync->invoke(iceC_argo_TickListener_onTick_name, ::Ice::OperationMode::Normal, ::Ice::FormatType::DefaultFormat, context,
        [&](::Ice::OutputStream* ostr)
        {
            ostr->writeAll(iceP_t);
        },
        nullptr);
}

void
argo::TickListenerPrx::_iceI_onImage(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<void>>& outAsync, const ::argo::TickImage& iceP_img, const ::Ice::Context& context)
{
    outAsync->invoke(iceC_argo_TickListener_onImage_name, ::Ice::OperationMode::Normal, ::Ice::FormatType::DefaultFormat, context,
        [&](::Ice::OutputStream* ostr)
        {
            ostr->writeAll(iceP_img);
        },
        nullptr);
}

::std::shared_ptr<::Ice::ObjectPrx>
argo::TickListenerPrx::_newInstance() const
{
    return ::IceInternal::createProxy<TickListenerPrx>();
}

const ::std::string&
argo::TickListenerPrx::ice_staticId()
{
    return argo::TickListener::ice_staticId();
}

void
argo::TickerPlantPrx::_iceI_subscribe(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<void>>& outAsync, const ::std::shared_ptr<::argo::TickListenerPrx>& iceP_l, const ::Ice::Context& context)
{
    outAsync->invoke(iceC_argo_TickerPlant_subscribe_name, ::Ice::OperationMode::Normal, ::Ice::FormatType::DefaultFormat, context,
        [&](::Ice::OutputStream* ostr)
        {
            ostr->writeAll(iceP_l);
        },
        nullptr);
}

void
argo::TickerPlantPrx::_iceI_subscribeWithIdent(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<void>>& outAsync, const ::Ice::Identity& iceP_ident, const ::Ice::Context& context)
{
    outAsync->invoke(iceC_argo_TickerPlant_subscribeWithIdent_name, ::Ice::OperationMode::Normal, ::Ice::FormatType::DefaultFormat, context,
        [&](::Ice::OutputStream* ostr)
        {
            ostr->writeAll(iceP_ident);
        },
        nullptr);
}

void
argo::TickerPlantPrx::_iceI_sayHello(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<::std::string>>& outAsync, const ::Ice::Context& context)
{
    _checkTwowayOnly(iceC_argo_TickerPlant_sayHello_name);
    outAsync->invoke(iceC_argo_TickerPlant_sayHello_name, ::Ice::OperationMode::Normal, ::Ice::FormatType::DefaultFormat, context,
        nullptr,
        nullptr);
}

::std::shared_ptr<::Ice::ObjectPrx>
argo::TickerPlantPrx::_newInstance() const
{
    return ::IceInternal::createProxy<TickerPlantPrx>();
}

const ::std::string&
argo::TickerPlantPrx::ice_staticId()
{
    return argo::TickerPlant::ice_staticId();
}

namespace Ice
{
}

#else // C++98 mapping

namespace
{

const ::std::string iceC_argo_TickListener_onTick_name = "onTick";

const ::std::string iceC_argo_TickListener_onImage_name = "onImage";

const ::std::string iceC_argo_TickerPlant_subscribe_name = "subscribe";

const ::std::string iceC_argo_TickerPlant_subscribeWithIdent_name = "subscribeWithIdent";

const ::std::string iceC_argo_TickerPlant_sayHello_name = "sayHello";

}
::IceProxy::Ice::Object* ::IceProxy::argo::upCast(::IceProxy::argo::TickListener* p) { return p; }

void
::IceProxy::argo::_readProxy(::Ice::InputStream* istr, ::IceInternal::ProxyHandle< ::IceProxy::argo::TickListener>& v)
{
    ::Ice::ObjectPrx proxy;
    istr->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::argo::TickListener;
        v->_copyFrom(proxy);
    }
}

::Ice::AsyncResultPtr
IceProxy::argo::TickListener::_iceI_begin_onTick(const ::argo::TickSeq& iceP_t, const ::Ice::Context& context, const ::IceInternal::CallbackBasePtr& del, const ::Ice::LocalObjectPtr& cookie, bool sync)
{
    ::IceInternal::OutgoingAsyncPtr result = new ::IceInternal::CallbackOutgoing(this, iceC_argo_TickListener_onTick_name, del, cookie, sync);
    try
    {
        result->prepare(iceC_argo_TickListener_onTick_name, ::Ice::Normal, context);
        ::Ice::OutputStream* ostr = result->startWriteParams(::Ice::DefaultFormat);
        ostr->write(iceP_t);
        result->endWriteParams();
        result->invoke(iceC_argo_TickListener_onTick_name);
    }
    catch(const ::Ice::Exception& ex)
    {
        result->abort(ex);
    }
    return result;
}

void
IceProxy::argo::TickListener::end_onTick(const ::Ice::AsyncResultPtr& result)
{
    _end(result, iceC_argo_TickListener_onTick_name);
}

::Ice::AsyncResultPtr
IceProxy::argo::TickListener::_iceI_begin_onImage(const ::argo::TickImage& iceP_img, const ::Ice::Context& context, const ::IceInternal::CallbackBasePtr& del, const ::Ice::LocalObjectPtr& cookie, bool sync)
{
    ::IceInternal::OutgoingAsyncPtr result = new ::IceInternal::CallbackOutgoing(this, iceC_argo_TickListener_onImage_name, del, cookie, sync);
    try
    {
        result->prepare(iceC_argo_TickListener_onImage_name, ::Ice::Normal, context);
        ::Ice::OutputStream* ostr = result->startWriteParams(::Ice::DefaultFormat);
        ostr->write(iceP_img);
        result->endWriteParams();
        result->invoke(iceC_argo_TickListener_onImage_name);
    }
    catch(const ::Ice::Exception& ex)
    {
        result->abort(ex);
    }
    return result;
}

void
IceProxy::argo::TickListener::end_onImage(const ::Ice::AsyncResultPtr& result)
{
    _end(result, iceC_argo_TickListener_onImage_name);
}

::IceProxy::Ice::Object*
IceProxy::argo::TickListener::_newInstance() const
{
    return new TickListener;
}

const ::std::string&
IceProxy::argo::TickListener::ice_staticId()
{
    return ::argo::TickListener::ice_staticId();
}
::IceProxy::Ice::Object* ::IceProxy::argo::upCast(::IceProxy::argo::TickerPlant* p) { return p; }

void
::IceProxy::argo::_readProxy(::Ice::InputStream* istr, ::IceInternal::ProxyHandle< ::IceProxy::argo::TickerPlant>& v)
{
    ::Ice::ObjectPrx proxy;
    istr->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::argo::TickerPlant;
        v->_copyFrom(proxy);
    }
}

::Ice::AsyncResultPtr
IceProxy::argo::TickerPlant::_iceI_begin_subscribe(const ::argo::TickListenerPrx& iceP_l, const ::Ice::Context& context, const ::IceInternal::CallbackBasePtr& del, const ::Ice::LocalObjectPtr& cookie, bool sync)
{
    ::IceInternal::OutgoingAsyncPtr result = new ::IceInternal::CallbackOutgoing(this, iceC_argo_TickerPlant_subscribe_name, del, cookie, sync);
    try
    {
        result->prepare(iceC_argo_TickerPlant_subscribe_name, ::Ice::Normal, context);
        ::Ice::OutputStream* ostr = result->startWriteParams(::Ice::DefaultFormat);
        ostr->write(iceP_l);
        result->endWriteParams();
        result->invoke(iceC_argo_TickerPlant_subscribe_name);
    }
    catch(const ::Ice::Exception& ex)
    {
        result->abort(ex);
    }
    return result;
}

void
IceProxy::argo::TickerPlant::end_subscribe(const ::Ice::AsyncResultPtr& result)
{
    _end(result, iceC_argo_TickerPlant_subscribe_name);
}

::Ice::AsyncResultPtr
IceProxy::argo::TickerPlant::_iceI_begin_subscribeWithIdent(const ::Ice::Identity& iceP_ident, const ::Ice::Context& context, const ::IceInternal::CallbackBasePtr& del, const ::Ice::LocalObjectPtr& cookie, bool sync)
{
    ::IceInternal::OutgoingAsyncPtr result = new ::IceInternal::CallbackOutgoing(this, iceC_argo_TickerPlant_subscribeWithIdent_name, del, cookie, sync);
    try
    {
        result->prepare(iceC_argo_TickerPlant_subscribeWithIdent_name, ::Ice::Normal, context);
        ::Ice::OutputStream* ostr = result->startWriteParams(::Ice::DefaultFormat);
        ostr->write(iceP_ident);
        result->endWriteParams();
        result->invoke(iceC_argo_TickerPlant_subscribeWithIdent_name);
    }
    catch(const ::Ice::Exception& ex)
    {
        result->abort(ex);
    }
    return result;
}

void
IceProxy::argo::TickerPlant::end_subscribeWithIdent(const ::Ice::AsyncResultPtr& result)
{
    _end(result, iceC_argo_TickerPlant_subscribeWithIdent_name);
}

::Ice::AsyncResultPtr
IceProxy::argo::TickerPlant::_iceI_begin_sayHello(const ::Ice::Context& context, const ::IceInternal::CallbackBasePtr& del, const ::Ice::LocalObjectPtr& cookie, bool sync)
{
    _checkTwowayOnly(iceC_argo_TickerPlant_sayHello_name, sync);
    ::IceInternal::OutgoingAsyncPtr result = new ::IceInternal::CallbackOutgoing(this, iceC_argo_TickerPlant_sayHello_name, del, cookie, sync);
    try
    {
        result->prepare(iceC_argo_TickerPlant_sayHello_name, ::Ice::Normal, context);
        result->writeEmptyParams();
        result->invoke(iceC_argo_TickerPlant_sayHello_name);
    }
    catch(const ::Ice::Exception& ex)
    {
        result->abort(ex);
    }
    return result;
}

::std::string
IceProxy::argo::TickerPlant::end_sayHello(const ::Ice::AsyncResultPtr& result)
{
    ::Ice::AsyncResult::_check(result, this, iceC_argo_TickerPlant_sayHello_name);
    ::std::string ret;
    if(!result->_waitForResponse())
    {
        try
        {
            result->_throwUserException();
        }
        catch(const ::Ice::UserException& ex)
        {
            throw ::Ice::UnknownUserException(__FILE__, __LINE__, ex.ice_id());
        }
    }
    ::Ice::InputStream* istr = result->_startReadParams();
    istr->read(ret);
    result->_endReadParams();
    return ret;
}

::IceProxy::Ice::Object*
IceProxy::argo::TickerPlant::_newInstance() const
{
    return new TickerPlant;
}

const ::std::string&
IceProxy::argo::TickerPlant::ice_staticId()
{
    return ::argo::TickerPlant::ice_staticId();
}

argo::TickListener::~TickListener()
{
}

::Ice::Object* argo::upCast(::argo::TickListener* p) { return p; }


namespace
{
const ::std::string iceC_argo_TickListener_ids[2] =
{
    "::Ice::Object",
    "::argo::TickListener"
};

}

bool
argo::TickListener::ice_isA(const ::std::string& s, const ::Ice::Current&) const
{
    return ::std::binary_search(iceC_argo_TickListener_ids, iceC_argo_TickListener_ids + 2, s);
}

::std::vector< ::std::string>
argo::TickListener::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&iceC_argo_TickListener_ids[0], &iceC_argo_TickListener_ids[2]);
}

const ::std::string&
argo::TickListener::ice_id(const ::Ice::Current&) const
{
    return ice_staticId();
}

const ::std::string&
argo::TickListener::ice_staticId()
{
#ifdef ICE_HAS_THREAD_SAFE_LOCAL_STATIC
    static const ::std::string typeId = "::argo::TickListener";
    return typeId;
#else
    return iceC_argo_TickListener_ids[1];
#endif
}

bool
argo::TickListener::_iceD_onTick(::IceInternal::Incoming& inS, const ::Ice::Current& current)
{
    _iceCheckMode(::Ice::Normal, current.mode);
    ::Ice::InputStream* istr = inS.startReadParams();
    ::argo::TickSeq iceP_t;
    istr->read(iceP_t);
    inS.endReadParams();
    this->onTick(iceP_t, current);
    inS.writeEmptyParams();
    return true;
}

bool
argo::TickListener::_iceD_onImage(::IceInternal::Incoming& inS, const ::Ice::Current& current)
{
    _iceCheckMode(::Ice::Normal, current.mode);
    ::Ice::InputStream* istr = inS.startReadParams();
    ::argo::TickImage iceP_img;
    istr->read(iceP_img);
    inS.endReadParams();
    this->onImage(iceP_img, current);
    inS.writeEmptyParams();
    return true;
}

namespace
{
const ::std::string iceC_argo_TickListener_all[] =
{
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "onImage",
    "onTick"
};

}

bool
argo::TickListener::_iceDispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair<const ::std::string*, const ::std::string*> r = ::std::equal_range(iceC_argo_TickListener_all, iceC_argo_TickListener_all + 6, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - iceC_argo_TickListener_all)
    {
        case 0:
        {
            return _iceD_ice_id(in, current);
        }
        case 1:
        {
            return _iceD_ice_ids(in, current);
        }
        case 2:
        {
            return _iceD_ice_isA(in, current);
        }
        case 3:
        {
            return _iceD_ice_ping(in, current);
        }
        case 4:
        {
            return _iceD_onImage(in, current);
        }
        case 5:
        {
            return _iceD_onTick(in, current);
        }
        default:
        {
            assert(false);
            throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
        }
    }
}

void
argo::TickListener::_iceWriteImpl(::Ice::OutputStream* ostr) const
{
    ostr->startSlice(ice_staticId(), -1, true);
    Ice::StreamWriter< ::argo::TickListener, ::Ice::OutputStream>::write(ostr, *this);
    ostr->endSlice();
}

void
argo::TickListener::_iceReadImpl(::Ice::InputStream* istr)
{
    istr->startSlice();
    Ice::StreamReader< ::argo::TickListener, ::Ice::InputStream>::read(istr, *this);
    istr->endSlice();
}

void
argo::_icePatchObjectPtr(TickListenerPtr& handle, const ::Ice::ObjectPtr& v)
{
    handle = ::argo::TickListenerPtr::dynamicCast(v);
    if(v && !handle)
    {
        IceInternal::Ex::throwUOE(::argo::TickListener::ice_staticId(), v);
    }
}

argo::TickerPlant::~TickerPlant()
{
}

::Ice::Object* argo::upCast(::argo::TickerPlant* p) { return p; }


namespace
{
const ::std::string iceC_argo_TickerPlant_ids[2] =
{
    "::Ice::Object",
    "::argo::TickerPlant"
};

}

bool
argo::TickerPlant::ice_isA(const ::std::string& s, const ::Ice::Current&) const
{
    return ::std::binary_search(iceC_argo_TickerPlant_ids, iceC_argo_TickerPlant_ids + 2, s);
}

::std::vector< ::std::string>
argo::TickerPlant::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&iceC_argo_TickerPlant_ids[0], &iceC_argo_TickerPlant_ids[2]);
}

const ::std::string&
argo::TickerPlant::ice_id(const ::Ice::Current&) const
{
    return ice_staticId();
}

const ::std::string&
argo::TickerPlant::ice_staticId()
{
#ifdef ICE_HAS_THREAD_SAFE_LOCAL_STATIC
    static const ::std::string typeId = "::argo::TickerPlant";
    return typeId;
#else
    return iceC_argo_TickerPlant_ids[1];
#endif
}

bool
argo::TickerPlant::_iceD_subscribe(::IceInternal::Incoming& inS, const ::Ice::Current& current)
{
    _iceCheckMode(::Ice::Normal, current.mode);
    ::Ice::InputStream* istr = inS.startReadParams();
    ::argo::TickListenerPrx iceP_l;
    istr->read(iceP_l);
    inS.endReadParams();
    this->subscribe(iceP_l, current);
    inS.writeEmptyParams();
    return true;
}

bool
argo::TickerPlant::_iceD_subscribeWithIdent(::IceInternal::Incoming& inS, const ::Ice::Current& current)
{
    _iceCheckMode(::Ice::Normal, current.mode);
    ::Ice::InputStream* istr = inS.startReadParams();
    ::Ice::Identity iceP_ident;
    istr->read(iceP_ident);
    inS.endReadParams();
    this->subscribeWithIdent(iceP_ident, current);
    inS.writeEmptyParams();
    return true;
}

bool
argo::TickerPlant::_iceD_sayHello(::IceInternal::Incoming& inS, const ::Ice::Current& current)
{
    _iceCheckMode(::Ice::Normal, current.mode);
    inS.readEmptyParams();
    ::std::string ret = this->sayHello(current);
    ::Ice::OutputStream* ostr = inS.startWriteParams();
    ostr->write(ret);
    inS.endWriteParams();
    return true;
}

namespace
{
const ::std::string iceC_argo_TickerPlant_all[] =
{
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "sayHello",
    "subscribe",
    "subscribeWithIdent"
};

}

bool
argo::TickerPlant::_iceDispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair<const ::std::string*, const ::std::string*> r = ::std::equal_range(iceC_argo_TickerPlant_all, iceC_argo_TickerPlant_all + 7, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - iceC_argo_TickerPlant_all)
    {
        case 0:
        {
            return _iceD_ice_id(in, current);
        }
        case 1:
        {
            return _iceD_ice_ids(in, current);
        }
        case 2:
        {
            return _iceD_ice_isA(in, current);
        }
        case 3:
        {
            return _iceD_ice_ping(in, current);
        }
        case 4:
        {
            return _iceD_sayHello(in, current);
        }
        case 5:
        {
            return _iceD_subscribe(in, current);
        }
        case 6:
        {
            return _iceD_subscribeWithIdent(in, current);
        }
        default:
        {
            assert(false);
            throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
        }
    }
}

void
argo::TickerPlant::_iceWriteImpl(::Ice::OutputStream* ostr) const
{
    ostr->startSlice(ice_staticId(), -1, true);
    Ice::StreamWriter< ::argo::TickerPlant, ::Ice::OutputStream>::write(ostr, *this);
    ostr->endSlice();
}

void
argo::TickerPlant::_iceReadImpl(::Ice::InputStream* istr)
{
    istr->startSlice();
    Ice::StreamReader< ::argo::TickerPlant, ::Ice::InputStream>::read(istr, *this);
    istr->endSlice();
}

void
argo::_icePatchObjectPtr(TickerPlantPtr& handle, const ::Ice::ObjectPtr& v)
{
    handle = ::argo::TickerPlantPtr::dynamicCast(v);
    if(v && !handle)
    {
        IceInternal::Ex::throwUOE(::argo::TickerPlant::ice_staticId(), v);
    }
}

namespace Ice
{
}

#endif

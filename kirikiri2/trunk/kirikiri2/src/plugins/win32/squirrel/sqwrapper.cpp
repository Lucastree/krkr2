#include <windows.h>
#include "tp_stub.h"
#include <squirrel.h>

void store(HSQUIRRELVM v, iTJSDispatch2 *dispatch);
void store(HSQUIRRELVM v, tTJSVariant &variant);
void store(tTJSVariant &result, HSQUIRRELVM v, HSQOBJECT &obj);
void store(tTJSVariant &result, HSQUIRRELVM v, int idx=-1);

static const SQUserPointer TJSTYPETAG = (SQUserPointer)"TJSTYPETAG";

/**
 * �G���[����
 */
void
SQEXCEPTION(HSQUIRRELVM v)
{
	sq_getlasterror(v);
	const SQChar *str;
	sq_getstring(v, -1, &str);
	ttstr error = str;
	sq_pop(v, 1);
	TVPThrowExceptionMessage(error.c_str());
}

/**
 * IDispatch �p iTJSDispatch2 ���b�p�[
 */
class iTJSDispatch2Wrapper : public tTJSDispatch
{
protected:
	/// �����ێ��p
	HSQUIRRELVM v;
	HSQOBJECT obj;

public:
	/**
	 * �R���X�g���N�^
	 * @param obj IDispatch
	 */
	iTJSDispatch2Wrapper(HSQUIRRELVM v, HSQOBJECT obj) : v(v), obj(obj) {
		sq_addref(v, &obj);
	}
	
	/**
	 * �f�X�g���N�^
	 */
	~iTJSDispatch2Wrapper() {
		if(v) {
			sq_release(v, &obj);
		}
	}

public:

	tjs_error TJS_INTF_METHOD CreateNew(
		tjs_uint32 flag,
		const tjs_char * membername,
		tjs_uint32 *hint,
		iTJSDispatch2 **result,
		tjs_int numparams,
		tTJSVariant **param,
		iTJSDispatch2 *objthis
		)
	{
		if (membername) {
			return TJS_E_MEMBERNOTFOUND;
		}
		if (obj._type != OT_CLASS) {
			return TJS_E_NOTIMPL;
		}
		int ret = S_FALSE;
		sq_pushobject(v, obj);
		sq_pushroottable(v);			// this ��������
		for (int i=0;i<numparams;i++) {	// �p�����[�^�Q
			store(v, *param[i]);
		}
		if (!SQ_SUCCEEDED(sq_call(v, numparams + 1, result ? SQTrue:SQFalse, SQTrue))) {
			sq_pop(v, 1);
			SQEXCEPTION(v);
		}
		if (result) {
			HSQOBJECT x;
			sq_resetobject(&x);
			sq_getstackobj(v,-1,&x);
			*result = new iTJSDispatch2Wrapper(v, x);
		}
		sq_pop(v, 1);
		return TJS_S_OK;
	}

	
	tjs_error TJS_INTF_METHOD FuncCall(
		tjs_uint32 flag,
		const tjs_char * membername,
		tjs_uint32 *hint,
		tTJSVariant *result,
		tjs_int numparams,
		tTJSVariant **param,
		iTJSDispatch2 *objthis
		) {
		if (membername == NULL) {
			if (!(obj._type == OT_CLOSURE ||
				  obj._type == OT_NATIVECLOSURE ||
				  obj._type == OT_GENERATOR)) {
				return TJS_E_NOTIMPL;
			}
			sq_pushobject(v, obj);
			sq_pushroottable(v);
			for (int i=0;i<numparams;i++) {	// �p�����[�^�Q
				store(v, *param[i]);
			}
			if (!SQ_SUCCEEDED(sq_call(v, numparams + 1, result ? SQTrue:SQFalse, SQTrue))) {
				sq_pop(v, 1);
				SQEXCEPTION(v);
			}
			if (result) {
				store(*result, v);
				sq_pop(v, 1);
			}
			sq_pop(v, 1);
			return TJS_S_OK;
		} else {
			sq_pushobject(v, obj);
			sq_pushstring(v, membername,-1);
			if (!SQ_SUCCEEDED(sq_get(v,-2))) {
				sq_pop(v, 1);
				return TJS_E_MEMBERNOTFOUND;
			}
			sq_pushobject(v, obj); // this
			for (int i=0;i<numparams;i++) {	// �p�����[�^�Q
				store(v, *param[i]);
			}
			// �A��l������ꍇ
			if (!SQ_SUCCEEDED(sq_call(v, numparams + 1, result ? SQTrue:SQFalse, SQTrue))) {
				sq_pop(v, 2);
				SQEXCEPTION(v);
			}
			if (result) {
				store(*result, v);
				sq_pop(v, 1);
			}
			sq_pop(v, 2);
			return TJS_S_OK;
		}
	}

	tjs_error TJS_INTF_METHOD PropGet(
		tjs_uint32 flag,
		const tjs_char * membername,
		tjs_uint32 *hint,
		tTJSVariant *result,
		iTJSDispatch2 *objthis
) {
		// �v���p�e�B�͂Ȃ�
		if (!membername) {
			return TJS_E_NOTIMPL;
		}
		sq_pushobject(v, obj);
		sq_pushstring(v, membername,-1);
		if (!SQ_SUCCEEDED(sq_get(v,-2))) {
			sq_pop(v,1);
			return TJS_E_MEMBERNOTFOUND;
		}
		if (result) {
			store(*result, v);
		}
		sq_pop(v,2);
		return TJS_S_OK;
	}

	tjs_error TJS_INTF_METHOD PropSet(
		tjs_uint32 flag,
		const tjs_char *membername,
		tjs_uint32 *hint,
		const tTJSVariant *param,
		iTJSDispatch2 *objthis
		) {
		// �v���p�e�B�͂Ȃ�
		if (!membername) {
			return TJS_E_NOTIMPL;
		}
		sq_pushobject(v, obj);
		sq_pushstring(v, membername,-1);
		store(v, (tTJSVariant&)*param);
		if ((flag & TJS_MEMBERENSURE)) {
			if (!SQ_SUCCEEDED(sq_newslot(v,-3, SQFalse))) {
				sq_pop(v,1);
				SQEXCEPTION(v);
			}
		} else {
			if (!SQ_SUCCEEDED(sq_set(v,-3))) {
				sq_pop(v,1);
				SQEXCEPTION(v);
			}
		}
		sq_pop(v,1);
		return TJS_S_OK;
	}
};


//----------------------------------------------------------------------------
// iTJSDispatch2 �� UserData �Ƃ��ĕێ����邽�߂̋@�\
//----------------------------------------------------------------------------

/**
 * iTJSDispatch2 �p�I�u�W�F�N�g�J������
 */
static SQInteger
tjsDispatchRelease(SQUserPointer up, SQInteger size)
{
	iTJSDispatch2 *dispatch	= *((iTJSDispatch2**)up);
	dispatch->Release();
	return 1;
}

static const SQChar *GetString(HSQUIRRELVM v, int idx)
{
	const SQChar *x = NULL;
	sq_getstring(v,idx,&x);
	return x;
}

static HSQOBJECT GetObjectHandle(HSQUIRRELVM v, int idx)
{
	HSQOBJECT x;
	sq_resetobject(&x);
	sq_getstackobj(v,idx,&x);
    return x;
}


static SQUserPointer GetUserData(HSQUIRRELVM v, int idx,SQUserPointer tag=0)
{
	SQUserPointer otag;
	SQUserPointer up;
	if (SQ_SUCCEEDED(sq_getuserdata(v,idx,&up,&otag)) && tag == otag) {
		return up;
	}
	return NULL;
}

/**
 * iTJSDispatch2 �p�v���p�e�B�̎擾
 * @param v squirrel VM
 */
static SQInteger
get(HSQUIRRELVM v)
{
	SQUserPointer up = GetUserData(v, 1, TJSTYPETAG);
	if (up) {
		iTJSDispatch2 *dispatch	= *((iTJSDispatch2**)up);
		tTJSVariant result;
		if (SUCCEEDED(dispatch->PropGet(0, GetString(v, 2), NULL, &result, dispatch))) {
			store(v, result);
			return 1;
		}
	}
	return 0;
}

/**
 * iTJSDispatch2 �p�v���p�e�B�̐ݒ�
 * @param v squirrel VM
 */
static SQInteger
set(HSQUIRRELVM v)
{
	SQUserPointer up = GetUserData(v, 1, TJSTYPETAG);
	if (up) {
		iTJSDispatch2 *dispatch	= *((iTJSDispatch2**)up);
		tTJSVariant result;
		store(result, v, GetObjectHandle(v, 3));
		dispatch->PropSet(TJS_MEMBERENSURE, GetString(v, 2), NULL, &result, dispatch);
	}
	return 0;
}

/**
 * iTJSDispatch2 �p���\�b�h�܂��̓R���X�g���N�^�̌Ăяo��
 * @param v squirrel VM
 */
static SQInteger
call(HSQUIRRELVM v)
{
	// param1 �I�u�W�F�N�g
	// param2 �I���W�i���I�u�W�F�N�g
	// param3 �` �{���̈�����

	SQUserPointer up = GetUserData(v, 1, TJSTYPETAG);
	int ret = 0;
	if (up) {
		iTJSDispatch2 *dispatch	= *((iTJSDispatch2**)up);

		// this ���擾
		iTJSDispatch2 *thisobj = NULL;
		up = GetUserData(v, 2, TJSTYPETAG);
		if (up) {
			thisobj = *((iTJSDispatch2**)up);
		}
		
		int argc = sq_gettop(v) - 2;
		
		// �����ϊ�
		tTJSVariant **args = new tTJSVariant*[argc];
		for (int i=0;i<argc;i++) {
			args[i] = new tTJSVariant();
			store(*args[i], v, GetObjectHandle(v, i+3));
		}

		if (dispatch->IsInstanceOf(0, NULL, NULL, L"Class", dispatch) == TJS_S_TRUE) {
			// �N���X�I�u�W�F�N�g�̏ꍇ�R���X�g���N�^�Ƃ݂Ȃ�
			iTJSDispatch2 *instance = NULL;
			if (SUCCEEDED(dispatch->CreateNew(0, NULL, NULL, &instance, argc, args, thisobj))) {
				store(v, instance);
				ret = 1;
			}
		} else {
			// ���\�b�h�Ăяo��
			tTJSVariant result;
			if (SUCCEEDED(dispatch->FuncCall(0, NULL, NULL, &result, argc, args, thisobj))) {
				if (result.Type() != tvtVoid) {
					store(v, result);
					ret = 1;
				}
			}
		}
			
		// �����j��
		for (int i=0;i<argc;i++) {
			delete args[i];
		}
		delete[] args;
	}
	return ret;
}

/**
 * iTJSDispatch2 �� squirrel �̋�Ԃɓ�������
 * @param v squirrel VM
 * @param dispatch iTJSDispatch2
 */
void
store(HSQUIRRELVM v, iTJSDispatch2 *dispatch)
{
	if (dispatch) {
		dispatch->AddRef();
		SQUserPointer up = sq_newuserdata(v, sizeof(iTJSDispatch2*));
		*((iTJSDispatch2**)up) = dispatch;

		// �^�O�o�^
		sq_settypetag(v, -1, TJSTYPETAG);
		
		// �J�����W�b�N��ǉ�
		sq_setreleasehook(v, -1, tjsDispatchRelease);

		// ���\�b�h�Q��ǉ�
		sq_newtable(v);

		sq_pushstring(v, L"_get", -1);
		sq_newclosure(v, get, 0);
		sq_createslot(v, -3);

		sq_pushstring(v, L"_set", -1);
		sq_newclosure(v, set, 0);
		sq_createslot(v, -3);

		sq_pushstring(v, L"_call", -1);
		sq_newclosure(v, call, 0);
		sq_createslot(v, -3);
		
		sq_setdelegate(v, -2);

	} else {
		sq_pushnull(v);
	}
}

/**
 * tTJSVariant �� squirrel �̋�Ԃɓ�������
 * @param v squirrel VM
 * @param variant tTJSVariant
 */
void
store(HSQUIRRELVM v, tTJSVariant &variant)
{
	switch (variant.Type()) {
	case tvtVoid:
		sq_pushnull(v);
		break;
	case tvtObject:
		store(v, variant.AsObjectNoAddRef());
		break;
	case tvtString:
		sq_pushstring(v, variant.GetString(), -1);
		break;
	case tvtOctet: // XXX
		sq_pushnull(v);
		break;
	case tvtInteger:
		sq_pushinteger(v, (SQInteger)(variant));
		break;
	case tvtReal:
		sq_pushfloat(v, (SQFloat)(double)(variant));
		break;
	}
}


/**
 * squirrel �̃I�u�W�F�N�g�� tTJSVariant �ɕϊ�����(�l�n���j
 * @param result ���ʊi�[��
 */
void
store(tTJSVariant &result, HSQUIRRELVM v, HSQOBJECT &obj)
{
	result.Clear();
	switch (obj._type) {
	case OT_NULL:
		break;
	case OT_INTEGER:
		result = sq_objtointeger(&obj);
		break;
	case OT_FLOAT:
		result = (double)sq_objtofloat(&obj);
		break;
	case OT_BOOL:
		result = sq_objtobool(&obj) ? 1 : 0;
		break;
	case OT_STRING:
		result = sq_objtostring(&obj);
		break;
	case OT_USERDATA:
		{
			sq_pushobject(v, obj);
			SQUserPointer data, typetag;
			sq_getuserdata(v, -1, &data, &typetag);
			if (data && typetag == TJSTYPETAG) {
				result = *((iTJSDispatch2**)data);
			}
			sq_pop(v, 1);
		}
		break;
	case OT_TABLE:
	case OT_ARRAY:
	case OT_CLOSURE:
	case OT_NATIVECLOSURE:
	case OT_GENERATOR:
	case OT_USERPOINTER:
	case OT_THREAD:
	case OT_CLASS:
	case OT_INSTANCE:
	case OT_WEAKREF:
		// ���b�s���O���K�v!
		{
			iTJSDispatch2 *tjsobj = new iTJSDispatch2Wrapper(v, obj);
			result = tjsobj;
			tjsobj->Release();
		}
		break;
	}
}

void
store(tTJSVariant &result, HSQUIRRELVM v, int idx)
{
	HSQOBJECT x;
	sq_resetobject(&x);
	sq_getstackobj(v,idx,&x);
	store(result, v, x);
}

// -------------------------------------------------------

/**
 * Squirrel �� �O���[�o����Ԃɓo�^�������s��
 */
void registglobal(HSQUIRRELVM v, const SQChar *name, iTJSDispatch2 *dispatch)
{
	sq_pushroottable(v);
	sq_pushstring(v, name, -1);
	store(v, dispatch);
	sq_createslot(v, -3); 
	sq_pop(v, 1);
}

/**
 * Squirrel �� �O���[�o����Ԃ���폜�������s��
 */
void unregistglobal(HSQUIRRELVM v, const SQChar *name)
{
	sq_pushroottable(v);
	sq_pushstring(v, name, -1);
	sq_deleteslot(v, -2, SQFalse); 
	sq_pop(v, 1);
}
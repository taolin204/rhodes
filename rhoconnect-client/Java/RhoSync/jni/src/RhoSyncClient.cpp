/*------------------------------------------------------------------------
* (The MIT License)
* 
* Copyright (c) 2008-2011 Rhomobile, Inc.
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
* 
* http://rhomobile.com
*------------------------------------------------------------------------*/

#include <vector>

#include "common/RhoStd.h"
#include "rhodes/JNIRhodes.h"
#include "sync/SyncThread.h"
#include "SyncClient/SyncClient.h"

#include "com_rhomobile_rhosync_RhoSyncClient.h"
#include "com_rhomobile_rhosync_RhomModel.h"

typedef std::vector<RHOM_MODEL> model_vector;
typedef std::vector<rho::String> string_vector;

RHO_GLOBAL void JNICALL Java_com_rhomobile_rhosync_RhomModel_init
  (JNIEnv * env, jobject jmodel)
{
    jclass clsmodel = getJNIClass(RHOSYNC_JAVA_CLASS_RHOMMODEL);
    if (!clsmodel) return;

    jmethodID midmodeltype = getJNIClassMethod(env, clsmodel, "setModelType", "(I)V");
    if (!midmodeltype) return;
    jmethodID midsynctype = getJNIClassMethod(env, clsmodel, "setSyncType", "(I)V");
    if (!midsynctype) return;
    jmethodID midsyncpri = getJNIClassMethod(env, clsmodel, "setSyncPriority", "(I)V");
    if (!midsyncpri) return;
    jmethodID midpart = getJNIClassMethod(env, clsmodel, "setPartition", "(Ljava/lang/String;)V");
    if (!midpart) return;

    RHOM_MODEL model;
    rho_syncclient_initmodel(&model);

    env->CallVoidMethod(jmodel, midmodeltype, model.type);
    env->CallVoidMethod(jmodel, midsynctype, model.sync_type);
    env->CallVoidMethod(jmodel, midsyncpri, model.sync_priority);
    env->CallVoidMethod(jmodel, midpart, rho_cast<jhstring>(env, model.partition).get());
}


RHO_GLOBAL void JNICALL Java_com_rhomobile_rhosync_RhoSyncClient_initialize
  (JNIEnv * env, jobject, jobjectArray jmodels)
{
    jclass clsmodel = getJNIClass(RHOSYNC_JAVA_CLASS_RHOMMODEL);
    if (!clsmodel) return;
    jmethodID midname = getJNIClassMethod(env, clsmodel, "getName", "()Ljava/lang/String;");
    if (!midname) return;
    jmethodID midmodeltype = getJNIClassMethod(env, clsmodel, "getModelType", "()I");
    if (!midmodeltype) return;
    jmethodID midsynctype = getJNIClassMethod(env, clsmodel, "getSyncType", "()I");
    if (!midsynctype) return;
    jmethodID midsyncpri = getJNIClassMethod(env, clsmodel, "getSyncPriority", "()I");
    if (!midsyncpri) return;
    jmethodID midpart = getJNIClassMethod(env, clsmodel, "getPartition", "()Ljava/lang/String;");
    if (!midpart) return;

    size_t cnt = static_cast<model_vector::size_type>(env->GetArrayLength(jmodels));
    model_vector models(cnt);
    string_vector names(cnt);
    string_vector partitions(cnt);

    for(model_vector::size_type i = 0, cnt = models.size(); i < cnt; ++i)
    {
        jobject jmodel = env->GetObjectArrayElement(jmodels, i);
        RHOM_MODEL& model = models[i];
        rho::String& name = names[i];
        rho::String& partition = partitions[i];
        
        jhobject jname = env->CallObjectMethod(jmodel, midname);
        name = rho_cast<rho::String>(env, static_cast<jstring>(jname.get()));
        model.name = const_cast<char*>(name.c_str());

        model.type = static_cast<RHOM_MODEL_TYPE>(env->CallIntMethod(jmodel, midmodeltype));
        model.sync_type = static_cast<RHOM_SYNC_TYPE>(env->CallIntMethod(jmodel, midsynctype));
        model.sync_priority = env->CallIntMethod(jmodel, midsyncpri);

        jhobject jpart = env->CallObjectMethod(jmodel, midpart);
        partition = rho_cast<rho::String>(env, static_cast<jstring>(jpart.get()));
        model.partition = const_cast<char*>(partition.c_str());
    }

    rho_syncclient_init(&models.front(), models.size());
}

RHO_GLOBAL void JNICALL Java_com_rhomobile_rhosync_RhoSyncClient_setSyncServer
  (JNIEnv * env, jobject, jstring host)
{
    rho_sync_set_syncserver(rho_cast<std::string>(env, host).c_str());
}

RHO_GLOBAL void JNICALL Java_com_rhomobile_rhosync_RhoSyncClient_setThreadedMode
  (JNIEnv *, jobject, jboolean jmode)
{
    bool mode = jmode;
    rho_sync_set_threaded_mode(mode ? 1 : 0);
}

//RHO_GLOBAL jboolean JNICALL Java_com_rhomobile_rhosync_RhoSyncClient_getThreadedMode
//  (JNIEnv *, jobject)
//{
//    return (jboolean)(rho_sync_get_threaded_mode() != 0);
//}

RHO_GLOBAL void JNICALL Java_com_rhomobile_rhosync_RhoSyncClient_setPollInterval
  (JNIEnv *, jobject, jint time)
{
    rho_sync_set_pollinterval(time);
}

RHO_GLOBAL jint JNICALL Java_com_rhomobile_rhosync_RhoSyncClient_getPollInterval
  (JNIEnv *, jobject)
{
    return (jint)rho_sync_get_pollinterval();
}

RHO_GLOBAL void JNICALL Java_com_rhomobile_rhosync_RhoSyncClient_setBulkSyncState
  (JNIEnv *, jobject, jint)
{
}

RHO_GLOBAL jint JNICALL Java_com_rhomobile_rhosync_RhoSyncClient_getBulkSyncState
  (JNIEnv *, jobject)
{
    return (jint)0;
}

RHO_GLOBAL void JNICALL Java_com_rhomobile_rhosync_RhoSyncClient_setConfigString
  (JNIEnv *, jobject, jstring, jstring)
{
}

RHO_GLOBAL jstring JNICALL Java_com_rhomobile_rhosync_RhoSyncClient_getConfigString
  (JNIEnv * env, jobject, jstring)
{
    const char* cs = "";
    return rho_cast<jhstring>(env, cs).release();
}

RHO_GLOBAL void JNICALL Java_com_rhomobile_rhosync_RhoSyncClient_initDatabase
  (JNIEnv *, jobject)
{
}

RHO_GLOBAL void JNICALL Java_com_rhomobile_rhosync_RhoSyncClient_addModels
  (JNIEnv *, jobject, jobjectArray)
{
}

RHO_GLOBAL void JNICALL Java_com_rhomobile_rhosync_RhoSyncClient_databaseFullResetAndLogout
  (JNIEnv *, jobject)
{
}

RHO_GLOBAL jboolean JNICALL Java_com_rhomobile_rhosync_RhoSyncClient_isLoggedIn
  (JNIEnv *, jobject)
{
    return (jboolean)rho_sync_logged_in() == 1;
}

RHO_GLOBAL jobject JNICALL Java_com_rhomobile_rhosync_RhoSyncClient_loginWithUser
  (JNIEnv * env, jobject, jstring juser, jstring jpass)
{
    unsigned long res = rho_sync_login(rho_cast<std::string>(env, juser).c_str(),
                                       rho_cast<std::string>(env, jpass).c_str(),
                                       "");
    return (jobject)NULL;
}

RHO_GLOBAL jobject JNICALL Java_com_rhomobile_rhosync_RhoSyncClient_syncAll
  (JNIEnv *, jobject)
{
    return (jobject)NULL;
}

RHO_GLOBAL void JNICALL Java_com_rhomobile_rhosync_RhoSyncClient_nativeInit
  (JNIEnv * env, jclass/*, jstring root, jstring sqliteJournals*/)
{
    //android_set_path(rho_cast<rho::String>(root), rho_cast<rho::String>(sqliteJournals));
    android_setup(env);
}
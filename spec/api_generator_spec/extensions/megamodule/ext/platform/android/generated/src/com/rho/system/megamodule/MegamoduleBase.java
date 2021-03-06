package com.rho.system.megamodule;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.rhomobile.rhodes.api.IMethodResult;
import com.rhomobile.rhodes.api.RhoApiObject;

import com.rhomobile.rhodes.api.RhoApiPropertyBag; 

public class MegamoduleBase extends RhoApiObject {

    private RhoApiPropertyBag mPropertyBag;
    public MegamoduleBase(String id) {
        super(id);

        mPropertyBag = new RhoApiPropertyBag();
    }



    public void getStringProperty(IMethodResult result) {

        getProperty("StringProperty", result);
    }

    public static class getStringPropertyTask implements Runnable {
        private IMegamodule mApiObject; 
        private IMethodResult mResult;

        public getStringPropertyTask(IMegamodule obj, 
                IMethodResult result) {
            this.mApiObject = obj; 
            this.mResult = result;
        }

        @Override
        public void run() {
            mApiObject.getStringProperty(mResult);
        }
    }



    public void setStringProperty(String value, IMethodResult result) {

        setProperty("StringProperty", value, result);
    }

    public static class setStringPropertyTask implements Runnable {
        private IMegamodule mApiObject; 
        private String value;
        private IMethodResult mResult;

        public setStringPropertyTask(IMegamodule obj, 
                String value, 
                IMethodResult result) {
            this.mApiObject = obj; 
            this.value = value;
            this.mResult = result;
        }

        @Override
        public void run() {
            mApiObject.setStringProperty(
                value, mResult);
        }
    }




    public static class getIntegerPropertyTask implements Runnable {
        private IMegamodule mApiObject; 
        private IMethodResult mResult;

        public getIntegerPropertyTask(IMegamodule obj, 
                IMethodResult result) {
            this.mApiObject = obj; 
            this.mResult = result;
        }

        @Override
        public void run() {
            mApiObject.getIntegerProperty(mResult);
        }
    }




    public static class typesTestTask implements Runnable {
        private IMegamodule mApiObject; 
        private String paramStr;
        private boolean paramBool;
        private int paramInt;
        private double paramFloat;
        private List<String> paramArray;
        private Map<String, String> paramHash;
        private IMethodResult mResult;

        public typesTestTask(IMegamodule obj, 
                String paramStr, 
                boolean paramBool, 
                int paramInt, 
                double paramFloat, 
                List<String> paramArray, 
                Map<String, String> paramHash, 
                IMethodResult result) {
            this.mApiObject = obj; 
            this.paramStr = paramStr;
            this.paramBool = paramBool;
            this.paramInt = paramInt;
            this.paramFloat = paramFloat;
            this.paramArray = paramArray;
            this.paramHash = paramHash;
            this.mResult = result;
        }

        @Override
        public void run() {
            mApiObject.typesTest(
                paramStr, 
                paramBool, 
                paramInt, 
                paramFloat, 
                paramArray, 
                paramHash, mResult);
        }
    }




    public static class produceArrayTask implements Runnable {
        private IMegamodule mApiObject; 
        private IMethodResult mResult;

        public produceArrayTask(IMegamodule obj, 
                IMethodResult result) {
            this.mApiObject = obj; 
            this.mResult = result;
        }

        @Override
        public void run() {
            mApiObject.produceArray(mResult);
        }
    }




    public static class showAlertFromUIThreadTask implements Runnable {
        private IMegamodule mApiObject; 
        private String message;
        private IMethodResult mResult;

        public showAlertFromUIThreadTask(IMegamodule obj, 
                String message, 
                IMethodResult result) {
            this.mApiObject = obj; 
            this.message = message;
            this.mResult = result;
        }

        @Override
        public void run() {
            mApiObject.showAlertFromUIThread(
                message, mResult);
        }
    }




    public static class setPeriodicallyCallbackTask implements Runnable {
        private IMegamodule mApiObject; 
        private int periodInMilliseconds;
        private IMethodResult mResult;

        public setPeriodicallyCallbackTask(IMegamodule obj, 
                int periodInMilliseconds, 
                IMethodResult result) {
            this.mApiObject = obj; 
            this.periodInMilliseconds = periodInMilliseconds;
            this.mResult = result;
        }

        @Override
        public void run() {
            mApiObject.setPeriodicallyCallback(
                periodInMilliseconds, mResult);
        }
    }




    public static class isPeriodicallyCallbackSettedTask implements Runnable {
        private IMegamodule mApiObject; 
        private IMethodResult mResult;

        public isPeriodicallyCallbackSettedTask(IMegamodule obj, 
                IMethodResult result) {
            this.mApiObject = obj; 
            this.mResult = result;
        }

        @Override
        public void run() {
            mApiObject.isPeriodicallyCallbackSetted(mResult);
        }
    }




    public static class stopPeriodicallyCallbackTask implements Runnable {
        private IMegamodule mApiObject; 
        private IMethodResult mResult;

        public stopPeriodicallyCallbackTask(IMegamodule obj, 
                IMethodResult result) {
            this.mApiObject = obj; 
            this.mResult = result;
        }

        @Override
        public void run() {
            mApiObject.stopPeriodicallyCallback(mResult);
        }
    }


    public void getProperty(String propertyName, IMethodResult result) { 
        mPropertyBag.getProperty(propertyName, result);
    }


    public static class getPropertyTask implements Runnable {
        private IMegamodule mApiObject; 
        private String propertyName;
        private IMethodResult mResult;

        public getPropertyTask(IMegamodule obj, 
                String propertyName, 
                IMethodResult result) {
            this.mApiObject = obj; 
            this.propertyName = propertyName;
            this.mResult = result;
        }

        @Override
        public void run() {
            mApiObject.getProperty(
                propertyName, mResult);
        }
    }


    public void getProperties(List<String> arrayofNames, IMethodResult result) { 
        mPropertyBag.getProperties(arrayofNames, result);
    }


    public static class getPropertiesTask implements Runnable {
        private IMegamodule mApiObject; 
        private List<String> arrayofNames;
        private IMethodResult mResult;

        public getPropertiesTask(IMegamodule obj, 
                List<String> arrayofNames, 
                IMethodResult result) {
            this.mApiObject = obj; 
            this.arrayofNames = arrayofNames;
            this.mResult = result;
        }

        @Override
        public void run() {
            mApiObject.getProperties(
                arrayofNames, mResult);
        }
    }


    public void getAllProperties(IMethodResult result) { 
        mPropertyBag.getAllProperties(result);
    }


    public static class getAllPropertiesTask implements Runnable {
        private IMegamodule mApiObject; 
        private IMethodResult mResult;

        public getAllPropertiesTask(IMegamodule obj, 
                IMethodResult result) {
            this.mApiObject = obj; 
            this.mResult = result;
        }

        @Override
        public void run() {
            mApiObject.getAllProperties(mResult);
        }
    }


    public void setProperty(String propertyName, String propertyValue, IMethodResult result) { 
        mPropertyBag.setProperty(propertyName, propertyValue, result);
    }


    public static class setPropertyTask implements Runnable {
        private IMegamodule mApiObject; 
        private String propertyName;
        private String propertyValue;
        private IMethodResult mResult;

        public setPropertyTask(IMegamodule obj, 
                String propertyName, 
                String propertyValue, 
                IMethodResult result) {
            this.mApiObject = obj; 
            this.propertyName = propertyName;
            this.propertyValue = propertyValue;
            this.mResult = result;
        }

        @Override
        public void run() {
            mApiObject.setProperty(
                propertyName, 
                propertyValue, mResult);
        }
    }


    public void setProperties(Map<String, String> propertyMap, IMethodResult result) { 
        mPropertyBag.setProperties(propertyMap, result);
    }


    public static class setPropertiesTask implements Runnable {
        private IMegamodule mApiObject; 
        private Map<String, String> propertyMap;
        private IMethodResult mResult;

        public setPropertiesTask(IMegamodule obj, 
                Map<String, String> propertyMap, 
                IMethodResult result) {
            this.mApiObject = obj; 
            this.propertyMap = propertyMap;
            this.mResult = result;
        }

        @Override
        public void run() {
            mApiObject.setProperties(
                propertyMap, mResult);
        }
    }


    public void clearAllProperties(IMethodResult result) { 
        mPropertyBag.clearAllProperties(result);
    }


    public static class clearAllPropertiesTask implements Runnable {
        private IMegamodule mApiObject; 
        private IMethodResult mResult;

        public clearAllPropertiesTask(IMegamodule obj, 
                IMethodResult result) {
            this.mApiObject = obj; 
            this.mResult = result;
        }

        @Override
        public void run() {
            mApiObject.clearAllProperties(mResult);
        }
    }

}

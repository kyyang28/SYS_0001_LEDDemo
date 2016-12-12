
package com.android.server;

import android.os.ILedService;

public class LedService extends ILedService.Stub {
    private static final String TAG = "LedService";

    /* Constructor of LedService */
    public LedService() {
        native_ledOpen();
    }
    
    /* call native c function to access hardware */
    public int ledCtrl(int whichLed, int ledStatus) throws android.os.RemoteException
    {
        return native_ledCtrl(whichLed, ledStatus);
    }

    public static native int native_ledOpen();
    public static native void native_ledClose();
    public static native int native_ledCtrl(int whichLed, int ledStatus);
}


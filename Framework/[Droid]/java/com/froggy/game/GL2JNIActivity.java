/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.froggy.game;

import android.app.Activity;
import android.media.AudioManager;
import android.os.Build;
import android.os.Bundle;
import android.content.Context;
import android.util.Log;
import android.view.WindowManager;

import java.io.File;


public class GL2JNIActivity extends Activity {

    GL2JNIView mView;
    private JavaOutlets mOutlets;

    @Override protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);

        Log.d("java", "ON_CREATE...");

        mOutlets = new JavaOutlets();
        GL2JNILib.NativeAppShellPreinitialize();

        File aFile = getDir("documents", Context.MODE_PRIVATE);
        String aDocumentsDirectory = aFile.getAbsolutePath();
        aDocumentsDirectory = getFilesDir().getAbsolutePath();
        aDocumentsDirectory += "/";

        GL2JNILib.NativeAppShellSetDirectoryDocuments(aDocumentsDirectory);



        int sampleRate = 0;
        int bufSize = 0;

        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1) {
            AudioManager myAudioMgr = (AudioManager) getSystemService(Context.AUDIO_SERVICE);
            String nativeParam = myAudioMgr.getProperty(AudioManager.PROPERTY_OUTPUT_SAMPLE_RATE);
            sampleRate = Integer.parseInt(nativeParam);
            nativeParam = myAudioMgr.getProperty(AudioManager.PROPERTY_OUTPUT_FRAMES_PER_BUFFER);
            bufSize = Integer.parseInt(nativeParam);
        }
        Log.d("java", "Device Sample Rate = " + sampleRate + ", Buff = " + bufSize);




        mView = new GL2JNIView(getApplication());
        setContentView(mView);
        mOutlets.setOpenGL(mView);


    }

    @Override protected void onPause() {
        Log.d("java", "onPause()\n");


        GL2JNILib.NativeAppShellPause();
        if (mView != null) {
            mView.onPause();
            //mOutlets.setOpenGL(null);
            //mView = null;

        }

        super.onPause();
    }

    @Override protected void onResume() {
        Log.d("java", "onResume()\n");
        mView.onResume();
        GL2JNILib.NativeAppShellResume();
        super.onResume();
    }




}
